#include "InitAndStoreAddressBook.h"

char* InitLocation(); //获取文件位置与名字
void StoreLocation(char* filelocation); //保持文件位置与名字
void ScanLocation(char* File); //输入文件位置与名字
void InitAddressBook(Endpoint EPT); //从文件中恢复数据
void StoreAddressBook(Endpoint EPT); //储存数据到文件中

char* InitLocation()
{
    FILE* Fp, *fp;
    char* filelocation;

    filelocation = (char*)malloc(sizeof(char) * FileMax);
    if(filelocation == NULL)
    {
        printf("filelocation malloc error.\n");
        exit(1);
    }
    if((Fp = fopen(FileLocation, "r")) == NULL)
    {
        Fp = fopen(FileLocation, "w");
        while(1)
        {
            printf("Please enter the location and file name you want to store.\n");
            scanf("%s", filelocation);
            if((fp = fopen(filelocation, "w")) == NULL)
            {
                system("CLS");
                printf("The storage location is invalid.\n");
            }
            else
            {
                fclose(fp);
                fprintf(Fp, "%s", filelocation);
                break;
            }
        }
        fclose(Fp);
        return filelocation;
    }
    else
    {
        fscanf(Fp, "%s", filelocation);
        fclose(Fp);
        return filelocation;
    }
}

void StoreLocation(char* filelocation)
{
    int input;

    printf("Do you want to change the location and name of the file.\n"
           "******************************\n"
           "****         1.Yes        ****\n"
           "****         0.No         ****\n"
           "******************************\n" );
    scanf("%d", &input);
    switch(input)
    {
        case 1:
            system("CLS");
            ScanLocation(filelocation);
            break;
        case 0:
            system("CLS");
            break;
    }
}
void ScanLocation(char* File)
{
    FILE* fp, * Fp;

    remove(File);
    while(1)
    {
        printf("Please enter the location and file name you want to store.\n");
        scanf("%s", File);
        system("CLS");
        if((fp = fopen(File, "w")) == NULL)
        {
            system("CLS");
            printf("The storage location is invalid.\n");
        }
        else
        {
            fclose(fp);
            Fp = fopen(FileLocation, "w");
            fprintf(Fp, "%s" , File);
            fclose(Fp);
            break;
        }
    }
}

void InitAddressBook(Endpoint EPT)
{
    char* File;
    FILE* Fp;
    Contact Con;

    File = InitLocation();
    Fp = fopen(File, "r");
    if (Fp == NULL)
    {
        Fp = fopen(File, "w");
        fclose(Fp);
        Fp = NULL;
        Fp = fopen(File, "r");
        if (Fp == NULL)
        {
            printf("Fopen error.\n");
            exit(1);
        }
    }
    while ((Con = InitAContact()) && ((fscanf(Fp, InputFormat, InputLocation))== TypesOfInformation))
    {
        if (EPT->Rear == NULL)
        {
            EPT->Hand = EPT->Rear = Con;
        }
        else
        {
            EPT->Rear->Next = Con;
            EPT->Rear = Con;
        }
    }
    free(Con);
    Con = NULL;
    fclose(Fp);
    Fp = NULL;
    free(File);
    File = NULL;
}

void StoreAddressBook(Endpoint EPT)
{
    char* File;
    FILE* Fp;
    Contact Con;

    File = InitLocation();
    StoreLocation(File);
    Fp = fopen(File, "w");
    if (Fp == NULL)
    {
        printf("Fopen error.\n");
        exit(1);
    }
    Con = EPT->Hand;
    while (Con)
    {
        fprintf(Fp, InputFormat, OutputLocation);
        EPT->Hand = Con->Next;
        free(Con);
        Con = EPT->Hand;
    }
    free(EPT);
    EPT = NULL;
    Con = NULL;
    fclose(Fp);
    Fp = NULL;
    free(File);
    File = NULL;
}
