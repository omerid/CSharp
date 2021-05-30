using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ex04.Menus.Test
{
    public class Program
    {
        public static void Main()
        {
            DelegatesMenuBuild DelegateMenu = new DelegatesMenuBuild();
            DelegateMenu.ShowMenu();

            InterfacesMenuBuild InterfacesMenu = new InterfacesMenuBuild();
            InterfacesMenu.ShowMenu();
        }
    }
}
