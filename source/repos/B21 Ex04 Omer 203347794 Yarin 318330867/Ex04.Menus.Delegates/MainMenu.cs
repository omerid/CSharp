using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ex04.Menus.Delegates
{
    public class MainMenu
    {
        SubMenu m_SubMenu;

        public MainMenu(string i_MenuTitle)
        {
            m_SubMenu = new SubMenu(i_MenuTitle, "Exit");
        }

        public void AddItemToSubMenu(MenuItem i_MenuItem)
        {
            m_SubMenu.AddItemToSubMenu(i_MenuItem);
        }

        public void Show()
        {
            m_SubMenu.HandleUserSelection();
        }
    }
}
