using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ex04.Menus.Delegates
{
    public class SubMenu : MenuItem
    {
        private List<MenuItem> m_SubMenu;
        private const int K_EndIndex = 0;

        public SubMenu(string i_ButtonTitle, string i_ReturnType = "Back") : base(i_ButtonTitle)
        {
            m_SubMenu = new List<MenuItem>();
            m_SubMenu.Add(new ButtonAction(i_ReturnType, null));
        }

        public List<MenuItem> SubMenuList
        {
            get { return m_SubMenu; }
        }

        public void AddItemToSubMenu(MenuItem i_Item)
        {
            m_SubMenu.Add(i_Item);
        }

        public override void HandleUserSelection()
        {
            bool continueToNextIteration = true;

            while(continueToNextIteration == true)
            {
                Console.Clear();
                int userChoice = HelperHandleUserSelection();
                DoUserSelection(userChoice);
                continueToNextIteration = userChoice != K_EndIndex;
            }

            Console.Clear();
        }

        internal void DoUserSelection(int i_UserChoice)
        {
            Console.Clear();
            m_SubMenu[i_UserChoice].HandleUserSelection();
        }

        internal int HelperHandleUserSelection()
        {
            ShowTitle();
            ShowMenu();
            int userChoice = GetIndexFromUser();
            return userChoice;
        }

        internal void ShowTitle()
        {
            Console.WriteLine(
$@"=======================================
{r_ButtonTitle}
========================================");
        }

        internal void ShowMenu()
        {
            int numberOfItemsInMenu = SubMenuList.Count;

            if(numberOfItemsInMenu == 0)
            {
                Console.WriteLine("The Menu Is Empty");
            }

            else
            {
                Console.WriteLine("Please Select One Of The Menu Options: ");

                for (int indexInMenu = 1; indexInMenu < numberOfItemsInMenu; indexInMenu++)
                {
                    Console.WriteLine($"{indexInMenu} - <{m_SubMenu[indexInMenu].ButtonTitle}>");
                }

                Console.WriteLine($"{K_EndIndex} - <{m_SubMenu[K_EndIndex].ButtonTitle}>");
            }
        }

        internal int GetIndexFromUser()
        {
            string inputFromUser;
            int parsingInput = -1;
            bool pasrsSuccess, isGood = false;
            int numberOfItemsInMenu = SubMenuList.Count;

            while (isGood == false)
            {
                inputFromUser = Console.ReadLine();
                pasrsSuccess = int.TryParse(inputFromUser, out parsingInput);
                if (pasrsSuccess && parsingInput >= 0 && parsingInput < numberOfItemsInMenu)
                {
                    isGood = true;
                }
                else
                {
                    Console.WriteLine("[ERROR] Your Choice Is Not In Range. Try Again: ");
                }
            }
            return parsingInput;
        }

    }
}
