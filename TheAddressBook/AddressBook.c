#include "AddressBook.h"

void AddressBook(Endpoint EPT); //通讯录主函数
void Menu(); //菜单的打印

void AddressBook(Endpoint EPT)
{
    int input;
    char* CLS = {"CLS"}; //清屏

    do
    {
        Menu();
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            system(CLS);
            AddContact(EPT); //添加联系人
            break;
        case 2:
            system(CLS);
            DeleteContact(EPT); //删除联系人
            break;
        case 3:
            system(CLS);
            ChangeInformation(EPT); //改变联系人信息
            break;
        case 4:
            system(CLS);
            QueryInformation(EPT); //查找联系人信息
            system("pause");
            system("CLS");
            break;
        case 5:
            system(CLS);
            EmptyAddressBook(EPT); //清空联系人信息
            break;
        case 6:
            system(CLS);
            ShowAllContacts(EPT); //展示所有联系人信息
            break;
        case 0:
            system(CLS);
            break;
        default:
            system(CLS);
            printf("Wrong selection, please select again.\n");
            break;
        }
    } while (input);
}

void Menu()
{
    char* menu = {"******************************\n"
                  "****     This is Menu.    ****\n"
                  "****     Please enter.    ****\n"
                  "****    1.Add a contact   ****\n"
                  "****   2.Delete contact   ****\n"
                  "**** 3.Change information ****\n"
                  "****  4.Query information ****\n"
                  "**** 5.Empty address book ****\n"
                  "****  6.Show All Contacts ****\n"
                  "****  0.Exit address book ****\n"
                  "******************************\n" }; //菜单
    printf(menu);
}
