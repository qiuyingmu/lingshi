#include "DeleteContact.h"

void DeleteContact(Endpoint EPT); //É¾³ýÁªÏµÈË

void DeleteContact(Endpoint EPT)
{
    int input, deleteNums;
    Contact Data, temp;

    if (EPT->Hand == NULL)
    {
        printf("The address book is empty.\n");
        system("pause");
        system("CLS");
        return;
    }
    printf("Please enter the number of people you want to delete.\n");
    scanf("%d", &deleteNums);
    while(deleteNums--)
    {
        Data = QueryInformation(EPT);
        if (Data == NULL)
        {
            system("pause");
            system("CLS");
            return;
        }
        do
        {
            printf("Are you sure you want to delete the contact?\n"
                   "******************************\n"
                   "****         1.Yes        ****\n"
                   "****         0.No         ****\n"
                   "******************************\n");
            scanf("%d", &input);
            if(input == 0)
            {
                system("CLS");
                printf("Cancel the success.\n");
                break;
            }
            else if(input == 1)
            {
                system("CLS");
                break;
            }
            else
            {
                system("CLS");
                deleteNums++;
                printf("Input error please re-select.\n");
            }
        }while(input);
        if(input == 0)
        {
            continue;
        }
        temp = EPT->Hand;
        if(temp->Next == NULL)
        {
            EPT->Hand = EPT->Rear = NULL;
            free(temp);
        }
        else if(temp == Data)
        {
            EPT->Hand = Data->Next;
            free(temp);
        }
        else
        {
            while (temp->Next)
            {
                if (temp->Next == Data)
                {
                    temp->Next = Data->Next;
                    free(Data);
                    break;
                }
                temp = temp->Next;
            }
            if (temp->Next == NULL)
            {
                EPT->Rear = temp;
            }
        }
        system("CLS");
        printf("The contact is deleted successfully.\n");
    }
    system("pause");
    system("CLS");
}
