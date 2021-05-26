using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ex04.Menus.Delegates
{
    public delegate void ClickOtion();

    public class ButtonAction : MenuItem
    {
        public event ClickOtion Clicked;

        public ButtonAction(string i_ButtonTitle, ClickOtion i_Function) : base (i_ButtonTitle)
        {
            Clicked += i_Function;
        }

        public override void HandleUserSelection()
        {
            if(Clicked != null)
            {
                Clicked.Invoke();
            }
            else
            {
                Console.WriteLine("[ERROR] There is no action in this button...");
            }
        }
    }
}
