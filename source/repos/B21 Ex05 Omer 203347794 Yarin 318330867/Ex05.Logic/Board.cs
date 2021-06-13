using System;
using System.Threading.Tasks;

namespace Ex05.Logic
{
    public class Board
    {
        private int m_BorderSize;
        private char[,] m_Board;
        private int m_Count;
        private bool m_BoardIsFull;

        public Board(int i_Size)
        {
            m_BorderSize = i_Size;
            m_Board = new char[m_BorderSize, m_BorderSize];
            InitialBoard();
        }

        public int Size
        {
            get { return m_BorderSize; }
            set { m_BorderSize = value; }
        }

        public char[,] MatrixBoard
        {
            get { return m_Board; }
            set { m_Board = value; }
        }

        public char this[int row, int col]
        {
            get { return m_Board[row, col]; }
            set
            {
                m_Board[row, col] = value;
                m_Count++;
                if (m_Count == (m_BorderSize * m_BorderSize))
                {
                    m_BoardIsFull = true;
                }
            }
        }

        public int Count
        {
            get { return m_Count; }
        }

        public bool IsBoardFull
        {
            get { return m_BoardIsFull; }
        }

        public void InitialBoard()
        {
            for (int row = 0; row < m_BorderSize; row++)
            {
                for (int col = 0; col < m_BorderSize; col++)
                {
                    m_Board[row, col] = ' ';
                }
            }
            m_BoardIsFull = false;
            m_Count = 0;
        }
    }
}
