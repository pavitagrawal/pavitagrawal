using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            String id = textBox1.Text;
            String pass = textBox2.Text;

            if (id == "230953406" && pass == "123456")
            {
                if (radioButton1.Checked || radioButton2.Checked)
                {
                    if (checkBox1.Checked || checkBox2.Checked || checkBox3.Checked)
                    {
                        if (dateTimePicker1.Checked)
                        {
                            MessageBox.Show("Login Successful");
                        }
                        else
                        {
                            MessageBox.Show("Date of Joining is required");
                        }
                    }
                    else
                    {
                        MessageBox.Show("Facilities is required");
                    }
                }
                else
                {
                    MessageBox.Show("Invalid User");
                }
            }
            else
            {
                MessageBox.Show("Invalid User");
            }
            Form2 f2 = new Form2();
            f2.Show();
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void label6_Click(object sender, EventArgs e)
        {

        }
    }
}
