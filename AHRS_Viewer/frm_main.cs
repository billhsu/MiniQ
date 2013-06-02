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

namespace ahrs_viewer
{
    public partial class mainForm : Form
    {
        private SerialPort comm = new SerialPort();

        object lockThis = new object();
        
        bool start_flag = false;
        int start_match_pos = 0;
        int recv_cnt = 0;

        byte[] recv_data = new byte[10];
        byte[] start_mark={0xff,0xaa};
        Int32[] imu_result = new Int32[16];
        int mFPS = 0;


        private bool closing = false;

        float yaw, pitch, roll;


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
        float[] mat = new float[16];

        private void openGLControl1_OpenGLDraw(object sender, PaintEventArgs e)
        {
            

            //  Get the OpenGL object, for quick access.
            SharpGL.OpenGL gl = this.openGLControl1.OpenGL;

            gl.PushMatrix();
            gl.LoadIdentity();
            gl.Rotate(yaw, 0.0f, 1.0f, 0.0f);
            gl.Rotate(pitch, 1.0f, 0.0f, 0.0f);
            gl.Rotate(roll, 0.0f, 0.0f, 1.0f);
            gl.GetFloat(OpenGL.GL_MODELVIEW_MATRIX, mat);
            gl.PopMatrix();
            gl.Clear(OpenGL.GL_COLOR_BUFFER_BIT | OpenGL.GL_DEPTH_BUFFER_BIT);
            
            gl.LoadIdentity();
            gl.Translate(0, 0, -10);
            gl.PointSize(6.0f);
            gl.LoadIdentity();
            //gl.LookAt(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -6.0f, 0.0f, 0.0f, 1.0f);
            gl.Translate(0.0f, -1.0f, -5.0f);

            //gl.Rotate(rx, ry, rz);
            gl.Rotate(-yaw, 0.0f, 1.0f, 0.0f);
            gl.Rotate(-pitch, 1.0f, 0.0f, 0.0f);
            gl.Rotate(-roll, 0.0f, 0.0f, 1.0f);
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
        }
        
        private void mainForm_Load(object sender, EventArgs e)
        {
            string[] ports = SerialPort.GetPortNames();
            Array.Sort(ports);
            comboPortName.Items.AddRange(ports);
            comboPortName.SelectedIndex = comboPortName.Items.Count > 0 ? 0 : -1;

            comm.DataReceived += new
                System.IO.Ports.SerialDataReceivedEventHandler(comm_DataReceived);
            comm.ErrorReceived += new
                System.IO.Ports.SerialErrorReceivedEventHandler(comm_ErrorReceived);

        }

