#include "ShowAllContacts.h"

void ShowAllContacts(Endpoint EPT);

void ShowAllContacts(Endpoint EPT)
{
    Contact hand;

    hand = EPT->Hand;
    if(!hand)
    {
        printf("The address book is empty.\n");
    }
    while(hand)
    {
        PrinInformation(hand);
        hand = hand->Next;
    }
    system("pause");
    system("CLS");
}
