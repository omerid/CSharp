namespace Ex05.WindowsUI
{
    partial class FormGameSettings
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
            this.BoardSizeLable = new System.Windows.Forms.Label();
            this.numericUpDown1 = new System.Windows.Forms.NumericUpDown();
            this.RowsLable = new System.Windows.Forms.Label();
            this.ColsLable = new System.Windows.Forms.Label();
            this.numericUpDown2 = new System.Windows.Forms.NumericUpDown();
            this.ButtonStart = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown2)).BeginInit();
            this.SuspendLayout();
            // 
            // PlayersLable
            // 
            this.PlayersLable.AutoSize = true;
            this.PlayersLable.Location = new System.Drawing.Point(14, 9);
            this.PlayersLable.Name = "PlayersLable";
            this.PlayersLable.Size = new System.Drawing.Size(44, 13);
            this.PlayersLable.TabIndex = 0;
            this.PlayersLable.Text = "Players:";
            // 
            // Player1Lable
            // 
            this.Player1Lable.AutoSize = true;
            this.Player1Lable.Location = new System.Drawing.Point(29, 38);
            this.Player1Lable.Name = "Player1Lable";
            this.Player1Lable.Size = new System.Drawing.Size(48, 13);
            this.Player1Lable.TabIndex = 1;
            this.Player1Lable.Text = "Player 1:";
            // 
            // Player1TextBox
            // 
            this.Player1TextBox.Location = new System.Drawing.Point(108, 35);
            this.Player1TextBox.Name = "Player1TextBox";
            this.Player1TextBox.Size = new System.Drawing.Size(116, 20);
            this.Player1TextBox.TabIndex = 2;
            // 
            // Player2CheckBox
            // 
            this.Player2CheckBox.AutoSize = true;
            this.Player2CheckBox.Location = new System.Drawing.Point(32, 68);
            this.Player2CheckBox.Name = "Player2CheckBox";
            this.Player2CheckBox.Size = new System.Drawing.Size(67, 17);
            this.Player2CheckBox.TabIndex = 3;
            this.Player2CheckBox.Text = "Player 2:";
            this.Player2CheckBox.UseVisualStyleBackColor = true;
            this.Player2CheckBox.CheckedChanged += new System.EventHandler(this.player2CheckBox_CheckedChanged);
            // 
            // Player2TextBox
            // 
            this.Player2TextBox.Enabled = false;
            this.Player2TextBox.Location = new System.Drawing.Point(108, 66);
            this.Player2TextBox.Name = "Player2TextBox";
            this.Player2TextBox.Size = new System.Drawing.Size(116, 20);
            this.Player2TextBox.TabIndex = 4;
            this.Player2TextBox.Text = "[Computer]";
            // 
            // BoardSizeLable
            // 
            this.BoardSizeLable.AutoSize = true;
            this.BoardSizeLable.Location = new System.Drawing.Point(17, 114);
            this.BoardSizeLable.Name = "BoardSizeLable";
            this.BoardSizeLable.Size = new System.Drawing.Size(61, 13);
            this.BoardSizeLable.TabIndex = 5;
            this.BoardSizeLable.Text = "Board Size:";
            // 
            // numericUpDown1
            // 
            this.numericUpDown1.Location = new System.Drawing.Point(76, 143);
            this.numericUpDown1.Maximum = new decimal(new int[] {
            9,
            0,
            0,
            0});
            this.numericUpDown1.Minimum = new decimal(new int[] {
            3,
            0,
            0,
            0});
            this.numericUpDown1.Name = "numericUpDown1";
            this.numericUpDown1.Size = new System.Drawing.Size(35, 20);
            this.numericUpDown1.TabIndex = 6;
            this.numericUpDown1.Value = new decimal(new int[] {
            3,
            0,
            0,
            0});
            this.numericUpDown1.ValueChanged += new System.EventHandler(this.numericUpDown1_ValueChanged);
            // 
            // RowsLable
            // 
            this.RowsLable.AutoSize = true;
            this.RowsLable.Location = new System.Drawing.Point(35, 145);
            this.RowsLable.Name = "RowsLable";
            this.RowsLable.Size = new System.Drawing.Size(37, 13);
            this.RowsLable.TabIndex = 7;
            this.RowsLable.Text = "Rows:";
            // 
            // ColsLable
            // 
            this.ColsLable.AutoSize = true;
            this.ColsLable.Location = new System.Drawing.Point(135, 145);
            this.ColsLable.Name = "ColsLable";
            this.ColsLable.Size = new System.Drawing.Size(30, 13);
            this.ColsLable.TabIndex = 9;
            this.ColsLable.Text = "Cols:";
            // 
            // numericUpDown2
            // 
            this.numericUpDown2.Location = new System.Drawing.Point(169, 143);
            this.numericUpDown2.Maximum = new decimal(new int[] {
            9,
            0,
            0,
            0});
            this.numericUpDown2.Minimum = new decimal(new int[] {
            3,
            0,
            0,
            0});
            this.numericUpDown2.Name = "numericUpDown2";
            this.numericUpDown2.Size = new System.Drawing.Size(35, 20);
            this.numericUpDown2.TabIndex = 8;
            this.numericUpDown2.Value = new decimal(new int[] {
            3,
            0,
            0,
            0});
            this.numericUpDown2.ValueChanged += new System.EventHandler(this.numericUpDown2_ValueChanged);
            // 
            // ButtonStart
            // 
            this.ButtonStart.AutoSize = true;
            this.ButtonStart.FlatAppearance.BorderSize = 10;
            this.ButtonStart.Location = new System.Drawing.Point(28, 183);
            this.ButtonStart.Name = "ButtonStart";
            this.ButtonStart.Size = new System.Drawing.Size(192, 24);
            this.ButtonStart.TabIndex = 10;
            this.ButtonStart.Text = "Start!";
            this.ButtonStart.UseVisualStyleBackColor = true;
            this.ButtonStart.Click += new System.EventHandler(this.buttonStart_Click);
            // 
            // FormGameSettings
            // 
            this.AccessibleDescription = "Game Settings";
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.ClientSize = new System.Drawing.Size(250, 219);
            this.Controls.Add(this.ButtonStart);
            this.Controls.Add(this.ColsLable);
            this.Controls.Add(this.numericUpDown2);
            this.Controls.Add(this.RowsLable);
            this.Controls.Add(this.numericUpDown1);
            this.Controls.Add(this.BoardSizeLable);
            this.Controls.Add(this.Player2TextBox);
            this.Controls.Add(this.Player2CheckBox);
            this.Controls.Add(this.Player1TextBox);
            this.Controls.Add(this.Player1Lable);
            this.Controls.Add(this.PlayersLable);
            this.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "FormGameSettings";
            this.Text = "Game Settings";
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown2)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label PlayersLable;
        private System.Windows.Forms.Label Player1Lable;
        private System.Windows.Forms.TextBox Player1TextBox;
        private System.Windows.Forms.CheckBox Player2CheckBox;
        private System.Windows.Forms.TextBox Player2TextBox;
        private System.Windows.Forms.Label BoardSizeLable;
        private System.Windows.Forms.NumericUpDown numericUpDown1;
        private System.Windows.Forms.Label RowsLable;
        private System.Windows.Forms.Label ColsLable;
        private System.Windows.Forms.NumericUpDown numericUpDown2;
        private System.Windows.Forms.Button ButtonStart;
    }
}