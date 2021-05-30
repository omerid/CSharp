using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ex04.Menus.Interfaces;

namespace Ex04.Menus.Test
{
    public class InterfacesMenuBuild
    {
        public MainMenu m_Menu;

        public InterfacesMenuBuild()
        {
            m_Menu = new MainMenu("Main Menu - Interface Test");
            buildTheMenu();
        }

        public void ShowMenu()
        {
            m_Menu.Show();
        }

        private void buildTheMenu()
        {
            SubMenu versionsAndSpaces = new SubMenu("Version & Spaces");
            versionsAndSpaces.AddItemToSubMenu(new ButtonAction("Show Verison", new FunctionsInterfaces.ShowVersion()));
            versionsAndSpaces.AddItemToSubMenu(new ButtonAction("Space Count", new FunctionsInterfaces.CountSpaces()));
            m_Menu.AddItemToSubMenu(versionsAndSpaces);

            SubMenu showDateTime = new SubMenu("Date & Time");
            showDateTime.AddItemToSubMenu(new ButtonAction("Show Time", new FunctionsInterfaces.ShowTime()));
            showDateTime.AddItemToSubMenu(new ButtonAction("Show Date", new FunctionsInterfaces.ShowDate()));
            m_Menu.AddItemToSubMenu(showDateTime);
        }
    }
}
