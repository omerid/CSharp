using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ex04.Menus.Test
{
    public static class Functions
    {
        public static void ShowVersion()
        {
            Console.WriteLine("Version: 21.1.4.8930 {0}", Environment.NewLine);
            TapToContinue();
        }

        public static void CountSpaces()
        {
            Console.WriteLine("Please Enter A Sentence: ");
            string userInput = Console.ReadLine();
            if(userInput != null)
            {
                int spaceCount = userInput.Count(ch => ch == ' ');
                if (spaceCount > 1)
                {
                    Console.WriteLine("There are {0} spaces {1}", spaceCount, Environment.NewLine);
                }
                else
                {
                    Console.WriteLine("There is {0} space {1}", spaceCount, Environment.NewLine);
                }
            }
            TapToContinue();
        }

        public static void ShowDate()
        {
            Console.WriteLine($"{DateTime.Today.ToString("d")} {Environment.NewLine}");
            TapToContinue();
        }

        public static void ShowTime()
        {
            Console.WriteLine($"{DateTime.Now.ToString("HH:mm:ss")} {Environment.NewLine}");
            TapToContinue();
        }

        public static void TapToContinue()
        {
            Console.WriteLine(
@"-----------------------------------
   < Press Any Key For Back To Menu >
-----------------------------------");

            string dummyInput = Console.ReadLine();
        }
    }
}
