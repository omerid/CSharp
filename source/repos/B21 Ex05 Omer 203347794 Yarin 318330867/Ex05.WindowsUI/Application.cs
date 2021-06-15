using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Ex05.Logic;

namespace Ex05.WindowsUI
{
    public class Application
    {
        private TicTacToeRev m_Game;
        private FormGame m_GameUI;

        public Application(FormGameSettings i_FormGameSettings)
        {
            if(i_FormGameSettings.DialogResult == DialogResult.OK)
            {
                InitGame(i_FormGameSettings);
            }

        }

        private void InitGame(FormGameSettings i_FormGameSettings)
        {
            string player1Name = i_FormGameSettings.Player1Name;
            string player2Name = i_FormGameSettings.Player2Name == "[Computer]" ? "Computer" : i_FormGameSettings.Player2Name;
            eGameDefinition gameMode = player2Name == "Computer" ? eGameDefinition.PlayerAgainstComputer : eGameDefinition.TwoPlayers;
            int boardSize = i_FormGameSettings.BoardSize;
            m_Game = new TicTacToeRev(boardSize, player1Name, player2Name, gameMode);
        }

        internal void RunGame()
        {
            
        }
    }
}
