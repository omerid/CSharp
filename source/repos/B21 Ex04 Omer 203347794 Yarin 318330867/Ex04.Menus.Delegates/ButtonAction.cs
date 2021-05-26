using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ex04.Menus.Delegates
{
    public delegate void ClickOtpion();

    public class ButtonAction : MenuItem
    {
        public event ClickOtpion Clicked;

        public ButtonAction(string i_ButtonTitle, ClickOtpion i_Function) : base (i_ButtonTitle)
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
