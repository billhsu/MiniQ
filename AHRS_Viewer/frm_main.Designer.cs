namespace ahrs_viewer
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
            this.lb_roll = new System.Windows.Forms.Label();
            this.lb_pitch = new System.Windows.Forms.Label();
            this.lb_yaw = new System.Windows.Forms.Label();
            this.button2 = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.lb_fps = new System.Windows.Forms.Label();
            this.lb_hlt = new System.Windows.Forms.Label();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.progressBar2 = new System.Windows.Forms.ProgressBar();
            this.progressBar3 = new System.Windows.Forms.ProgressBar();
            this.openGLControl1 = new SharpGL.OpenGLControl();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.timer2 = new System.Windows.Forms.Timer(this.components);
            this.button4 = new System.Windows.Forms.Button();
            this.trackBar1 = new System.Windows.Forms.TrackBar();
            this.lb_thr = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.btn_left = new System.Windows.Forms.Button();
            this.btn_backword = new System.Windows.Forms.Button();
            this.btn_right = new System.Windows.Forms.Button();
            this.btn_forward = new System.Windows.Forms.Button();
            this.textP = new System.Windows.Forms.TextBox();
            this.textD = new System.Windows.Forms.TextBox();
            this.button3 = new System.Windows.Forms.Button();
            this.textI = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.openGLControl1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).BeginInit();
            this.SuspendLayout();
            // 
            // comboPortName
            // 
            this.comboPortName.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.comboPortName.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.comboPortName.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.comboPortName.FormattingEnabled = true;
            this.comboPortName.Location = new System.Drawing.Point(77, 158);
            this.comboPortName.Name = "comboPortName";
            this.comboPortName.Size = new System.Drawing.Size(79, 21);
            this.comboPortName.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.label1.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.label1.Location = new System.Drawing.Point(12, 161);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(55, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Serial Port";
            // 
            // button1
            // 
            this.button1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button1.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.button1.Location = new System.Drawing.Point(162, 154);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(79, 26);
            this.button1.TabIndex = 3;
            this.button1.Text = "Open";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // lb_roll
            // 
            this.lb_roll.AutoSize = true;
            this.lb_roll.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.lb_roll.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lb_roll.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.lb_roll.Location = new System.Drawing.Point(295, 98);
            this.lb_roll.Name = "lb_roll";
            this.lb_roll.Size = new System.Drawing.Size(31, 20);
            this.lb_roll.TabIndex = 21;
            this.lb_roll.Text = "0.0";
            // 
            // lb_pitch
            // 
            this.lb_pitch.AutoSize = true;
            this.lb_pitch.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.lb_pitch.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lb_pitch.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.lb_pitch.Location = new System.Drawing.Point(295, 58);
            this.lb_pitch.Name = "lb_pitch";
            this.lb_pitch.Size = new System.Drawing.Size(31, 20);
            this.lb_pitch.TabIndex = 20;
            this.lb_pitch.Text = "0.0";
            // 
            // lb_yaw
            // 
            this.lb_yaw.AutoSize = true;
            this.lb_yaw.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.lb_yaw.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lb_yaw.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.lb_yaw.Location = new System.Drawing.Point(295, 16);
            this.lb_yaw.Name = "lb_yaw";
            this.lb_yaw.Size = new System.Drawing.Size(31, 20);
            this.lb_yaw.TabIndex = 19;
            this.lb_yaw.Text = "0.0";
            // 
            // button2
            // 
            this.button2.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.button2.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button2.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.button2.Location = new System.Drawing.Point(247, 154);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(79, 26);
            this.button2.TabIndex = 27;
            this.button2.Text = "Refresh Ports";
            this.button2.UseVisualStyleBackColor = false;
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
            this.lb_fps.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.lb_fps.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.lb_fps.Location = new System.Drawing.Point(9, 303);
            this.lb_fps.Name = "lb_fps";
            this.lb_fps.Size = new System.Drawing.Size(30, 13);
            this.lb_fps.TabIndex = 28;
            this.lb_fps.Text = "FPS:";
            // 
            // lb_hlt
            // 
            this.lb_hlt.AutoSize = true;
            this.lb_hlt.Location = new System.Drawing.Point(160, 171);
            this.lb_hlt.Name = "lb_hlt";
            this.lb_hlt.Size = new System.Drawing.Size(0, 13);
            this.lb_hlt.TabIndex = 29;
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(73, 13);
            this.progressBar1.MarqueeAnimationSpeed = 1;
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(212, 23);
            this.progressBar1.Step = 1;
            this.progressBar1.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.progressBar1.TabIndex = 30;
            // 
            // progressBar2
            // 
            this.progressBar2.Location = new System.Drawing.Point(73, 55);
            this.progressBar2.MarqueeAnimationSpeed = 1;
            this.progressBar2.Name = "progressBar2";
            this.progressBar2.Size = new System.Drawing.Size(212, 23);
            this.progressBar2.Step = 1;
            this.progressBar2.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.progressBar2.TabIndex = 31;
            // 
            // progressBar3
            // 
            this.progressBar3.Location = new System.Drawing.Point(73, 95);
            this.progressBar3.MarqueeAnimationSpeed = 1;
            this.progressBar3.Name = "progressBar3";
            this.progressBar3.Size = new System.Drawing.Size(212, 23);
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
            this.openGLControl1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.openGLControl1.DrawFPS = false;
            this.openGLControl1.ForeColor = System.Drawing.SystemColors.ControlText;
            this.openGLControl1.FrameRate = 30;
            this.openGLControl1.Location = new System.Drawing.Point(346, 16);
            this.openGLControl1.Name = "openGLControl1";
            this.openGLControl1.RenderContextType = SharpGL.RenderContextType.DIBSection;
            this.openGLControl1.Size = new System.Drawing.Size(356, 302);
            this.openGLControl1.TabIndex = 33;
            this.openGLControl1.OpenGLDraw += new System.Windows.Forms.PaintEventHandler(this.openGLControl1_OpenGLDraw);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.label7.Location = new System.Drawing.Point(11, 13);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(40, 20);
            this.label7.TabIndex = 34;
            this.label7.Text = "Yaw";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.label8.Location = new System.Drawing.Point(11, 58);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(44, 20);
            this.label8.TabIndex = 35;
            this.label8.Text = "Pitch";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.label9.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label9.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.label9.Location = new System.Drawing.Point(12, 98);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(36, 20);
            this.label9.TabIndex = 36;
            this.label9.Text = "Roll";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.label16.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.label16.Location = new System.Drawing.Point(353, 23);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(86, 13);
            this.label16.TabIndex = 38;
            this.label16.Text = "3D Attitude View";
            // 
            // timer2
            // 
            this.timer2.Enabled = true;
            this.timer2.Interval = 20;
            this.timer2.Tick += new System.EventHandler(this.timer2_Tick);
            // 
            // button4
            // 
            this.button4.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.button4.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button4.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.button4.Location = new System.Drawing.Point(12, 259);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(102, 25);
            this.button4.TabIndex = 41;
            this.button4.Text = "Stop Motor";
            this.button4.UseVisualStyleBackColor = false;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // trackBar1
            // 
            this.trackBar1.Location = new System.Drawing.Point(127, 212);
            this.trackBar1.Name = "trackBar1";
            this.trackBar1.Size = new System.Drawing.Size(199, 45);
            this.trackBar1.TabIndex = 42;
            this.trackBar1.Scroll += new System.EventHandler(this.trackBar1_Scroll);
            // 
            // lb_thr
            // 
            this.lb_thr.AutoSize = true;
            this.lb_thr.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.lb_thr.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.lb_thr.Location = new System.Drawing.Point(124, 196);
            this.lb_thr.Name = "lb_thr";
            this.lb_thr.Size = new System.Drawing.Size(60, 13);
            this.lb_thr.TabIndex = 43;
            this.lb_thr.Text = "Throttle:0%";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.label3.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.label3.Location = new System.Drawing.Point(134, 303);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(193, 13);
            this.label3.TabIndex = 44;
            this.label3.Text = "Shipeng Xu 2013        http://BillHsu.me";
            // 
            // btn_left
            // 
            this.btn_left.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btn_left.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.btn_left.Location = new System.Drawing.Point(12, 223);
            this.btn_left.Name = "btn_left";
            this.btn_left.Size = new System.Drawing.Size(30, 30);
            this.btn_left.TabIndex = 46;
            this.btn_left.Text = "←";
            this.btn_left.UseVisualStyleBackColor = true;
            // 
            // btn_backword
            // 
            this.btn_backword.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btn_backword.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.btn_backword.Location = new System.Drawing.Point(48, 223);
            this.btn_backword.Name = "btn_backword";
            this.btn_backword.Size = new System.Drawing.Size(30, 30);
            this.btn_backword.TabIndex = 47;
            this.btn_backword.Text = "↓";
            this.btn_backword.UseVisualStyleBackColor = true;
            // 
            // btn_right
            // 
            this.btn_right.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btn_right.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.btn_right.Location = new System.Drawing.Point(84, 223);
            this.btn_right.Name = "btn_right";
            this.btn_right.Size = new System.Drawing.Size(30, 30);
            this.btn_right.TabIndex = 48;
            this.btn_right.Text = "→";
            this.btn_right.UseVisualStyleBackColor = true;
            // 
            // btn_forward
            // 
            this.btn_forward.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btn_forward.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.btn_forward.Location = new System.Drawing.Point(48, 187);
            this.btn_forward.Name = "btn_forward";
            this.btn_forward.Size = new System.Drawing.Size(30, 30);
            this.btn_forward.TabIndex = 45;
            this.btn_forward.Text = "↑";
            this.btn_forward.UseVisualStyleBackColor = true;
            // 
            // textP
            // 
            this.textP.BackColor = System.Drawing.SystemColors.InfoText;
            this.textP.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textP.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.textP.Location = new System.Drawing.Point(127, 263);
            this.textP.Name = "textP";
            this.textP.Size = new System.Drawing.Size(33, 20);
            this.textP.TabIndex = 49;
            this.textP.Text = "0.0";
            // 
            // textD
            // 
            this.textD.BackColor = System.Drawing.SystemColors.InfoText;
            this.textD.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textD.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.textD.Location = new System.Drawing.Point(208, 263);
            this.textD.Name = "textD";
            this.textD.Size = new System.Drawing.Size(33, 20);
            this.textD.TabIndex = 50;
            this.textD.Text = "0.0";
            // 
            // button3
            // 
            this.button3.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button3.Location = new System.Drawing.Point(263, 261);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(63, 23);
            this.button3.TabIndex = 51;
            this.button3.Text = "Set PID";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // textI
            // 
            this.textI.BackColor = System.Drawing.SystemColors.InfoText;
            this.textI.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textI.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.textI.Location = new System.Drawing.Point(169, 263);
            this.textI.Name = "textI";
            this.textI.Size = new System.Drawing.Size(33, 20);
            this.textI.TabIndex = 52;
            this.textI.Text = "0.0";
            // 
            // mainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.ClientSize = new System.Drawing.Size(714, 327);
            this.Controls.Add(this.textI);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.textD);
            this.Controls.Add(this.textP);
            this.Controls.Add(this.btn_right);
            this.Controls.Add(this.btn_backword);
            this.Controls.Add(this.btn_left);
            this.Controls.Add(this.btn_forward);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.lb_thr);
            this.Controls.Add(this.trackBar1);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.label16);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.openGLControl1);
            this.Controls.Add(this.progressBar3);
            this.Controls.Add(this.progressBar2);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.lb_hlt);
            this.Controls.Add(this.lb_fps);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.lb_roll);
            this.Controls.Add(this.lb_pitch);
            this.Controls.Add(this.lb_yaw);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.comboPortName);
            this.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "mainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "MiniQ Control";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.mainForm_FormClosing);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.mainForm_FormClosed);
            this.Load += new System.EventHandler(this.mainForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.openGLControl1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox comboPortName;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label lb_roll;
        private System.Windows.Forms.Label lb_pitch;
        private System.Windows.Forms.Label lb_yaw;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Label lb_fps;
        private System.Windows.Forms.Label lb_hlt;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.ProgressBar progressBar2;
        private System.Windows.Forms.ProgressBar progressBar3;
        private SharpGL.OpenGLControl openGLControl1;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Timer timer2;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.TrackBar trackBar1;
        private System.Windows.Forms.Label lb_thr;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button btn_left;
        private System.Windows.Forms.Button btn_backword;
        private System.Windows.Forms.Button btn_right;
        private System.Windows.Forms.Button btn_forward;
        private System.Windows.Forms.TextBox textP;
        private System.Windows.Forms.TextBox textD;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.TextBox textI;
    }
}

