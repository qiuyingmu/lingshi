#include "AddContact.h"

void AddContact(Endpoint EPT); //添加联系人

void AddContact(Endpoint EPT)
{
    int input, Inspection, addNums;
    Contact Con;


    Con = InitAContact();
    Inspection = ScanInformation(Con);
    if(Inspection == 1)
    {
        system("CLS");
        printf("The operation was cancelled successfully.\n");
        system("pause");
        system("CLS");
        return;
    }
    do
    {
        printf("Are you sure you want to add the contact?\n"
               "******************************\n"
               "****         1.Yes        ****\n"
               "****         0.No         ****\n"
               "******************************\n");
        scanf("%d", &input);
        if(input == 0)
        {
            system("CLS");
            printf("Cancel the success.\n");
            system("pause");
            system("CLS");
            return;
        }
        else if(input == 1)
        {
            break;
        }
        else
        {
            system("CLS");
            printf("Input error please re-select.\n");
        }
    }while(input);
    if (EPT->Rear == NULL)
    {
        EPT->Hand = EPT->Rear = Con;
    }
    else
    {
        EPT->Rear->Next = Con;
        EPT->Rear = Con;
    }
    system("CLS");
    printf("Contact added successfully.\n");
    system("pause");
    system("CLS");
}
