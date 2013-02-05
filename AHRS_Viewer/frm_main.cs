using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using System.Drawing.Imaging;
using System.Diagnostics;
using SharpGL;
using SharpGL.SceneGraph.Assets;

namespace uart_cam
{
    public partial class mainForm : Form
    {
        private SerialPort comm = new SerialPort();
        bool start_flag = false;
        int start_match_pos = 0;
        int recv_cnt = 0;

        Bitmap image = null;
        byte[] recv_data = new byte[26];
        byte[] start_mark={0xa5,0x5a,0x12,0xa1};
        Int32[] imu_result = new Int32[14];
        int mFPS = 0;
        float rtri = 0;
        Texture texture = new Texture();
        float rx, ry, rz;
        public mainForm()
        {
            InitializeComponent();
            //  Get the OpenGL object, for quick access.
            SharpGL.OpenGL gl = this.openGLControl1.OpenGL;

            //  A bit of extra initialisation here, we have to enable textures.
            gl.Enable(OpenGL.GL_TEXTURE_2D);

            //  Create our texture object from a file. This creates the texture for OpenGL.
            texture.Create(gl, "E:/Projects/MiniQ/AHRS_Viewer/Crate.bmp");
        }
        private void openGLControl1_OpenGLDraw(object sender, PaintEventArgs e)
        {
            //  Get the OpenGL object, for quick access.
            SharpGL.OpenGL gl = this.openGLControl1.OpenGL;

            gl.Clear(OpenGL.GL_COLOR_BUFFER_BIT | OpenGL.GL_DEPTH_BUFFER_BIT);
            gl.LoadIdentity();
            gl.Translate(0.0f, 0.0f, -6.0f);

            gl.Rotate(rx, ry, rz);
            //  Bind the texture.
            texture.Bind(gl);

            gl.Begin(OpenGL.GL_QUADS);

            // Front Face
            gl.TexCoord(0.0f, 0.0f); gl.Vertex(-1.0f, -1.0f, 1.0f);	// Bottom Left Of The Texture and Quad
            gl.TexCoord(1.0f, 0.0f); gl.Vertex(1.0f, -1.0f, 1.0f);	// Bottom Right Of The Texture and Quad
            gl.TexCoord(1.0f, 1.0f); gl.Vertex(1.0f, 1.0f, 1.0f);	// Top Right Of The Texture and Quad
            gl.TexCoord(0.0f, 1.0f); gl.Vertex(-1.0f, 1.0f, 1.0f);	// Top Left Of The Texture and Quad

            // Back Face
            gl.TexCoord(1.0f, 0.0f); gl.Vertex(-1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
            gl.TexCoord(1.0f, 1.0f); gl.Vertex(-1.0f, 1.0f, -1.0f);	// Top Right Of The Texture and Quad
            gl.TexCoord(0.0f, 1.0f); gl.Vertex(1.0f, 1.0f, -1.0f);	// Top Left Of The Texture and Quad
            gl.TexCoord(0.0f, 0.0f); gl.Vertex(1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad

            // Top Face
            gl.TexCoord(0.0f, 1.0f); gl.Vertex(-1.0f, 1.0f, -1.0f);	// Top Left Of The Texture and Quad
            gl.TexCoord(0.0f, 0.0f); gl.Vertex(-1.0f, 1.0f, 1.0f);	// Bottom Left Of The Texture and Quad
            gl.TexCoord(1.0f, 0.0f); gl.Vertex(1.0f, 1.0f, 1.0f);	// Bottom Right Of The Texture and Quad
            gl.TexCoord(1.0f, 1.0f); gl.Vertex(1.0f, 1.0f, -1.0f);	// Top Right Of The Texture and Quad

            // Bottom Face
            gl.TexCoord(1.0f, 1.0f); gl.Vertex(-1.0f, -1.0f, -1.0f);	// Top Right Of The Texture and Quad
            gl.TexCoord(0.0f, 1.0f); gl.Vertex(1.0f, -1.0f, -1.0f);	// Top Left Of The Texture and Quad
            gl.TexCoord(0.0f, 0.0f); gl.Vertex(1.0f, -1.0f, 1.0f);	// Bottom Left Of The Texture and Quad
            gl.TexCoord(1.0f, 0.0f); gl.Vertex(-1.0f, -1.0f, 1.0f);	// Bottom Right Of The Texture and Quad

            // Right face
            gl.TexCoord(1.0f, 0.0f); gl.Vertex(1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
            gl.TexCoord(1.0f, 1.0f); gl.Vertex(1.0f, 1.0f, -1.0f);	// Top Right Of The Texture and Quad
            gl.TexCoord(0.0f, 1.0f); gl.Vertex(1.0f, 1.0f, 1.0f);	// Top Left Of The Texture and Quad
            gl.TexCoord(0.0f, 0.0f); gl.Vertex(1.0f, -1.0f, 1.0f);	// Bottom Left Of The Texture and Quad

            // Left Face
            gl.TexCoord(0.0f, 0.0f); gl.Vertex(-1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
            gl.TexCoord(1.0f, 0.0f); gl.Vertex(-1.0f, -1.0f, 1.0f);	// Bottom Right Of The Texture and Quad
            gl.TexCoord(1.0f, 1.0f); gl.Vertex(-1.0f, 1.0f, 1.0f);	// Top Right Of The Texture and Quad
            gl.TexCoord(0.0f, 1.0f); gl.Vertex(-1.0f, 1.0f, -1.0f);	// Top Left Of The Texture and Quad
            gl.End();

            gl.Flush();

            //rtri += 1.0f;// 0.2f;						// Increase The Rotation Variable For The Triangle 
        }
        private void mainForm_Load(object sender, EventArgs e)
        {
            string[] ports = SerialPort.GetPortNames();
            Array.Sort(ports);
            comboPortName.Items.AddRange(ports);
            comboPortName.SelectedIndex = comboPortName.Items.Count > 0 ? 0 : -1;
            image = new Bitmap(320, 240, PixelFormat.Format32bppArgb);
            //comm.DataReceived += comm_DataReceived;
            comm.DataReceived += new
                System.IO.Ports.SerialDataReceivedEventHandler(comm_DataReceived);

        }


        void comm_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            
            
            //Trace.Write(n);
            this.Invoke((EventHandler)(delegate
            {
                int n = comm.BytesToRead;
                if (n == 0) return;
                byte[] buf = new byte[n];

                comm.Read(buf, 0, n);
                foreach (byte b in buf)
                {
                    
                    if (!start_flag)
                    {
                        if (b == start_mark[start_match_pos])
                        {
                            start_match_pos++;
                            if (start_match_pos == start_mark.Length)
                            {
                                start_flag = true; 
                                recv_cnt = 0;
                                start_match_pos = 0;
                                //Trace.WriteLine("Start a frame");
                                mFPS++;
                            }
                        }
                        else start_match_pos = 0;
                    }
                    else
                    {

                        recv_data[recv_cnt] = b;
                        ++recv_cnt;
                        if (recv_cnt == 26)
                        {
                            for (int i = 0; i < 26; i += 2)
                            {
                                imu_result[i / 2] = (Int32)(UInt16)(recv_data[i] << 8 | recv_data[i + 1]);
                                if (imu_result[i / 2] >= 32768)
                                {
                                    imu_result[i / 2] -= 32768;
                                    imu_result[i / 2] = -imu_result[i / 2];
                                }
                            }
                            recv_cnt = 0;
                            
                            lb_ax.Text = "" + imu_result[0] / 10.0f ;
                            lb_ay.Text = "" + imu_result[1] / 10.0f;
                            lb_az.Text = "" + imu_result[2] / 10.0f;

                            lb_gx.Text = "" + imu_result[3] / 10.0f;
                            lb_gy.Text = "" + imu_result[4] / 10.0f;
                            lb_gz.Text = "" + imu_result[5] / 10.0f;

                            lb_mx.Text = "" + imu_result[6] / 10.0f;
                            lb_my.Text = "" + imu_result[7] / 10.0f;
                            lb_mz.Text = "" + imu_result[8] / 10.0f;
                            lb_yaw.Text = "" + imu_result[9] / 10.0f;
                            progressBar1.Value = progressBar1.Value + 1;
                            progressBar1.Value = (int)((imu_result[9] / 10.0f + 180.0f) / 3.6f);
                            progressBar1.Value = (progressBar1.Value - 1)>0?(progressBar1.Value - 1):0;
                            lb_pitch.Text = "" + imu_result[10] / 10.0f;
                            progressBar2.Value = progressBar2.Value + 1;
                            progressBar2.Value = (int)((imu_result[10] / 10.0f + 180.0f) / 3.6f);
                            progressBar2.Value = progressBar2.Value - 1;
                            lb_roll.Text = "" + imu_result[11] / 10.0f;
                            progressBar3.Value = progressBar3.Value + 1;
                            progressBar3.Value = (int)((imu_result[11] / 10.0f + 180.0f) / 3.6f);
                            progressBar3.Value = (progressBar3.Value - 1) > 0 ? (progressBar3.Value - 1) : 0;
                            lb_hlt.Text = "" + progressBar1.Value+0*imu_result[12];

                            ry = (imu_result[9]) / 10.0f;
                            rz = -(imu_result[10]) / 10.0f;
                            rx = (imu_result[11]) / 10.0f;
                            start_flag = false;
                            recv_cnt = 0;
                            start_match_pos = 0;
                        }
                        else if (recv_cnt > 25) { start_flag = false; recv_cnt = 0; }
                    }
                }
            }));
            
        }  


        private void button1_Click(object sender, EventArgs e)
        {
            Trace.Write("Click\n");
            if (comm.IsOpen) this.Invoke((EventHandler)(delegate
            { comm.Close(); }));
            else
            {
                comm.PortName = comboPortName.Text;
                Trace.WriteLine("open" + comboPortName.Text);
                comm.BaudRate = 115200;
                comm.Parity = Parity.None;
                comm.StopBits = StopBits.One;
                comm.DataBits = 8;
                comm.Handshake = Handshake.None;

                try
                {
                    comm.Open();
                    comm.DataReceived += new
                System.IO.Ports.SerialDataReceivedEventHandler(comm_DataReceived);
                }
                catch (Exception ex)
                {
                    comm = new SerialPort();
                    MessageBox.Show(ex.Message);
                }
            }
            button1.Text = comm.IsOpen ? "Close" : "Open"; 
        }

        private void mainForm_FormClosing(object sender, FormClosingEventArgs e)
        {

        }

        private void mainForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (comm.IsOpen) this.Invoke((EventHandler)(delegate
            { comm.Close(); }));
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            lb_fps.Text = "FPS: " + mFPS;
            mFPS = 0;
        }

        private void button2_Click(object sender, EventArgs e)
        {
           
        }
    }
}
