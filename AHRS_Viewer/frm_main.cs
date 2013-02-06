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
        bool closing = false;
        Bitmap image = null;
        byte[] recv_data = new byte[26];
        byte[] start_mark={0xa5,0x5a,0x12,0xa1};
        Int32[] imu_result = new Int32[14];
        int mFPS = 0;

        float ax, ay, az, gx, gy, gz, mx, my, mz, yaw, pitch, roll;


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
            Trace.WriteLine(System.IO.Directory.GetCurrentDirectory());
            texture.Create(gl, "Crate.bmp");
        }

        private void openGLControl1_OpenGLDraw(object sender, PaintEventArgs e)
        {
            //  Get the OpenGL object, for quick access.
            SharpGL.OpenGL gl = this.openGLControl1.OpenGL;

            gl.Clear(OpenGL.GL_COLOR_BUFFER_BIT | OpenGL.GL_DEPTH_BUFFER_BIT);
            gl.LoadIdentity();
            
            gl.Translate(0.0f, 0.0f, -6.0f);

            gl.Rotate(rx, ry, rz);
            gl.Scale(1.0f, 0.5f, 2.0f);
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

        int setProgressValue(int value)
        {
            if (value > 100) return 100;
            else if (value < 0) return 0;
            else return value;
        }

        void comm_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            if (closing) return;
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
                        
                        ax = imu_result[0] / 10.0f;
                        ay = imu_result[1] / 10.0f;
                        az = imu_result[2] / 10.0f;

                        gx = imu_result[3] / 10.0f;
                        gy = imu_result[4] / 10.0f;
                        gz = imu_result[5] / 10.0f;

                        mx = imu_result[6] / 10.0f;
                        my = imu_result[7] / 10.0f;
                        mz = imu_result[8] / 10.0f;

                        yaw = imu_result[9] / 10.0f;
                        pitch = imu_result[10] / 10.0f;
                        roll = imu_result[11] / 10.0f;
                        try
                        {
                            this.Invoke((EventHandler)(delegate
                            {
                                lb_ax.Text = "" + ax;
                                lb_ay.Text = "" + ay;
                                lb_az.Text = "" + az;

                                lb_gx.Text = "" + gx;
                                lb_gy.Text = "" + gy;
                                lb_gz.Text = "" + gz;

                                lb_mx.Text = "" + mx;
                                lb_my.Text = "" + my;
                                lb_mz.Text = "" + mz;
                                lb_yaw.Text = "" + yaw;
                                progressBar1.Value = setProgressValue(progressBar1.Value + 1);
                                progressBar1.Value = setProgressValue((progressBar1.Value - 1));
                                progressBar1.Value = setProgressValue((int)((yaw + 180.0f) / 3.6f));
                                lb_pitch.Text = "" + pitch;
                                progressBar2.Value = setProgressValue(progressBar2.Value + 1);
                                progressBar2.Value = setProgressValue(progressBar2.Value - 1);
                                progressBar2.Value = setProgressValue((int)((pitch + 180.0f) / 3.6f));
                                lb_roll.Text = "" + roll;
                                progressBar3.Value = setProgressValue(progressBar3.Value + 1);
                                progressBar3.Value = setProgressValue((progressBar3.Value - 1));
                                progressBar3.Value = setProgressValue((int)((roll + 180.0f) / 3.6f));

                                lb_hlt.Text = "" + imu_result[12];
                                //Trace.WriteLine(""+gz);
                            }));
                        }
                        catch(Exception ex)
                        {
                            Trace.WriteLine(ex.ToString());
                        }
                        ry = -yaw;
                        rz = pitch;
                        rx = roll;
                        start_flag = false;
                        recv_cnt = 0;
                        start_match_pos = 0;
                        //Trace.WriteLine("End frame");
                    }
                    else if (recv_cnt > 25) { start_flag = false; recv_cnt = 0; }
                }
            }
            
            
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
            closing = true;
            try
            {
                this.Invoke((EventHandler)(delegate
                { comm.Close(); }));
            }
            catch (System.Exception ex)
            {
                Trace.WriteLine(ex.ToString());
            }
            
            Trace.WriteLine("Closed");
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            lb_fps.Text = "FPS: " + mFPS;
            mFPS = 0;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string[] ports = SerialPort.GetPortNames();
            Array.Sort(ports);
            comboPortName.Items.Clear();
            comboPortName.Items.AddRange(ports);
            comboPortName.SelectedIndex = comboPortName.Items.Count > 0 ? 0 : -1;
        }
    }
}
