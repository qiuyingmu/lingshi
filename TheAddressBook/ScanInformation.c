#include "ScanInformation.h"

int ScanInformation(Contact Con);//联系人信息读入

int ScanInformation(Contact Con)
{
    char Inspection[2] = "0";

    printf("If you want to cancel this contact addition, type 0 to end.\n");
    printf("Please enter the name：\n");
    scanf("%s", Con->Name);
    if(strcmp(Con->Name, Inspection) == 0)
    {
        return 1;
    }
    printf("Please enter the telephone number：\n");
    scanf("%s", Con->TelePhoneNums);
    if(strcmp(Con->TelePhoneNums, Inspection) == 0)
    {
        return 1;
    }
    printf("Please enter the gender：\n");
    scanf("%s", Con->Gender);
    if(strcmp(Con->Gender, Inspection) == 0)
    {
        return 1;
    }
    printf("Please enter the Age：\n");
    scanf("%d", &Con->Age);
    if(Con->Age == 0)
    {
        return 1;
    }
    return 2;
}
