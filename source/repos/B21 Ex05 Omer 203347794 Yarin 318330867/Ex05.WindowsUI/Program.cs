using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Mime;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Ex05.WindowsUI
{
    public class Program
    {
        public static void Main()
        {
            FormGameSettings newGameSettings = new FormGameSettings();
            newGameSettings.ShowDialog();
            Application TicTacTow = new Application(newGameSettings);
            TicTacTow.RunGame();
        }
    }
}
