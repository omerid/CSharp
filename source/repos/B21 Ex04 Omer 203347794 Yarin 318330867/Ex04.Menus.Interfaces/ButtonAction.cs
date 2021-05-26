using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ex04.Menus.Interfaces
{
    public class ButtonAction : MenuItem
    {
        protected LButtonActionFunction Clicked;

        public ButtonAction(string i_ButtonTitle, LButtonActionFunction i_Function) : base(i_ButtonTitle)
        {
            Clicked = i_Function;
        }

        public void OnClicked()
        {
            if (Clicked != null)
            {
                Clicked.ButtonActionFunction();
            }
        }

        public override void HandleUserSelection()
        {
            OnClicked();
        }
    }
}
