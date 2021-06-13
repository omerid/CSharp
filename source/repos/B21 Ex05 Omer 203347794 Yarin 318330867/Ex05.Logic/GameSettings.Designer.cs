namespace Ex05.Logic
{
    partial class GameSettings
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
            this.PlayersLable = new System.Windows.Forms.Label();
            this.Player1Lable = new System.Windows.Forms.Label();
            this.Player1TextBox = new System.Windows.Forms.TextBox();
            this.Player2CheckBox = new System.Windows.Forms.CheckBox();
            this.Player2TextBox = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // PlayersLable
            // 
            this.PlayersLable.AutoSize = true;
            this.PlayersLable.Location = new System.Drawing.Point(23, 9);
            this.PlayersLable.Name = "PlayersLable";
            this.PlayersLable.Size = new System.Drawing.Size(44, 13);
            this.PlayersLable.TabIndex = 0;
            this.PlayersLable.Text = "Players:";
            // 
            // Player1Lable
            // 
            this.Player1Lable.AutoSize = true;
            this.Player1Lable.Location = new System.Drawing.Point(55, 38);
            this.Player1Lable.Name = "Player1Lable";
            this.Player1Lable.Size = new System.Drawing.Size(48, 13);
            this.Player1Lable.TabIndex = 1;
            this.Player1Lable.Text = "Player 1:";
            // 
            // Player1TextBox
            // 
            this.Player1TextBox.Location = new System.Drawing.Point(134, 35);
            this.Player1TextBox.Name = "Player1TextBox";
            this.Player1TextBox.Size = new System.Drawing.Size(116, 20);
            this.Player1TextBox.TabIndex = 2;
            // 
            // Player2CheckBox
            // 
            this.Player2CheckBox.AutoSize = true;
            this.Player2CheckBox.Location = new System.Drawing.Point(58, 69);
            this.Player2CheckBox.Name = "Player2CheckBox";
            this.Player2CheckBox.Size = new System.Drawing.Size(67, 17);
            this.Player2CheckBox.TabIndex = 3;
            this.Player2CheckBox.Text = "Player 2:";
            this.Player2CheckBox.UseVisualStyleBackColor = true;
            this.Player2CheckBox.CheckedChanged += new System.EventHandler(this.Player2CheckBox_CheckedChanged);
            // 
            // Player2TextBox
            // 
            this.Player2TextBox.Enabled = false;
            this.Player2TextBox.Location = new System.Drawing.Point(134, 66);
            this.Player2TextBox.Name = "Player2TextBox";
            this.Player2TextBox.Size = new System.Drawing.Size(116, 20);
            this.Player2TextBox.TabIndex = 4;
            // 
            // GameSettings
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(291, 270);
            this.Controls.Add(this.Player2TextBox);
            this.Controls.Add(this.Player2CheckBox);
            this.Controls.Add(this.Player1TextBox);
            this.Controls.Add(this.Player1Lable);
            this.Controls.Add(this.PlayersLable);
            this.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "GameSettings";
            this.Text = "Game Settings";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label PlayersLable;
        private System.Windows.Forms.Label Player1Lable;
        private System.Windows.Forms.TextBox Player1TextBox;
        private System.Windows.Forms.CheckBox Player2CheckBox;
        private System.Windows.Forms.TextBox Player2TextBox;
    }
}