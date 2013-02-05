namespace uart_cam
{
    partial class mainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.comboPortName = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.lb_ax = new System.Windows.Forms.Label();
            this.lb_ay = new System.Windows.Forms.Label();
            this.lb_az = new System.Windows.Forms.Label();
            this.lb_gz = new System.Windows.Forms.Label();
            this.lb_gy = new System.Windows.Forms.Label();
            this.lb_gx = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.lb_mz = new System.Windows.Forms.Label();
            this.lb_my = new System.Windows.Forms.Label();
            this.lb_mx = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.lb_roll = new System.Windows.Forms.Label();
            this.lb_pitch = new System.Windows.Forms.Label();
            this.lb_yaw = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.button2 = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.lb_fps = new System.Windows.Forms.Label();
            this.lb_hlt = new System.Windows.Forms.Label();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.progressBar2 = new System.Windows.Forms.ProgressBar();
            this.progressBar3 = new System.Windows.Forms.ProgressBar();
            this.openGLControl1 = new SharpGL.OpenGLControl();
            ((System.ComponentModel.ISupportInitialize)(this.openGLControl1)).BeginInit();
            this.SuspendLayout();
            // 
            // comboPortName
            // 
            this.comboPortName.FormattingEnabled = true;
            this.comboPortName.Location = new System.Drawing.Point(75, 158);
            this.comboPortName.Name = "comboPortName";
            this.comboPortName.Size = new System.Drawing.Size(79, 21);
            this.comboPortName.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(14, 161);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(55, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Serial Port";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(160, 150);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(79, 34);
            this.button1.TabIndex = 3;
            this.button1.Text = "Open";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(14, 62);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(34, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Accel";
            // 
            // lb_ax
            // 
            this.lb_ax.AutoSize = true;
            this.lb_ax.Location = new System.Drawing.Point(55, 62);
            this.lb_ax.Name = "lb_ax";
            this.lb_ax.Size = new System.Drawing.Size(22, 13);
            this.lb_ax.TabIndex = 5;
            this.lb_ax.Text = "0.0";
            // 
            // lb_ay
            // 
            this.lb_ay.AutoSize = true;
            this.lb_ay.Location = new System.Drawing.Point(97, 62);
            this.lb_ay.Name = "lb_ay";
            this.lb_ay.Size = new System.Drawing.Size(22, 13);
            this.lb_ay.TabIndex = 6;
            this.lb_ay.Text = "0.0";
            // 
            // lb_az
            // 
            this.lb_az.AutoSize = true;
            this.lb_az.Location = new System.Drawing.Point(139, 62);
            this.lb_az.Name = "lb_az";
            this.lb_az.Size = new System.Drawing.Size(22, 13);
            this.lb_az.TabIndex = 7;
            this.lb_az.Text = "0.0";
            // 
            // lb_gz
            // 
            this.lb_gz.AutoSize = true;
            this.lb_gz.Location = new System.Drawing.Point(139, 87);
            this.lb_gz.Name = "lb_gz";
            this.lb_gz.Size = new System.Drawing.Size(22, 13);
            this.lb_gz.TabIndex = 11;
            this.lb_gz.Text = "0.0";
            // 
            // lb_gy
            // 
            this.lb_gy.AutoSize = true;
            this.lb_gy.Location = new System.Drawing.Point(97, 87);
            this.lb_gy.Name = "lb_gy";
            this.lb_gy.Size = new System.Drawing.Size(22, 13);
            this.lb_gy.TabIndex = 10;
            this.lb_gy.Text = "0.0";
            // 
            // lb_gx
            // 
            this.lb_gx.AutoSize = true;
            this.lb_gx.Location = new System.Drawing.Point(55, 87);
            this.lb_gx.Name = "lb_gx";
            this.lb_gx.Size = new System.Drawing.Size(22, 13);
            this.lb_gx.TabIndex = 9;
            this.lb_gx.Text = "0.0";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(14, 87);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(29, 13);
            this.label6.TabIndex = 8;
            this.label6.Text = "Gryo";
            // 
            // lb_mz
            // 
            this.lb_mz.AutoSize = true;
            this.lb_mz.Location = new System.Drawing.Point(139, 111);
            this.lb_mz.Name = "lb_mz";
            this.lb_mz.Size = new System.Drawing.Size(22, 13);
            this.lb_mz.TabIndex = 15;
            this.lb_mz.Text = "0.0";
            // 
            // lb_my
            // 
            this.lb_my.AutoSize = true;
            this.lb_my.Location = new System.Drawing.Point(97, 111);
            this.lb_my.Name = "lb_my";
            this.lb_my.Size = new System.Drawing.Size(22, 13);
            this.lb_my.TabIndex = 14;
            this.lb_my.Text = "0.0";
            // 
            // lb_mx
            // 
            this.lb_mx.AutoSize = true;
            this.lb_mx.Location = new System.Drawing.Point(55, 111);
            this.lb_mx.Name = "lb_mx";
            this.lb_mx.Size = new System.Drawing.Size(22, 13);
            this.lb_mx.TabIndex = 13;
            this.lb_mx.Text = "0.0";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(14, 111);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(36, 13);
            this.label10.TabIndex = 12;
            this.label10.Text = "Magni";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(139, 36);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(15, 13);
            this.label11.TabIndex = 18;
            this.label11.Text = " z";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(97, 36);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(15, 13);
            this.label12.TabIndex = 17;
            this.label12.Text = " y";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(55, 36);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(15, 13);
            this.label13.TabIndex = 16;
            this.label13.Text = " x";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(289, 55);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(21, 20);
            this.label3.TabIndex = 24;
            this.label3.Text = " z";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(241, 55);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(20, 20);
            this.label4.TabIndex = 23;
            this.label4.Text = " y";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(193, 55);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(20, 20);
            this.label5.TabIndex = 22;
            this.label5.Text = " x";
            // 
            // lb_roll
            // 
            this.lb_roll.AutoSize = true;
            this.lb_roll.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lb_roll.Location = new System.Drawing.Point(289, 81);
            this.lb_roll.Name = "lb_roll";
            this.lb_roll.Size = new System.Drawing.Size(31, 20);
            this.lb_roll.TabIndex = 21;
            this.lb_roll.Text = "0.0";
            // 
            // lb_pitch
            // 
            this.lb_pitch.AutoSize = true;
            this.lb_pitch.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lb_pitch.Location = new System.Drawing.Point(241, 81);
            this.lb_pitch.Name = "lb_pitch";
            this.lb_pitch.Size = new System.Drawing.Size(31, 20);
            this.lb_pitch.TabIndex = 20;
            this.lb_pitch.Text = "0.0";
            // 
            // lb_yaw
            // 
            this.lb_yaw.AutoSize = true;
            this.lb_yaw.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lb_yaw.Location = new System.Drawing.Point(193, 81);
            this.lb_yaw.Name = "lb_yaw";
            this.lb_yaw.Size = new System.Drawing.Size(31, 20);
            this.lb_yaw.TabIndex = 19;
            this.lb_yaw.Text = "0.0";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label14.Location = new System.Drawing.Point(205, 9);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(107, 20);
            this.label14.TabIndex = 25;
            this.label14.Text = "Fusion Result";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label15.Location = new System.Drawing.Point(54, 9);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(110, 20);
            this.label15.TabIndex = 26;
            this.label15.Text = "Sensor Result";
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(245, 150);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(79, 34);
            this.button2.TabIndex = 27;
            this.button2.Text = "3D View";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 1000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // lb_fps
            // 
            this.lb_fps.AutoSize = true;
            this.lb_fps.Location = new System.Drawing.Point(17, 181);
            this.lb_fps.Name = "lb_fps";
            this.lb_fps.Size = new System.Drawing.Size(30, 13);
            this.lb_fps.TabIndex = 28;
            this.lb_fps.Text = "FPS:";
            // 
            // lb_hlt
            // 
            this.lb_hlt.AutoSize = true;
            this.lb_hlt.Location = new System.Drawing.Point(160, 186);
            this.lb_hlt.Name = "lb_hlt";
            this.lb_hlt.Size = new System.Drawing.Size(0, 13);
            this.lb_hlt.TabIndex = 29;
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(17, 221);
            this.progressBar1.MarqueeAnimationSpeed = 1;
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(307, 23);
            this.progressBar1.Step = 1;
            this.progressBar1.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.progressBar1.TabIndex = 30;
            // 
            // progressBar2
            // 
            this.progressBar2.Location = new System.Drawing.Point(17, 263);
            this.progressBar2.MarqueeAnimationSpeed = 1;
            this.progressBar2.Name = "progressBar2";
            this.progressBar2.Size = new System.Drawing.Size(307, 23);
            this.progressBar2.Step = 1;
            this.progressBar2.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.progressBar2.TabIndex = 31;
            // 
            // progressBar3
            // 
            this.progressBar3.Location = new System.Drawing.Point(17, 303);
            this.progressBar3.MarqueeAnimationSpeed = 1;
            this.progressBar3.Name = "progressBar3";
            this.progressBar3.Size = new System.Drawing.Size(307, 23);
            this.progressBar3.Step = 1;
            this.progressBar3.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.progressBar3.TabIndex = 32;
            // 
            // openGLControl1
            // 
            this.openGLControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.openGLControl1.BitDepth = 24;
            this.openGLControl1.DrawFPS = false;
            this.openGLControl1.FrameRate = 28;
            this.openGLControl1.Location = new System.Drawing.Point(343, 12);
            this.openGLControl1.Name = "openGLControl1";
            this.openGLControl1.RenderContextType = SharpGL.RenderContextType.DIBSection;
            this.openGLControl1.Size = new System.Drawing.Size(399, 314);
            this.openGLControl1.TabIndex = 33;
            this.openGLControl1.OpenGLDraw += new System.Windows.Forms.PaintEventHandler(this.openGLControl1_OpenGLDraw);
            // 
            // mainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(754, 339);
            this.Controls.Add(this.openGLControl1);
            this.Controls.Add(this.progressBar3);
            this.Controls.Add(this.progressBar2);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.lb_hlt);
            this.Controls.Add(this.lb_fps);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.label15);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.lb_roll);
            this.Controls.Add(this.lb_pitch);
            this.Controls.Add(this.lb_yaw);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.lb_mz);
            this.Controls.Add(this.lb_my);
            this.Controls.Add(this.lb_mx);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.lb_gz);
            this.Controls.Add(this.lb_gy);
            this.Controls.Add(this.lb_gx);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.lb_az);
            this.Controls.Add(this.lb_ay);
            this.Controls.Add(this.lb_ax);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.comboPortName);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "mainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "AHRS Viewer";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.mainForm_FormClosing);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.mainForm_FormClosed);
            this.Load += new System.EventHandler(this.mainForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.openGLControl1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox comboPortName;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label lb_ax;
        private System.Windows.Forms.Label lb_ay;
        private System.Windows.Forms.Label lb_az;
        private System.Windows.Forms.Label lb_gz;
        private System.Windows.Forms.Label lb_gy;
        private System.Windows.Forms.Label lb_gx;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label lb_mz;
        private System.Windows.Forms.Label lb_my;
        private System.Windows.Forms.Label lb_mx;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label lb_roll;
        private System.Windows.Forms.Label lb_pitch;
        private System.Windows.Forms.Label lb_yaw;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Label lb_fps;
        private System.Windows.Forms.Label lb_hlt;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.ProgressBar progressBar2;
        private System.Windows.Forms.ProgressBar progressBar3;
        private SharpGL.OpenGLControl openGLControl1;
    }
}

