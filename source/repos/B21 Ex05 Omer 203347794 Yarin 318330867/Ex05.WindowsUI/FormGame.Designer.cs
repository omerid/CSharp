using System.Drawing;

namespace Ex05.WindowsUI
{
    partial class FormGame
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
            this.Player1ScoreLabel = new System.Windows.Forms.Label();
            this.Player2ScoreLabel = new System.Windows.Forms.Label();
            this.Player2Label = new System.Windows.Forms.Label();
            this.Player1Label = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // Player1ScoreLabel
            // 
            this.Player1ScoreLabel.AutoSize = true;
            //this.Player1ScoreLabel.Location = new System.Drawing.Point(324, 544);
            this.Player1ScoreLabel.Name = "Player1ScoreLabel";
            this.Player1ScoreLabel.Size = new System.Drawing.Size(13, 13);
            this.Player1ScoreLabel.TabIndex = 1;
            this.Player1ScoreLabel.Text = "0";
            // 
            // Player2ScoreLabel
            // 
            this.Player2ScoreLabel.AutoSize = true;
            //this.Player2ScoreLabel.Location = new System.Drawing.Point(390, 544);
            this.Player2ScoreLabel.Name = "Player2ScoreLabel";
            this.Player2ScoreLabel.Size = new System.Drawing.Size(13, 13);
            this.Player2ScoreLabel.TabIndex = 3;
            this.Player2ScoreLabel.Text = "0";
            // 
            // Player2Label
            // 
            this.Player2Label.AutoSize = true;
            //this.Player2Label.Location = new System.Drawing.Point(343, 544);
            this.Player2Label.Name = "Player2Label";
            this.Player2Label.Size = new System.Drawing.Size(48, 13);
            this.Player2Label.TabIndex = 2;
            this.Player2Label.Text = "Player 2:";
            // 
            // Player1Label
            // 
            this.Player1Label.AutoSize = true;
            //this.Player1Label.Location = new System.Drawing.Point(279, 544);
            this.Player1Label.Name = "Player1Label";
            this.Player1Label.Size = new System.Drawing.Size(48, 13);
            this.Player1Label.TabIndex = 0;
            this.Player1Label.Text = "Player 1:";
            // 
            // FormGame
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(682, 566);
            this.Controls.Add(this.Player1Label);
            this.Controls.Add(this.Player2ScoreLabel);
            this.Controls.Add(this.Player2Label);
            this.Controls.Add(this.Player1ScoreLabel);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.MaximizeBox = false;
            this.Name = "FormGame";
            this.Text = "TicTacToe ReveresMode";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Label Player1ScoreLabel;
        private System.Windows.Forms.Label Player2ScoreLabel;
        private System.Windows.Forms.Label Player2Label;
        private System.Windows.Forms.Label Player1Label;
    }
}