using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ex04.Menus.Interfaces;

namespace Ex04.Menus.Test.FunctionsInterfaces
{
    public class ShowVersion : LButtonActionFunction
    {
        public void ButtonActionFunction()
        {
            Functions.ShowVersion();
        }
    }
}
