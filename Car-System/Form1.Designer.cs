
namespace Car_System
{
    partial class Form1
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
            this.serialPort = new System.IO.Ports.SerialPort(this.components);
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.btnHazard = new System.Windows.Forms.Button();
            this.lsbBlackBox = new System.Windows.Forms.ListBox();
            this.txtTemp = new System.Windows.Forms.TextBox();
            this.txtHeadlights = new System.Windows.Forms.TextBox();
            this.lblTemp = new System.Windows.Forms.Label();
            this.lblHeadlights = new System.Windows.Forms.Label();
            this.timerAnimate = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // serialPort
            // 
            this.serialPort.PortName = "COM5";
            // 
            // timer
            // 
            this.timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // btnHazard
            // 
            this.btnHazard.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.btnHazard.Location = new System.Drawing.Point(39, 46);
            this.btnHazard.Name = "btnHazard";
            this.btnHazard.Size = new System.Drawing.Size(104, 64);
            this.btnHazard.TabIndex = 0;
            this.btnHazard.Text = "HAZARD";
            this.btnHazard.UseVisualStyleBackColor = false;
            this.btnHazard.BackColorChanged += new System.EventHandler(this.timer_Tick);
            this.btnHazard.Click += new System.EventHandler(this.btnHazard_Click);
            // 
            // lsbBlackBox
            // 
            this.lsbBlackBox.FormattingEnabled = true;
            this.lsbBlackBox.Location = new System.Drawing.Point(553, 55);
            this.lsbBlackBox.Name = "lsbBlackBox";
            this.lsbBlackBox.Size = new System.Drawing.Size(147, 277);
            this.lsbBlackBox.TabIndex = 1;
            // 
            // txtTemp
            // 
            this.txtTemp.Location = new System.Drawing.Point(344, 122);
            this.txtTemp.Name = "txtTemp";
            this.txtTemp.Size = new System.Drawing.Size(100, 20);
            this.txtTemp.TabIndex = 2;
            // 
            // txtHeadlights
            // 
            this.txtHeadlights.Location = new System.Drawing.Point(344, 184);
            this.txtHeadlights.Name = "txtHeadlights";
            this.txtHeadlights.Size = new System.Drawing.Size(100, 20);
            this.txtHeadlights.TabIndex = 3;
            // 
            // lblTemp
            // 
            this.lblTemp.AutoSize = true;
            this.lblTemp.Location = new System.Drawing.Point(282, 122);
            this.lblTemp.Name = "lblTemp";
            this.lblTemp.Size = new System.Drawing.Size(34, 13);
            this.lblTemp.TabIndex = 4;
            this.lblTemp.Text = "Temp";
            // 
            // lblHeadlights
            // 
            this.lblHeadlights.AutoSize = true;
            this.lblHeadlights.Location = new System.Drawing.Point(259, 187);
            this.lblHeadlights.Name = "lblHeadlights";
            this.lblHeadlights.Size = new System.Drawing.Size(57, 13);
            this.lblHeadlights.TabIndex = 5;
            this.lblHeadlights.Text = "Headlights";
            // 
            // timerAnimate
            // 
            this.timerAnimate.Interval = 1000;
            this.timerAnimate.Tick += new System.EventHandler(this.timerAnimate_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.lblHeadlights);
            this.Controls.Add(this.lblTemp);
            this.Controls.Add(this.txtHeadlights);
            this.Controls.Add(this.txtTemp);
            this.Controls.Add(this.lsbBlackBox);
            this.Controls.Add(this.btnHazard);
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.IO.Ports.SerialPort serialPort;
        private System.Windows.Forms.Timer timer;
        private System.Windows.Forms.Button btnHazard;
        private System.Windows.Forms.ListBox lsbBlackBox;
        private System.Windows.Forms.TextBox txtTemp;
        private System.Windows.Forms.TextBox txtHeadlights;
        private System.Windows.Forms.Label lblTemp;
        private System.Windows.Forms.Label lblHeadlights;
        private System.Windows.Forms.Timer timerAnimate;
    }
}

