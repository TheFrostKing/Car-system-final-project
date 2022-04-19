using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Car_System
{
    public partial class Form1 : Form
    {
        bool isItOn = false;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // Set up the serial port.
            serialPort.PortName = "COM5";
            serialPort.DtrEnable = true; // For Arduino Leonardo
            serialPort.Open();
            // Set up the timers.
            timer.Start();
           
        }

      
        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            // Close the timers.
            timer.Stop();
            timerAnimate.Stop();
            // Release the serial port.
            serialPort.Close();
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            if(serialPort.BytesToRead>0)
            {
                string message = serialPort.ReadLine();
                if (message.Trim()=="HdlON")
                {
                    txtHeadlights.Text = message.Remove(0,3);
                    lsbBlackBox.Items.Add("Lights: " + message.Remove(0, 3));
                    Refresh();
                }
                if (message.Trim() == "HdlOFF")
                {
                    txtHeadlights.Text = message.Remove(0, 3);
                    lsbBlackBox.Items.Add("Lights: " + message.Remove(0,3));
                    Refresh();
                }
                if (message.Trim().StartsWith("T"))
                {
                    
                    lsbBlackBox.Items.Add(message+" C");
                    txtTemp.Text= message.Remove(0, 5)+" C";
                    Refresh();
                }
                if (message.Trim()=="Left")
                {
                    
                    lsbBlackBox.Items.Add(message);
                    Refresh();
                }
                if (message.Trim() == "Right")
                {
                    lsbBlackBox.Items.Add(message);
                    Refresh();
                }
            }
        }
        private void btnHazard_Click(object sender, EventArgs e)
        {
            if (!isItOn)
            {
                timerAnimate.Start();
                isItOn = true;
                serialPort.Write("HAZARD\n");
                lsbBlackBox.Items.Add("Hazard");
                Refresh();
            }
            else
            {
                timerAnimate.Stop();
                btnHazard.BackColor = Color.Gray;
                isItOn = false;
                serialPort.Write("NORMAL\n");
                lsbBlackBox.Items.Add("Normal");
                Refresh();
            }
        }

        private void timerAnimate_Tick(object sender, EventArgs e)
        {
            if (btnHazard.BackColor == Color.Gray)
            {
                btnHazard.BackColor = Color.Red;
            }
            else
            {
                btnHazard.BackColor = Color.Gray;
            }
        }
    }
}
