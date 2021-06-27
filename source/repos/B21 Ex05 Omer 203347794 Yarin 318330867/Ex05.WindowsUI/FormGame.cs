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

        public Button GetButtonByPoint(Point i_CellToChange)
        {
            return r_GameBoardButtons[i_CellToChange.X, i_CellToChange.Y];
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

        private Button createAndInitialNewBoardButton(int i_Row, int i_Col)
        {
            Button gameBoardButton = new Button();
            gameBoardButton.Size = new Size(k_TicTacTowButtonSize, k_TicTacTowButtonSize);
            gameBoardButton.Location = new Point(i_Col * k_TicTacTowButtonSize + 13, i_Row * k_TicTacTowButtonSize + 12);
            gameBoardButton.Tag = new Point(i_Row,i_Col);
            gameBoardButton.Enabled = true;
            gameBoardButton.Click += new EventHandler(gameBoardButton_Click);
            return gameBoardButton;
        }

        public void SetGameFormLablesAndTheirSize(string i_Player1Name, string i_Player2Name)
        {
            this.Player1Label.Location = new Point(this.ClientSize.Width / 2 - k_TicTacTowButtonSize - 10, this.ClientSize.Height - 25);

            this.Player1ScoreLabel.Left = this.Player1Label.Right;
            this.Player1ScoreLabel.Left -= 15;
            this.Player1ScoreLabel.Top = this.Player1Label.Top;
            this.Player1ScoreLabel.BringToFront();

            this.Player2Label.Left = this.Player1ScoreLabel.Right + 10;
            this.Player2Label.Top = this.Player1ScoreLabel.Top;

            this.Player2ScoreLabel.Left = this.Player2Label.Right + 5;
            this.Player2ScoreLabel.Top = this.Player2Label.Top;

            this.Player1Label.Text = string.Format($"{i_Player1Name}:");
            this.Player2Label.Text = string.Format($"{i_Player2Name}:");
        }

        private void gameBoardButton_Click(object sender, EventArgs e)
        {
            Button gameBoardButton = sender as Button;
            Point p = (Point)gameBoardButton.Tag;

            if (gameBoardButton != null)
            {
                if(gameBoardButton.Enabled == true)
                {
                    AfterClick(gameBoardButton, null);
                }
            }
        }

        public void UpdateScoreLables(int i_Player1Score, int i_Player2Score)
        {
            this.Player1ScoreLabel.Text = i_Player1Score.ToString();
            this.Player2ScoreLabel.Text = i_Player2Score.ToString();
        }

        public void ChangeButtonSignEnablementAndBold(Point i_CoordinateToChange, string i_Sign)
        {
            ChangeLableBold();
            Button ButtonToUpdate = GetButtonByPoint(i_CoordinateToChange);
            ButtonToUpdate.Text = i_Sign;
            ButtonToUpdate.Enabled = false;
        }

        public void ChangeLableBold()
        {
            if(Player1Label.Font.Bold == true)
            {
                this.Player2Label.Font = new Font(this.Player2Label.Font, FontStyle.Bold);
                this.Player2ScoreLabel.Font = new Font(this.Player2ScoreLabel.Font, FontStyle.Bold);
                this.Player1Label.Font = new Font(this.Player1Label.Font, FontStyle.Regular);
                this.Player1ScoreLabel.Font = new Font(this.Player1ScoreLabel.Font, FontStyle.Regular);
            }
            else
            {
                this.Player2Label.Font = new Font(this.Player2Label.Font, FontStyle.Regular);
                this.Player2ScoreLabel.Font = new Font(this.Player2ScoreLabel.Font, FontStyle.Regular);
                this.Player1Label.Font = new Font(this.Player1Label.Font, FontStyle.Bold);
                this.Player1ScoreLabel.Font = new Font(this.Player1ScoreLabel.Font, FontStyle.Bold);
            }
        }

        public void RestartTheBoard()
        {
            foreach (Button boardButton in r_GameBoardButtons)
            {
                boardButton.Text = "";
                boardButton.Enabled = true;
            }

            this.Player2Label.Font = new Font(this.Player2Label.Font, FontStyle.Regular);
            this.Player2ScoreLabel.Font = new Font(this.Player2ScoreLabel.Font, FontStyle.Regular);
            this.Player1Label.Font = new Font(this.Player1Label.Font, FontStyle.Bold);
            this.Player1ScoreLabel.Font = new Font(this.Player1ScoreLabel.Font, FontStyle.Bold);
        }
    }
}
