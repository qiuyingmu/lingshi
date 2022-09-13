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
    InitAddressBook(EPT); //从文件中恢复数据
    AddressBook(EPT); //通讯录功能实现
    StoreAddressBook(EPT); //储存数据到文件中
    printf("Exit address book is success.\n");
    return 0;
}
