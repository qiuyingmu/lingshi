#include "EmptyAddressBook.h"

void EmptyAddressBook(Endpoint EPT); //清空联系人信息

void EmptyAddressBook(Endpoint EPT)
{
    int input;
    Contact hand;

    hand = EPT->Hand;
    if(hand == NULL)
    {
        printf("The address book is empty.\n");
        system("pause");
        system("CLS");
        return;
    }
    do
    {
        printf("Have you identified all the contacts?\n"
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
    while(hand)
    {
        EPT->Hand = hand->Next;
        free(hand);
        hand = EPT->Hand;
    }
    hand = NULL;
    EPT->Hand = EPT->Rear = NULL;
    system("CLS");
    printf("Clearing the address book successfully.\n");
    system("pause");
    system("CLS");
}
