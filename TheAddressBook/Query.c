#include "Query.h"

Contact QueryInformation(Endpoint EPT); //查找联系人信息
Contact QueryName(Endpoint EPT); //按名字搜索信息
Contact QueryTelePhoneNums(Endpoint EPT); //按电话号码搜索信息
Contact Query(Endpoint EPT, char* DataType, int Type); //搜索信息

Contact QueryInformation(Endpoint EPT)
{
    int input;
    Contact Data = NULL;
    char* SearchHint = {"Please enter the way you want to proceed to the next step.\n"
                        "******************************\n"
                        "****         1.Name       ****\n"
                        "****    2.TelePhoneNums   ****\n"
                        "****  0.Exit this feature ****\n"
                        "******************************\n" }; //查找联系人提示

    if (EPT->Hand == NULL)
    {
        printf("The address book is empty.\n");
        return NULL;
    }
    do
    {
        printf(SearchHint);
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            system("CLS");
            Data = QueryName(EPT); //按名字搜索信息
            break;
        case 2:
            system("CLS");
            Data = QueryTelePhoneNums(EPT); //按电话号码搜索信息
            break;
        case 0:
            system("CLS");
            printf("Exit this function successfully.\n"); //退出当前操作
            break;
        default:
            system("CLS");
            printf("Wrong selection, please select again.\n");
            break;
        }
    } while(input != 1 && input != 2 && input != 0);
    if(input == 0)
    {
        return NULL;
    }
    else if(Data == NULL)
    {
        printf("The contact information was not found.\n");
        return Data;
    }
    else
    {
        PrinInformation(Data);
        return Data;
    }
}

Contact QueryName(Endpoint EPT)
{
    char name[NameMax];

    printf("Please enter the name.\n");
    scanf("%s", name);
    system("CLS");
    return Query(EPT, name, NameMax);
}

Contact QueryTelePhoneNums(Endpoint EPT)
{
    char telephonenums[TPNumsMax];

    printf("Please enter the telephonenums.\n");
    scanf("%s", telephonenums);
    system("CLS");
    return Query(EPT, telephonenums, TPNumsMax);
}

Contact Query(Endpoint EPT, char* DataType, int Type)
{
    Contact Data;

    Data = EPT->Hand;
    if (Type == NameMax)
    {
        while (Data)
        {
            if (strcmp(Data->Name, DataType) == 0)
            {
                return Data;
            }
            Data = Data->Next;
        }
    }
    else if (Type == TPNumsMax)
    {
        while (Data)
        {
            if (strcmp(Data->TelePhoneNums, DataType) == 0)
            {
                return Data;
            }
            Data = Data->Next;
        }
    }
    return NULL;
}
