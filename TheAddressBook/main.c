#include <stdlib.h>
#include <stdio.h>
#include "AddressBook.h"
#include "InitAndStoreAddressBook.h"
#include "ContactsInformation.h"

int main()
{
    Endpoint EPT;

    EPT = (Endpoint)malloc(sizeof(struct ContactEndpoint));
    if (EPT == NULL)
    {
        printf("EPT error.\n");
        exit(1);
    }
    EPT->Hand = EPT->Rear = NULL;
    system("color 02");
    InitAddressBook(EPT); //���ļ��лָ�����
    AddressBook(EPT); //ͨѶ¼����ʵ��
    StoreAddressBook(EPT); //�������ݵ��ļ���
    printf("Exit address book is success.\n");
    return 0;
}
