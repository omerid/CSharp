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
    public partial class FormGame : Form
    {
        private const int k_TicTacTowButtonSize = 50;
        private readonly Button[,] r_GameBoardButtons;
        public EventHandler AfterClick;

        public FormGame(int i_BoardSize)
        {
            InitializeComponent();
            r_GameBoardButtons = new Button[i_BoardSize, i_BoardSize];
            initialForm(i_BoardSize);
        }

        public string Player1Name
        {
            get { return Player1Label.Text; }
            set { Player1Label.Text = value; }
        }

        public string Player1Score
        {
            get { return Player1ScoreLabel.Text; }
            set { Player1ScoreLabel.Text = value; }
        }

        public string Player2Name
        {
            get { return Player2Label.Text; }
            set { Player2Label.Text = value; }
        }

        public string Player2Score
        {
            get { return Player2ScoreLabel.Text; }
            set { Player2ScoreLabel.Text = value; }
        }


        private void initialForm(int i_BoardSize)
        {
            this.Size = new Size(i_BoardSize * k_TicTacTowButtonSize + 50 , i_BoardSize * k_TicTacTowButtonSize + 90);

            for (int row = 0; row < i_BoardSize; row++)
            {
                for (int col = 0; col < i_BoardSize; col++)
                {
                    Button gameBoardButton = createAndInitialNewBoardButton(row, col);
                    gameBoardButton.TabStop = false;
                    Controls.Add(gameBoardButton);
                    r_GameBoardButtons[row, col] = gameBoardButton;
                }
            }
        }

        private Button createAndInitialNewBoardButton(int row, int col)
        {
            Button gameBoardButton = new Button();
            gameBoardButton.Size = new Size(k_TicTacTowButtonSize, k_TicTacTowButtonSize);
            gameBoardButton.Location = new Point(col * k_TicTacTowButtonSize + 13, row * k_TicTacTowButtonSize + 12);
            //newButtonToReturn.BackColor = Color.Gray;
            gameBoardButton.Enabled = true;
            gameBoardButton.Click += new EventHandler(gameBoardButton_Click);
            return gameBoardButton;
        }

        public void SetGameFormLablesAndTheirSize(string i_Player1Name, string i_Player2Name)
        {
            this.Player1Label.Location = new Point(this.Size.Width / 2 - k_TicTacTowButtonSize, this.ClientSize.Height - 25);

            this.Player1ScoreLabel.Left = this.Player1Label.Right;
            this.Player1ScoreLabel.Left -= 15;
            this.Player1ScoreLabel.Top = Player1Label.Top;

            this.Player2Label.Left = Player1ScoreLabel.Right;
            this.Player2Label.Top = Player1ScoreLabel.Top;

            this.Player2ScoreLabel.Left = Player2Label.Right + 3;
            this.Player2ScoreLabel.Top = Player2Label.Top;

            this.Player1Label.Text = string.Format($"{i_Player1Name}:");
            this.Player2Label.Text = string.Format($"{i_Player2Name}:");
        }

        private void gameBoardButton_Click(object sender, EventArgs e)
        {
            Button gameBoardButton = sender as Button;
            
            if (gameBoardButton != null)
            {
                if(gameBoardButton.Enabled == true)
                {
                    gameBoardButton.Enabled = false;
                    AfterClick(gameBoardButton, r_GameBoardButtons.index);
                }
            }
        }


    }
}
