#include "ChangeInformation.h"

void ChangeInformation(Endpoint EPT); //修改联系人信息确认
void Change(Contact Data, int input); //修改联系人各类信息

void ChangeInformation(Endpoint EPT)
{
    int input;
    Contact Data;
    char* Message = {"Please enter the information you want to chang.\n"
                     "******************************\n"
                     "****        1.Name        ****\n"
                     "****    2.TelePhoneNums   ****\n"
                     "****        3.Gender      ****\n"
                     "****        4.Age         ****\n"
                     "****  0.Exit this feature ****\n"
                     "******************************\n"
                    };

    if(EPT->Hand == NULL)
    {
        printf("The address book is empty.\n");
        system("pause");
        system("CLS");
        return;
    }
    Data = QueryInformation(EPT);
    if(Data == NULL)
    {
        system("pause");
        system("CLS");
        return;
    }
    else
    {
        printf(Message);
        do
        {
            scanf("%d", &input);
            if(input > 0 && input < 5)
            {
                Change(Data, input);
                input = 0;
            }
            else if(input == 0)
            {
                system("CLS");
                printf("Exit this function successfully.\n");
            }
            else
            {
                printf("Wrong selection, please select again.\n");
                input = 1;
            }
        }
        while(input);
    }
    if(input != 0)
    {
        printf("The contact information has been modified successfully.\n");
    }
}

void Change(Contact Data, int input)
{
    switch(input)
    {
    case 1:
        printf("Please enter name.\n");
        scanf("%s", Data->Name);
        break;
    case 2:
        printf("Please enter telephonenums.\n");
        scanf("%s", Data->TelePhoneNums);
        break;
    case 3:
        printf("Please enter gender.\n");
        scanf("%s", Data->Gender);
        break;
    case 4:
        printf("Please enter age.\n");
        scanf("%d", &Data->Age);
        break;
    }
    system("CLS");
    printf("The contact information is modified successfully.\n");
    system("pause");
    system("CLS");
}
