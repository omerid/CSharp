using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ex04.Menus.Delegates;

namespace Ex04.Menus.Test
{
    public class DelegatesMenuBuild
    {
        public MainMenu m_Menu;

        public DelegatesMenuBuild()
        {
            m_Menu = new MainMenu("Main Menu - Delegates Test");
            BuildTheMenu();
        }

        public void ShowMenu()
        {
            m_Menu.Show();
        }

        private void BuildTheMenu()
        {
            SubMenu versionsAndSpaces = new SubMenu("Version & Spaces");
            versionsAndSpaces.AddItemToSubMenu(new ButtonAction("Show Verison", Functions.ShowVersion));
            versionsAndSpaces.AddItemToSubMenu(new ButtonAction("Space Count", Functions.CountSpaces));
            m_Menu.AddItemToSubMenu(versionsAndSpaces);

            SubMenu showDateTime = new SubMenu("Date & Time");
            showDateTime.AddItemToSubMenu(new ButtonAction("Show Date", Functions.ShowDate));
            showDateTime.AddItemToSubMenu(new ButtonAction("Show Time", Functions.ShowTime));
            m_Menu.AddItemToSubMenu(showDateTime);
        }
    }
}
