using System;
using System.Threading.Tasks;

namespace Ex05.Logic
{
    public class Player
    {
        private string m_Name;
        private int m_Score;
        private readonly char m_Sign;

        public Player(string i_Name, char i_Sign)
        {
            m_Name = i_Name;
            m_Score = 0;
            m_Sign = i_Sign;
        }

        public string Name
        {
            get { return m_Name; }
            set { m_Name = value; }
        }

        public int Score
        {
            get { return m_Score; }
            set { m_Score = value; }
        }

        public int Sign
        {
            get { return m_Sign; }
        }
    }
}
