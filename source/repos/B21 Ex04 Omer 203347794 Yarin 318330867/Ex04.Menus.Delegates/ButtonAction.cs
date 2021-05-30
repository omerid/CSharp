using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ex04.Menus.Delegates
{
    public class ButtonAction : MenuItem
    {
        public event Action Clicked;

        public ButtonAction(string i_ButtonTitle, Action i_Function) : base (i_ButtonTitle)
        {
            Clicked += i_Function;
        }

        public void OnClicked()
        {
            if (Clicked != null)
            {
                Clicked();
            }
        }

        public override void HandleUserSelection()
        {
            OnClicked();
        }
    }
}
