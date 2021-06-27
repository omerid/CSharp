using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Ex05.WindowsUI
{
    public partial class FormGameSettings : Form
    {
        public FormGameSettings()
        {
            InitializeComponent();
        }

        public string Player1Name
        {
            get { return Player1TextBox.Text; }
        }

        public string Player2Name
        {
            get { return Player2TextBox.Text; }
        }

        public int BoardSize
        {
            get { return (int)numericUpDown1.Value; }
        }

        private void player2CheckBox_CheckedChanged(object sender, EventArgs e)
        {
            Player2TextBox.Enabled = Player2TextBox.Enabled == true ? false : true;
            if(Player2TextBox.Enabled == true)
            {
                Player2TextBox.BackColor = Color.White;
                Player2TextBox.Text = String.Empty;
            }
            else
            {
                Player2TextBox.BackColor = System.Drawing.SystemColors.Control;
                Player2TextBox.Text = "[Computer]";
            }
        }

        private void buttonStart_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(Player1TextBox.Text) && string.IsNullOrEmpty(Player2TextBox.Text))
            {
                MessageBox.Show("Please fill all fields", "Error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else if (string.IsNullOrEmpty(Player1TextBox.Text))
            {
                MessageBox.Show("Please fill player 1 name", "Error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else if (string.IsNullOrEmpty(Player2TextBox.Text))
            {
                MessageBox.Show("Please fill player 2 name", "Error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else
            {
                this.DialogResult = DialogResult.OK;
                this.Close();
            }
        }

        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            numericUpDown2.Value = numericUpDown1.Value;
        }

        private void numericUpDown2_ValueChanged(object sender, EventArgs e)
        {
            numericUpDown1.Value = numericUpDown2.Value;
        }
    }
}
