using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace Ex05.Logic
{
    public class TicTacToeRev
    {
        public enum eCurrentPlayer
        {
            PlayerOne = -1,
            PlayerTwo = 1
        }

        public EventHandler GameOperationAfterClick;

        private char m_UnSuccessfulTicTacToePattern;
        private bool m_HasGameFinishedWithWinner;
        private bool m_HasGameFinishedWithDraw;
        private bool m_HasGameFinishedWithRetirement;

        private Player m_PlayerOne;
        private Player m_PlayerTwo;
        private Board m_GameMatrix;

        private readonly eGameDefinition m_GameMode;
        private eCurrentPlayer m_CurrentTurn;

        public TicTacToeRev(int i_Size, string i_PlayerOneName, string i_PlayerTwoName, eGameDefinition i_GameMode)
        {
            m_PlayerOne = new Player(i_PlayerOneName, 'X');
            m_PlayerTwo = new Player(i_PlayerTwoName, 'O');
            m_GameMatrix = new Board(i_Size);
            this.m_GameMode = i_GameMode;
            InitialNewRound();
        }

        public int Size
        {
            get { return m_GameMatrix.Size; }
        }

        public eGameDefinition GameMode
        {
            get { return m_GameMode; }
        }

        public List<Player> Players
        {
            get
            {
                List<Player> playersListToReturn = new List<Player>
                {
                    m_PlayerOne,
                    m_PlayerTwo
                };
                return playersListToReturn;
            }
        }

        public char this[int row, int col]
        {
            get { return this.m_GameMatrix[row, col]; }
        }

        public Player CurrentPlayer
        {
            get
            {
                Player playerToReturn;
                if (m_CurrentTurn == eCurrentPlayer.PlayerOne)
                {
                    playerToReturn = m_PlayerOne;
                }
                else
                {
                    playerToReturn = m_PlayerTwo;
                }
                return playerToReturn;
            }
        }

        public Player NextPlayer
        {
            get
            {
                Player playerToReturn;
                if (m_CurrentTurn == eCurrentPlayer.PlayerOne)
                {
                    playerToReturn = m_PlayerTwo;
                }
                else
                {
                    playerToReturn = m_PlayerOne;
                }
                return playerToReturn;
            }
        }

        public string GetSignByIndex(int i_Row, int i_Col)
        {
            return m_GameMatrix[i_Row,i_Col].ToString(); 
        }

        public string Player1Name
        {
            get { return m_PlayerOne.Name; }
        }

        public string Player2Name
        {
            get { return m_PlayerTwo.Name; }
        }

        public void InitialNewRound()
        {
            m_GameMatrix.InitialBoard();
            m_HasGameFinishedWithWinner = false;
            m_HasGameFinishedWithDraw = false;
            m_HasGameFinishedWithRetirement = false;
            m_UnSuccessfulTicTacToePattern = 'D';
            m_CurrentTurn = eCurrentPlayer.PlayerOne;
        }

        public bool HasGameFinishedWithWinnerFlag
        {
            get { return m_HasGameFinishedWithWinner; }
        }

        public bool HasGameFinishedWithRetirementFlag
        {
            get { return m_HasGameFinishedWithRetirement; }
        }

        public bool HasGameFinishedWithDrawFlag
        {
            get { return m_HasGameFinishedWithDraw; }
        }

        public Player GetTheWinner()
        {
            Player playrToReturn;

            if (m_UnSuccessfulTicTacToePattern == 'X')
            {
                playrToReturn = m_PlayerTwo;
            }
            else
            {
                playrToReturn = m_PlayerOne;
            }
            return playrToReturn;
        }

        public Player GetTheTheLosser()
        {
            Player playrToReturn;

            if (m_UnSuccessfulTicTacToePattern == 'X')
            {
                playrToReturn = m_PlayerOne;
            }
            else
            {
                playrToReturn = m_PlayerTwo;
            }
            return playrToReturn;
        }

        public bool SetCoordinate(int i_Row, int i_Col)
        {
            bool isTheSetCoordinateSucceeded = false;
            if ((i_Row >= 0 && i_Row < m_GameMatrix.Size) && (i_Col >= 0 && i_Col < m_GameMatrix.Size))
            {
                if (this.m_GameMatrix[i_Row, i_Col] == ' ')
                {
                    m_GameMatrix[i_Row, i_Col] = ReturnCellToMark(m_CurrentTurn);
                    isTheSetCoordinateSucceeded = true;
                    MoveToNextTurn();
                    OnGameOperationAfterClick(i_Row, i_Col);

                }
            }
            return isTheSetCoordinateSucceeded;
        }

        public void OnGameOperationAfterClick(int i_Row, int i_Col)
        {
            if(GameOperationAfterClick != null)
            {
                GameOperationAfterClick(new Point(i_Row,i_Col),null);
            }
        }

        public void SetPlayerRetirement()
        {
            m_HasGameFinishedWithRetirement = true;
        }

        public void ComputerMove()
        {
            int row, col;
            bool setCoordinateSucceeded = false;

            while (setCoordinateSucceeded == false)
            {
                Random randNumber = new Random();
                row = randNumber.Next(Size);
                col = randNumber.Next(Size);
                setCoordinateSucceeded = SetCoordinate(row, col);
            }
        }

        public void CleanBoard()
        {
            m_GameMatrix.InitialBoard();
        }

        public void IncrementPlayerScore(Player i_PlayerToUpdate)
        {
            i_PlayerToUpdate.Score++;
        }

        private void MoveToNextTurn()
        {
            m_CurrentTurn = (eCurrentPlayer)((int)m_CurrentTurn * (-1));
        }

        private bool CheckIfAllElementsAreTheSame(List<char> i_DiagonalLineElements)
        {
            bool isAllTheElementsTheSame = true;

            for (int i = 0; i < i_DiagonalLineElements.Count - 1; i++)
            {
                if (i_DiagonalLineElements[i] != i_DiagonalLineElements[i + 1])
                {
                    isAllTheElementsTheSame = false;
                }
            }
            if (isAllTheElementsTheSame == true)
            {
                if (i_DiagonalLineElements[0] != ' ')
                {
                    this.m_UnSuccessfulTicTacToePattern = i_DiagonalLineElements[0];
                }
                else
                {
                    isAllTheElementsTheSame = false;
                }
            }
            return isAllTheElementsTheSame;
        }

        public bool CheckDiagonalLine(char[,] i_Matrix)
        {
            bool isAllTheElementsTheSame = false;
            int boardSize = m_GameMatrix.Size;

            List<char> matrixCharacters = new List<char>();
            for (int row = 0; row < boardSize; row++)
            {
                matrixCharacters.Add(i_Matrix[row, row]);
            }
            isAllTheElementsTheSame = CheckIfAllElementsAreTheSame(matrixCharacters);
            return isAllTheElementsTheSame;
        }

        public bool CheckAllDiagonalLines()
        {
            return CheckDiagonalLine(m_GameMatrix.MatrixBoard) || CheckDiagonalLine(GetRotate90Matrix(m_GameMatrix.MatrixBoard));
        }


        public char[,] GetRotate90Matrix(char[,] i_Matrix)
        {
            int boardSize = m_GameMatrix.Size;

            char[,] matrixToReturn = new char[Size, Size];

            for (int i = 0; i < boardSize; ++i)
            {
                for (int j = 0; j < boardSize; ++j)
                {
                    matrixToReturn[i, j] = i_Matrix[boardSize - j - 1, i];
                }
            }
            return matrixToReturn;
        }

        public bool CheckAllRowsAndCols()
        {
            return CheckRows(m_GameMatrix.MatrixBoard) || CheckRows(GetRotate90Matrix(m_GameMatrix.MatrixBoard));
        }

        public bool CheckRows(char[,] i_Matrix)
        {
            int boardSize = m_GameMatrix.Size;
            bool isThereASequence = true;

            for (int row = 0; row < boardSize; row++)
            {
                isThereASequence = true;
                for (int col = 0; col < boardSize - 1; col++)
                {
                    if (i_Matrix[row, col] != i_Matrix[row, col + 1])
                    {
                        isThereASequence = false;
                    }
                }
                if (isThereASequence == true)
                {
                    if (i_Matrix[row, 0] != ' ')
                    {
                        this.m_UnSuccessfulTicTacToePattern = i_Matrix[row, 0]; // initiallizing the first occurrence
                    }
                    else
                    {
                        isThereASequence = false;
                    }

                    break;
                }
            }
            return isThereASequence;
        }

        public bool GameIsOver()
        {
            m_HasGameFinishedWithWinner = CheckIfWinByGameLogic();
            m_HasGameFinishedWithDraw = CheckIfTikko();

            if (m_HasGameFinishedWithWinner == true)
            {
                IncrementPlayerScore(GetTheWinner());
            }

            return (m_HasGameFinishedWithWinner || m_HasGameFinishedWithDraw || m_HasGameFinishedWithRetirement);
        }

        private bool CheckIfTikko()
        {
            return m_GameMatrix.IsBoardFull;
        }

        public bool CheckIfWinByGameLogic()
        {
            return CheckAllRowsAndCols() || CheckAllDiagonalLines();
        }

        private char ReturnCellToMark(eCurrentPlayer i_PlayerTurn)
        {
            return i_PlayerTurn == eCurrentPlayer.PlayerOne ? 'X' : 'O';
        }
    }
}