        int setProgressValue(int value)
        {
            if (value > 100) return 100;
            else if (value < 0) return 0;
            else return value;
        }
        void comm_ErrorReceived(object sender, SerialErrorReceivedEventArgs e)
        {
            Trace.WriteLine(sender.ToString()+" - "+e.ToString());
        }
        Object lockingObj = new Object();
        void comm_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            lock (lockingObj)
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
                                mFPS++;
                            }
                        }
                        else start_match_pos = 0;
                    }
                    else
                    {

                        recv_data[recv_cnt] = b;
                        ++recv_cnt;
                        if (recv_cnt == 8)
                        {
                            for (int i = 0; i < 8; i += 2)
                            {
                                imu_result[i / 2] = (Int32)(UInt16)(recv_data[i] << 8 | recv_data[i + 1]);
                                if (imu_result[i / 2] >= 32768)
                                {
                                    imu_result[i / 2] -= 32768;
                                    imu_result[i / 2] = -imu_result[i / 2];
                                }
                            }
                            recv_cnt = 0;

                            yaw = imu_result[0] / 10.0f;
                            pitch = imu_result[1] / 10.0f;
                            roll = imu_result[2] / 10.0f;
                            //lb_fps.Text = "FPS:" + imu_result[3]/10*25;
                            start_flag = false;
                            recv_cnt = 0;
                            start_match_pos = 0;
                        }
                        else if (recv_cnt > 9)
                        {
                            Trace.WriteLine("This should not appear");
                            start_flag = false;
                            start_match_pos = 0;
                            recv_cnt = 0;
                        }
                    }
                }
            } 
        }


        private void button1_Click(object sender, EventArgs e)
        {
            Trace.Write("Click\n");
            trackBar1.Value = 0;
            lb_thr.Text = "Throttle:" + trackBar1.Value * 10 + "%";
            if (comm.IsOpen)
            {
                closing = true;
                comm.Close();
                closing = false;
                
            }
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
                //while (Listening) Application.DoEvents();
                comm.Close();
                closing = false;
            }
            catch (System.Exception ex)
            {
                Trace.WriteLine(ex.ToString());
            }
            
            Trace.WriteLine("Closed");
        }
        int oldFPS = 0;
        private void timer1_Tick(object sender, EventArgs e)
        {
            /*if(oldFPS>50 && mFPS<30 && comm.IsOpen){
                Trace.WriteLine("Oops!");
                comm.DiscardInBuffer();
            }*/
            lb_fps.Text = "FPS: " + mFPS;
            oldFPS = mFPS;
            mFPS = 0;
            lb_fps.Text += " calcFPS:" + imu_result[3];
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string[] ports = SerialPort.GetPortNames();
            Array.Sort(ports);
            comboPortName.Items.Clear();
            comboPortName.Items.AddRange(ports);
            comboPortName.SelectedIndex = comboPortName.Items.Count > 0 ? 0 : -1;
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            lb_yaw.Text = "" + yaw;
            progressBar1.Value = setProgressValue(progressBar1.Value + 1);
            progressBar1.Value = setProgressValue((progressBar1.Value - 1));
            progressBar1.Value = setProgressValue((int)((yaw + 180.0f) / 3.6f));
            lb_pitch.Text = "" + pitch;
            progressBar2.Value = setProgressValue(progressBar2.Value + 1);
            progressBar2.Value = setProgressValue(progressBar2.Value - 1);
            progressBar2.Value = setProgressValue((int)((pitch + 90.0f) / 1.8f));
            lb_roll.Text = "" + roll;
            progressBar3.Value = setProgressValue(progressBar3.Value + 1);
            progressBar3.Value = setProgressValue((progressBar3.Value - 1));
            progressBar3.Value = setProgressValue((int)((roll + 90.0f) / 1.8f));
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (comm.IsOpen)
            {
                comm.Write(start_mark, 0, start_mark.Length);
                Byte[] stop = { 0x01,1,0x00 };
                comm.Write(stop, 0, stop.Length);
            }
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            if (comm.IsOpen)
            {
                lb_thr.Text = "Throttle:" + trackBar1.Value * 10 + "%";
                comm.Write(start_mark, 0, start_mark.Length);
                Byte[] thr = { 0x01,1,(Byte)trackBar1.Value };
                //Byte[] thr = { 5 };
                comm.Write(thr, 0, thr.Length);
                Trace.WriteLine(lb_thr.Text);
            }
            else
            {
                trackBar1.Value = 0;
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (comm.IsOpen)
            {
                float P, D;
                P = float.Parse(textP.Text);
                D = float.Parse(textD.Text);
                byte[] pBytes = BitConverter.GetBytes(P);
                byte[] dBytes = BitConverter.GetBytes(D);
                Byte[] setP = { 0x02 };
                Byte[] setD = { 0x03 };
                Byte[] cmdLen = { 4 };
                comm.Write(start_mark, 0, start_mark.Length);
                comm.Write(setP, 0, 1);
                comm.Write(cmdLen, 0, cmdLen.Length);
                comm.Write(pBytes, 0, pBytes.Length);

                comm.Write(start_mark, 0, start_mark.Length);
                comm.Write(setD, 0, 1);
                comm.Write(cmdLen, 0, cmdLen.Length);
                comm.Write(dBytes, 0, dBytes.Length);
            }
        }
    }
}
