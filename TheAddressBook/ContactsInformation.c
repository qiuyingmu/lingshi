#include "ContactsInformation.h"

Contact InitAContact(); //����һ����ϵ�˴洢�ռ�

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
