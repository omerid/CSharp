using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ex04.Menus.Interfaces
{
    public abstract class MenuItem
    {
        protected readonly string r_ButtonTitle;

        public abstract void HandleUserSelection();

        public MenuItem(string i_ButtonTitle)
        {
            r_ButtonTitle = i_ButtonTitle;
        }

        public string ButtonTitle
        {
            get { return r_ButtonTitle; }
        }
    }
}
