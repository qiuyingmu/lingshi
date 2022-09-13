#include "AddressBook.h"

void AddressBook(Endpoint EPT); //ͨѶ¼������
void Menu(); //�˵��Ĵ�ӡ

void AddressBook(Endpoint EPT)
{
    int input;
    char* CLS = {"CLS"}; //����

    do
    {
        Menu();
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            system(CLS);
            AddContact(EPT); //�����ϵ��
            break;
        case 2:
            system(CLS);
            DeleteContact(EPT); //ɾ����ϵ��
            break;
        case 3:
            system(CLS);
            ChangeInformation(EPT); //�ı���ϵ����Ϣ
            break;
        case 4:
            system(CLS);
            QueryInformation(EPT); //������ϵ����Ϣ
            system("pause");
            system("CLS");
            break;
        case 5:
            system(CLS);
            EmptyAddressBook(EPT); //�����ϵ����Ϣ
            break;
        case 6:
            system(CLS);
            ShowAllContacts(EPT); //չʾ������ϵ����Ϣ
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
                  "******************************\n" }; //�˵�
    printf(menu);
}
