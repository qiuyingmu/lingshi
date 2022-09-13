#include "ContactsInformation.h"

Contact InitAContact(); //申请一个联系人存储空间

Contact InitAContact()
{
    Contact Con;

    Con = (Contact)malloc(sizeof(struct Contacts));
    if (Con == NULL)
    {
        printf("Contact malloc error.\n");
        exit(1);
    }
    Con->Next = NULL;
    return Con;
}
