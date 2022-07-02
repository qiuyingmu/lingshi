#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define AdmLocation "Adm.txt" //����Ա��Ϣ�洢�ļ�
#define UsersLocation "AllUsers.txt" //�������ˡ���Ϣ�洢�ļ�
#define BooksLocation "Books.txt" //�鼮��Ϣ�洢�ļ�
#define OnAShelf 1
#define Borrow 2
#define Buy 3
#define BookNameMaxSize 20 //�鼮������󳤶�
#define PeriodicalsMaxSzie 10 //�鼮�ڿ�����󳤶�
#define IdMaxSize 11 //�˺ŵ���󳤶�
#define PasswordMaxSize 11 //�������󳤶�

//�鼮
typedef struct
{
    int State;//State����1Ϊ������ϣ�����2Ϊ�ѱ����ģ�����3Ϊ�ѱ�����
}bool;
struct BookNode
{
    int Num;              //�鼮���
    char BookName[BookNameMaxSize];    //�鼮����
    char Periodicals[PeriodicalsMaxSzie]; //�鼮�ڿ�
    float Price;          //�鼮�۸�
    bool BookState;       //�鼮��״̬
    struct BookNode* Next; //��һ���鼮�ĵ�ַ
};
typedef struct BookNode* OneBook; //�������鼮��Ϣ
struct Book
{
    OneBook Hand; //����ͷָ��
    OneBook Rear; //����βָ��
};
typedef struct Book* Books; //�������鼮��Ϣ����

//�������ˡ�
struct UserNode
{
    char UserId[IdMaxSize];       //�������ˡ��˺�
    char UserPassword[PasswordMaxSize]; //�������ˡ�����
    Books UserBorrow;	   //�������ˡ����ĵ��鼮
    Books UserBuy;         //�������ˡ�������鼮
    struct UserNode* Next; //��һ���������ˡ��ĵ�ַ
};
typedef struct UserNode* OneUser; //��������������Ϣ
struct User
{
    OneUser Hand; //����ͷָ��
    OneUser Rear; //����βָ��
};
typedef struct User* Users; //�������������ˡ���Ϣ����

//ͼ�����Ա
struct Administrator
{
    char AdmId[IdMaxSize];        //ͼ�����Ա���˻�
    char AdmPassword[PasswordMaxSize];  //ͼ�����Ա������
};
typedef struct Administrator* ADM; //������ͼ�����Ա����

//��������
//�������溯��
void SelectLogin(); //��ʾѡ���¼����
void Login(int x); //ͼ�����Ա�Լ��������ˡ��ĵ�¼����
void AdmUI(); //����Ա����
void UserUI(Users U, OneUser Reader); //�������ˡ�ҳ��
//�鼮��Ϣ�־û�����
void InitBooks(Books AllBooks); //�Ӵ����е����鼮��Ϣ
void SaveBooks(Books AllBooks); //���鼮��Ϣ����������
//����Ա�롰�����ˡ����ܺ���
void ShowAllBooks(Books AllBooks); //չʾ�����鼮��Ϣ
OneBook SearchBooks(Books AllBooks); //չʾ��ѯ���鼮��Ϣ
void AddBook(Books AllBooks); //�����鼮
void DeleteBook(Books AllBooks); //ɾ���鼮
void ChangeBook(Books AllBooks); //�޸��鼮��Ϣ
void ChangeAdm(); //�޸Ĺ���Ա�˺�����
void InitUser(OneUser Reader); //�Ӵ����е��롰�����ˡ������鼮����͹����鼮���
void SaveUser(OneUser Reader); //�ѡ������ˡ������鼮����͹����鼮�������������
void BorrowBook(OneUser Reader, Books AllBooks);  //�������ˡ������鼮
void BuyBook(OneUser Reader, Books AllBooks);  //�������ˡ������鼮
void ReturnBook(OneUser Reader, Books AllBooks); //�������ˡ������ĵ�ͼ�黹��ȥ
void Cancellation(Users U, OneUser Reader); //ע���������ˡ���Ϣ��Reader�������ˡ���Ϣ�� UΪ���С������ˡ���Ϣ
void ChangeUser(OneUser Reader); //�޸ġ������ˡ��˺ź�����
void DeleteUserFile(char* OldFile); //�޸��˺���Ҫ�����������й���ͽ����鼮��Ϣ���ļ�����ɾ��,OldFileΪ���ļ�����

int main()
{
    int i;

    printf("******************************\n"
           "****       ��ӭʹ��       ****\n"
           "****     ͼ�����ϵͳ     ****\n"
           "******************************\n"
           "������");
    for(i = 0; i < 5; i++)
    {
        Sleep(500);
        printf(">>>");
    }
    printf("\n�����ɹ���\n");
    system("pause");
    system("CLS");
    SelectLogin();
    return 0;
}

void SelectLogin()
{
    int input;

    do
    {
        system("CLS");
        printf("******************************\n"
               "****     1.ͼ�����Ա     ****\n"
               "****     2.�������ˡ�     ****\n"
               "****     0.�˳�           ****\n"
               "******************************\n"
               "��ѡ��");
        scanf("%d", &input);
        switch(input)
        {
        case 0:
            system("CLS");
            printf("�˳�ϵͳ�ɹ���\n");
            system("pause");
            break;
        case 1:
            system("CLS");
            Login(1); //���õ�¼����
            break;
        case 2:
            system("CLS");
            Login(2); //���õ�¼����
            break;
        default:
            system("CLS");
            printf("�������������ѡ��\n");
            break;
        }
    }
    while(input);
}

void Login(int x)
{
    FILE* Fp;

    if(x == 1) //����Ա��¼����
    {
        if((Fp = fopen(AdmLocation, "rb")) == NULL)
        {
            printf("����Ա��¼�쳣��������ѡ��\n");
            return;
        }
        else
        {
            ADM adm;
            char Id[IdMaxSize], Password[PasswordMaxSize]; //�����˺ź���������

            adm = (ADM)malloc(sizeof(struct Administrator));
            if(adm == NULL)
            {
                printf("�豸�ڴ治�㡣\n");
                return;
            }
            fscanf(Fp, "%s %s", adm->AdmId, adm->AdmPassword); //�ȴ��ļ��ж�ȡ����Ա����Ϣ
            fclose(Fp);
            while(1)
            {
                printf("����Ա��ʼ�˺�Ϊ��ADM����ʼ����Ϊ��123456����������޸ģ��������仰\n");
                printf("�������˺Ż�0�˳���\n");
                scanf("%s", Id);
                if(strcmp(Id, adm->AdmId) == 0)//�ж��˺��Ƿ���ȷ
                {
                    while(1)
                    {
                        printf("�˺���ȷ�������������0�˳���\n");
                        scanf("%s", Password);
                        if(strcmp(Password, adm->AdmPassword) == 0)//�ж������Ƿ���ȷ
                        {
                            int i;

                            free(adm);
                            printf("������ȷ����¼��>>");//�������
                            for(i = 0; i < 5; i++)
                            {
                                Sleep(500);
                                printf(">>");
                            }
                            system("CLS");
                            printf("��¼�ɹ���\n");
                            system("pause");
                            system("CLS");//�������
                            AdmUI();
                            adm = NULL;
                            break;
                        }
                        else if(strcmp(Password, "0") == 0)
                        {
                            printf("�˳���¼�ɹ���\n");
                            break;
                        }
                        else
                        {
                            system("CLS");
                            printf("�����������");
                        }
                    }
                    break;
                }
                else if(strcmp(Id, "0") == 0)
                {
                    system("CLS");
                    printf("�˳���¼�ɹ���\n");
                    system("pause");
                    system("CLS");
                    break;
                }
                else
                {
                    system("CLS");
                    printf("�˺Ų����ڡ�\n");
                }
            }
        }
    }
    else if(x == 2) //�������ˡ���¼����
    {
        int input; //ѡ��
        Users users; //���С������ˡ���Ϣ

        users = (Users)malloc(sizeof(struct User));
        users->Hand = users->Rear = NULL;
        if(users == NULL)
        {
            printf("�ڴ治�㡣\n");
            return;
        }
        Fp = fopen(UsersLocation, "rb"); //�����С������ˡ���Ϣ���ļ�
        if(Fp == NULL)
        {
            printf("�ڴ治�㡣\n");
            return;
        }
        while(1) //���ļ��еġ������ˡ���Ϣ����
        {
            OneUser user;

            user = (OneUser)malloc(sizeof(struct UserNode));
            if(user == NULL)
            {
                printf("�ڴ治�㡣\n");
                return;
            }
            user->Next = NULL;
            user->UserBuy = (Books)malloc(sizeof(struct Book));
            if(user->UserBuy == NULL)
            {
                printf("�ڴ治�㡣\n");
                return;
            }
            user->UserBorrow = (Books)malloc(sizeof(struct Book));
            if(user->UserBorrow == NULL)
            {
                printf("�ڴ治�㡣\n");
                return;
            }
            user->UserBuy->Hand = user->UserBorrow->Hand = NULL;
            user->UserBuy->Rear = user->UserBorrow->Rear = NULL;
            if((fscanf(Fp, "%s %s ", user->UserId, user->UserPassword)) != 2) //һ�ε������
            {
                free(user);
                break;
            }
            if (users->Rear == NULL)
            {
                users->Hand = users->Rear = user;
            }
            else
            {
                users->Rear->Next = user;
                users->Rear = user;
            }
        }
        fclose(Fp);
        Fp = NULL;
        while(1) //�������ˡ���¼����ע�����
        {
            system("CLS");
            printf("******************************\n"
                   "****   1.�������ˡ���¼   ****\n"
                   "****   2.�������ˡ�ע��   ****\n"
                   "****        0.�˳�        ****\n"
                   "******************************\n"
                   "��ѡ��");
            scanf("%d", &input);
            if(input == 1)
            {
                OneUser hand; //���ҡ������ˡ���ý��
                char Id[IdMaxSize], Password[PasswordMaxSize]; //�����˺ź���������

                system("CLS");
                while(1) //�������ˡ���¼����
                {
                    printf("�������˺Ż�0�˳���\n");
                    scanf("%s", Id);
                    if(strcmp(Id, "0") == 0)//�˳���¼����
                    {
                        system("CLS");
                        printf("�˳���¼�ɹ���\n");
                        system("pause");
                        break;
                    }
                    else
                    {
                        hand = users->Hand;
                        while(hand) //�����С������ˡ������������˺�
                        {
                            if(strcmp(Id, hand->UserId) == 0) //�ҵ������˺�
                            {
                                while(1)
                                {
                                    printf("�˺���ȷ�������������0�˳���\n");
                                    scanf("%s", Password);
                                    if(strcmp(Password, hand->UserPassword) == 0)//�ж������Ƿ���ȷ
                                    {
                                        int i;

                                        printf("������ȷ����¼��>>");//�������
                                        for(i = 0; i < 5; i++)
                                        {
                                            Sleep(500);
                                            printf(">>");
                                        }
                                        system("CLS");
                                        printf("��¼�ɹ���\n");
                                        system("pause");
                                        system("CLS");//�������
                                        UserUI(users, hand); //�����˽���
                                        break;
                                    }
                                    else if(strcmp(Password, "0") == 0) //�˳�����
                                    {
                                        system("CLS");
                                        printf("�˳���¼�ɹ���\n");
                                        system("pause");
                                        system("CLS");
                                        break;
                                    }
                                    else
                                    {
                                        system("CLS");
                                        printf("�����������");
                                    }
                                }
                                break;
                            }
                            else //��������
                            {
                                hand = hand->Next;
                            }
                        }
                        if(hand == NULL) //�����С������ˡ���δ�ҵ������˺�
                        {
                            system("CLS");
                            printf("�˺Ų����ڣ�");
                        }
                        else //�ҵ������˺ŵ���������
                        {
                            break;
                        }
                    }
                }
            }
            else if(input == 2)
            {
                OneUser newuser;

                newuser = (OneUser)malloc(sizeof(struct UserNode)); //����һ���յġ������ˡ�
                if(newuser == NULL)
                {
                    printf("�ڴ治�㡣\n");
                    return;
                }
                printf("������ע�ᡰ�����ˡ����˺ź����룻\n");
                scanf("%s %s", newuser->UserId, newuser->UserPassword); //����ע����˺ź����뵽�ա������ˡ�
                newuser->Next = NULL; //��ע��ġ������ˡ���Ϣ��ʼ��
                newuser->UserBorrow = newuser->UserBuy = NULL; //��ע��ġ������ˡ���Ϣ��ʼ��
                if (users->Rear == NULL) //����ע��ġ������ˡ��ŵ����ж�������
                {
                    users->Hand = users->Rear = newuser;
                }
                else
                {
                    users->Rear->Next = newuser;
                    users->Rear = newuser;
                }
                printf("ע��ɹ���\n");
                system("pause");
                system("CLS");
            }
            else if(input == 0)
            {
                //����������Ϣ�����������ļ�
                Fp = fopen(UsersLocation, "wb"); //�����С������ˡ���Ϣ���ļ�
                if(Fp == NULL)
                {
                    printf("�ڴ治�㡣\n");
                    return;
                }
                OneUser saveuser = users->Hand; //���������ˡ�������Ϣ�еĵ�һ���˵���Ϣ�õ�
                while(saveuser) //���е���ѭ������������
                {
                    fprintf(Fp, "%s %s ", saveuser->UserId, saveuser->UserPassword); //��������
                    users->Hand = saveuser->Next; //������ĵ�����һ���������ˡ�����
                    free(saveuser);
                    saveuser = users->Hand;
                }
                free(users); //���տռ�
                users = NULL;
                saveuser = NULL;
                fclose(Fp);
                Fp = NULL;
                system("CLS");
                printf("�˳���¼�ɹ���\n");
                system("pause");
                system("CLS");
                break;
            }
            else
            {
                printf("ѡ���������ѡ��\n");
            }
        }
    }
}

void AdmUI() //����Ա����
{
    int input;
    Books AllBooks;//ȫ���鼮��Ϣ

    AllBooks = (Books)malloc(sizeof(struct Book));
    if(AllBooks == NULL)
    {
        printf("�ڴ治��\n");
        exit(1);
    }
    AllBooks->Hand = AllBooks->Rear = NULL;
    InitBooks(AllBooks); //�������е��鼮��Ϣ����
    system("CLS");
    do
    {
        printf("******************************\n"
               "****    1.չʾ�����鼮    ****\n"
               "****    2.��ѯ�����鼮    ****\n"
               "****    3.�����鼮        ****\n"
               "****    4.ɾ���鼮        ****\n"
               "****    5.�޸��鼮��Ϣ    ****\n"
               "****    6.�޸��˺�����    ****\n"
               "****    0.�˳�����Աϵͳ  ****\n"
               "******************************\n"
               "��ѡ��");
        scanf("%d", &input);
        switch(input)
        {
            case 1:
                system("CLS");
                ShowAllBooks(AllBooks); //չʾ�����鼮
                system("CLS");
                break;
            case 2:
                system("CLS");
                SearchBooks(AllBooks); //��ѯ�����鼮
                system("CLS");
                break;
            case 3:
                system("CLS");
                AddBook(AllBooks); //�����鼮
                system("CLS");
                break;
            case 4:
                system("CLS");
                DeleteBook(AllBooks); //ɾ���鼮
                system("CLS");
                break;
            case 5:
                system("CLS");
                ChangeBook(AllBooks); //�޸��鼮��Ϣ
                system("CLS");
                break;
            case 6:
                system("CLS");
                ChangeAdm(); //�޸Ĺ���Ա�˺�����
                system("CLS");
                break;
            case 0:
                SaveBooks(AllBooks); //���鼮��Ϣ����������
                system("CLS");
                printf("�˳��ɹ���\n");
                system("pause");
                system("CLS");
                break;
            default :
                system("CLS");
                printf("�������\n");
        }
    }while(input);
    AllBooks = NULL;
    return;
}

void UserUI(Users U, OneUser Reader) //�������ˡ����棬Reader�������ˡ���Ϣ��UΪ���С������ˡ���Ϣ
{
    int input;
    Books AllBooks;//ȫ���鼮��Ϣ

    AllBooks = (Books)malloc(sizeof(struct Book));
    if(AllBooks == NULL)
    {
        printf("�ڴ治��\n");
        exit(1);
    }
    AllBooks->Hand = AllBooks->Rear = NULL;
    Reader->UserBorrow = (Books)malloc(sizeof(struct Book));
    if(Reader->UserBorrow == NULL)
    {
        printf("�ڴ治��\n");
        exit(1);
    }
    Reader->UserBuy = (Books)malloc(sizeof(struct Book));
    if(Reader->UserBuy == NULL)
    {
        printf("�ڴ治��\n");
        exit(1);
    }
    Reader->UserBorrow->Hand = Reader->UserBorrow->Rear = Reader->UserBuy->Hand = Reader->UserBuy->Rear = NULL;
    InitBooks(AllBooks); //�������е��鼮��Ϣ����
    InitUser(Reader); //�������еĽ��ĺ͵�����Ϣ����
    system("CLS");
    do
    {
        printf("******************************\n"
               "****    1.չʾ�����鼮    ****\n"
               "****    2.��ѯ�����鼮    ****\n"
               "****    3.�����鼮        ****\n"
               "****    4.�����鼮        ****\n"
               "****    5.�����鼮        ****\n"
               "****    6.ע���˺�        ****\n"
               "****    7.�޸��˺�����    ****\n"
               "****  8.�Լ������鼮���  ****\n"
               "****  9.�Լ������鼮���  ****\n"
               "**** 0.�˳��������ˡ�ϵͳ ****\n"
               "******************************\n"
               "��ѡ��");
        scanf("%d", &input);
        switch(input)
        {
            case 1:
                system("CLS");
                ShowAllBooks(AllBooks); //չʾ�����鼮
                system("CLS");
                break;
            case 2:
                system("CLS");
                SearchBooks(AllBooks); //��ѯ�����鼮
                system("CLS");
                break;
            case 3:
                system("CLS");
                BorrowBook(Reader, AllBooks); //�����鼮
                system("CLS");
                break;
            case 4:
                system("CLS");
                ReturnBook(Reader, AllBooks); //�����鼮
                system("CLS");
                break;
            case 5:
                system("CLS");
                BuyBook(Reader, AllBooks); //�����鼮
                system("CLS");
                break;
            case 6:
                system("CLS");
                Cancellation(U, Reader); //ע���˺�
                system("CLS");
                break;
            case 7:
                system("CLS");
                ChangeUser(Reader); //�޸ġ������ˡ��˺�����
                system("CLS");
                break;
            case 8:
                system("CLS");
                ShowAllBooks(Reader->UserBorrow); //չʾ�á������ˡ������鼮�����
                system("CLS");
                break;
            case 9:
                system("CLS");
                ShowAllBooks(Reader->UserBuy); //չʾ�á������ˡ������鼮�����
                system("CLS");
                break;
            case 0:
                system("CLS");
                printf("�˳��ɹ���\n");
                system("pause");
                system("CLS");
                break;
            default :
                system("CLS");
                printf("�������\n");
        }
        if(input == 6) //�ж��Ƿ�ע��
        {
            break;
        }
    }while(input);
    if(input != 6) //���ע���򲻽��е������ĺ͹����鼮��Ϣ������
    {
        SaveUser(Reader); //�������ĺ͹����鼮��Ϣ������
    }
    SaveBooks(AllBooks); //���鼮��Ϣ����������
    AllBooks = NULL;
    return;
}

void InitBooks(Books AllBooks)
{
    FILE* Fp;
    OneBook book; //��ʱ�鼮�洢λ��

    Fp = fopen(BooksLocation, "rb"); //���鼮�ļ�
    if (Fp == NULL)
    {
        printf("�ڴ治��\n");
        exit(1);
    }
    while (1)
    {
        book = (OneBook)malloc(sizeof(struct BookNode));
        if(book == NULL)
        {
            printf("�ڴ治��\n");
            exit(1);
        }
        book->Next = NULL;
        if(fscanf(Fp, "%d %s %s %f %d ", &book->Num, book->BookName, book->Periodicals, &book->Price, &book->BookState.State) != 5) //��ȡ�鼮�ļ�����
        {
            free(book);
            break;
        }
        if (AllBooks->Rear == NULL) //�������鼮���������鼮��
        {
            AllBooks->Hand = AllBooks->Rear = book;
        }
        else
        {
            AllBooks->Rear->Next = book;
            AllBooks->Rear = book;
        }
    }
    book = NULL;
    fclose(Fp);
    Fp = NULL;
}

void SaveBooks(Books AllBooks)
{
    FILE* Fp;
    OneBook book; //��ʱ�鼮�洢λ��

    Fp = fopen(BooksLocation, "wb"); //���鼮�ļ�
    if (Fp == NULL)
    {
        printf("�ڴ治��\n");
        exit(1);
    }
    book = AllBooks->Hand;
    while(book)
    {
        fprintf(Fp, "%d %s %s %f %d ",  book->Num, book->BookName, book->Periodicals, book->Price, book->BookState.State); //����鼮�ļ�����
        AllBooks->Hand = book->Next;
        free(book);
        book = AllBooks->Hand;
    }
    free(AllBooks);
    AllBooks = NULL;
    book = NULL;
    fclose(Fp);
    Fp = NULL;
}

void ShowAllBooks(Books AllBooks)
{
    OneBook book;

    book = AllBooks->Hand;
    if(!book)
    {
        printf("һ���鶼û�У�\n");
    }
    while(book) //���鼮��Ϣ����������Ļ
    {
        printf("��ţ�%-5d ������%-20s �ڿ���%-10s �۸�%-5.2f ", book->Num, book->BookName, book->Periodicals, book->Price);
        if(book->BookState.State == OnAShelf)
        {
            printf("״̬���������\n");
        }
        else if(book->BookState.State == Borrow)
        {
            printf("״̬���ѱ�����\n");
        }
        else if(book->BookState.State == Buy)
        {
            printf("״̬���ѱ�����\n");
        }
        book = book->Next;
    }
    system("pause");
    system("CLS");
}

OneBook SearchBooks(Books AllBooks)
{
    OneBook book;
    char name[BookNameMaxSize]; //�����Ҫ���ҵ��鼮������λ��

    book = AllBooks->Hand;
    if(book == NULL) //û���鼮
    {
        system("CLS");
        printf("�����û���鼮��\n");
        system("pause");
        system("CLS");
        return NULL;
    }
    printf("�������鼮���ֻ���0�˳���\n");
    scanf("%s", name);
    if(strcmp(name, "0") == 0) //�˳�����
    {
        system("CLS");
        printf("�˳����ܳɹ���\n");
        system("pause");
        system("CLS");
        return NULL;
    }
    else //˳��Ѱ�Ҳ���
    {
        while(book)
        {
            if (strcmp(book->BookName, name) == 0)
            {
                break;
            }
            book = book->Next;
        }
    }
    if(book == NULL) //û�ҵ��鼮
    {
        system("CLS");
        printf("û���ҵ����鼮�����Ϣ��\n");
        system("pause");
        system("CLS");
        return NULL;
    }
    else //�ҵ����鼮�������Ϣ����ӡ����Ļ
    {
        system("CLS");
        printf("�ҵ��Ȿ�鼮�ˣ�������Ϣ���£�\n");
        printf("��ţ�%-5d ������%-20s �ڿ���%-10s �۸�%-5.2f ", book->Num, book->BookName, book->Periodicals, book->Price);
        if(book->BookState.State == OnAShelf)
        {
            printf("״̬���������\n");
        }
        else if(book->BookState.State == Borrow)
        {
            printf("״̬���ѱ�����\n");
        }
        else if(book->BookState.State == Buy)
        {
            printf("״̬���ѱ�����\n");
        }
        system("pause");
        system("CLS");
        return book;
    }
}

void AddBook(Books AllBooks)
{
    OneBook book; //��ʱ�鼮�洢λ��

    book = (OneBook)malloc(sizeof(struct BookNode));
    if(book == NULL)
    {
        printf("�ڴ治��\n");
        exit(1);
    }
    book->Next = NULL;
    printf("�������鼮��Ż�0�˳���\n"); //�鼮���
    scanf("%d", &book->Num);
    if(book->Num == 0)
    {
        printf("�˳������ɹ�\n");
        system("pause");
        system("CLS");
        return;
    }
    printf("�������鼮���ֻ�0�˳���\n");
    scanf("%s", book->BookName);
    if(strcmp(book->BookName, "0") == 0) //�鼮����
    {
        printf("�˳������ɹ�\n");
        system("pause");
        system("CLS");
        return;
    }
    printf("�������鼮�ڿ���0�˳���\n");
    scanf("%s", book->Periodicals);
    if(strcmp(book->Periodicals, "0") == 0) //�鼮�ڿ�
    {
        printf("�˳������ɹ�\n");
        system("pause");
        system("CLS");
        return;
    }
    printf("�������鼮�۸��0�˳���\n");
    scanf("%f", &book->Price);
    if(book->Price == 0) //�鼮�۸�
    {
        printf("�˳������ɹ�\n");
        system("pause");
        system("CLS");
        return;
    }
    printf("�������鼮״̬(1Ϊ������ϣ�2Ϊ�ѱ����ģ�3Ϊ�ѱ�����)��0�˳���\n"); //�鼮״̬
    scanf("%d", &book->BookState.State);
    if(book->BookState.State == 0)
    {
        printf("�˳������ɹ�\n");
        system("pause");
        system("CLS");
        return;
    }
    if (AllBooks->Rear == NULL) //�������鼮���������鼮����
    {
        AllBooks->Hand = AllBooks->Rear = book;
    }
    else
    {
        AllBooks->Rear->Next = book;
        AllBooks->Rear = book;
    }
    system("CLS");
    printf("�鼮���ӳɹ���\n");
    system("pause");
    system("CLS");
}

void DeleteBook(Books AllBooks)
{
    int input;
    OneBook book, Data;

    if (AllBooks->Hand == NULL) //�����û�пɹ�ɾ�����鼮
    {
        printf("�����û���鼮��\n");
        system("pause");
        system("CLS");
        return;
    }
    Data = SearchBooks(AllBooks); //������Ҫɾ�����鼮
    if(Data == NULL) //û�ҵ����鼮
    {
        return;
    }
    do //�ҵ����鼮��ɾ�����鼮�Ĳ���
    {
        printf("��ȷ��Ҫɾ�����鼮��\n"
                "******************************\n"
                "****        1.ɾ��        ****\n"
                "****        0.��ɾ��      ****\n"
                "******************************\n");
        scanf("%d", &input);
        if(input == 0) //ȡ��ɾ���鼮
        {
            system("CLS");
            printf("ȡ��ɾ���ɹ���\n");
            system("pause");
            return;
        }
        else if(input == 1) //ȷ��ɾ���鼮
        {
            system("CLS");
            printf("ɾ�����鼮�ɹ���\n");
            system("pause");
            break;
        }
    }while(input);
    book = AllBooks->Hand; //ɾ���鼮����
    if(book->Next == NULL) //���ֻ��һ���鼮�����
    {
        AllBooks->Hand = AllBooks->Rear = NULL;
        free(book);
    }
    else if(book == Data) //�����Ҫɾ�����鼮�ǵ�һ��
    {
        AllBooks->Hand = Data->Next;
        free(book);
    }
    else//�����Ҫɾ�����鼮���ǵ�һ��
    {
        while(book->Next) //���Ѱ���鼮����
        {
            if (book->Next == Data) //�ҵ�����Ҫɾ�����鼮
            {
                book->Next = Data->Next; //ɾ������
                free(Data);
                break;
            }
            book = book->Next;
        }
        if (book->Next == NULL) //ɾ����ĵ���
        {
            AllBooks->Rear = book;
        }
    }
    return;
}

void ChangeBook(Books AllBooks)
{
    OneBook Data;

    if (AllBooks->Hand == NULL) //�����û�пɹ�ɾ�����鼮
    {
        printf("�����û���鼮��\n");
        system("pause");
        system("CLS");
        return;
    }
    Data = SearchBooks(AllBooks); //������Ҫ�޸ĵ��鼮
    if(Data == NULL)
    {
        return;
    }
    else
    {
        int input;

        do
        {
            printf("����Ҫ�޸�ʲô��\n"
                   "******************************\n"
                   "****      1.�鼮���      ****\n"
                   "****      2.�鼮����      ****\n"
                   "****      3.�鼮�ڿ�      ****\n"
                   "****      4.�鼮�۸�      ****\n"
                   "****      5.�鼮״̬      ****\n"
                   "****      0.�˳��޸�      ****\n"
                   "******************************\n");
            scanf("%d", &input);
            if(input == 0)
            {
                system("CLS");
                printf("�˳��޸ĳɹ���\n");
                system("pause");
                system("CLS");
                return;
            }
            else if(input == 1) //�޸��鼮���
            {
                int Num;

                system("CLS");
                printf("�������鼮��Ż�0�˳���\n");
                scanf("%d", &Num);
                if(Num == 0)
                {
                    system("CLS");
                    printf("�˳������ɹ���\n");
                    system("pause");
                    system("CLS");
                    break;
                }
                else
                {
                    Data->Num = Num;
                    system("CLS");
                    printf("�޸ı�ųɹ���\n");
                    system("pause");
                    system("CLS");
                    break;
                }
            }
            else if(input == 2) //�޸��鼮����
            {
                char name[BookNameMaxSize];

                system("CLS");
                printf("�������鼮���ֻ�0�˳���\n");
                scanf("%s", name);
                if(strcmp(name, "0") == 0)
                {
                    system("CLS");
                    printf("�˳������ɹ���\n");
                    system("pause");
                    system("CLS");
                    break;
                }
                else
                {
                    strcpy(Data->BookName, name);
                    system("CLS");
                    printf("�޸����ֳɹ���\n");
                    system("pause");
                    system("CLS");
                    break;
                }
            }
            else if(input == 3) //�޸��鼮�ڿ�
            {
                char periodicals[PeriodicalsMaxSzie];

                system("CLS");
                printf("�������鼮�ڿ���0�˳���\n");
                scanf("%s", periodicals);
                if(strcmp(periodicals, "0") == 0)
                {
                    system("CLS");
                    printf("�˳������ɹ���\n");
                    system("pause");
                    system("CLS");
                    break;
                }
                else
                {
                    strcpy(Data->Periodicals, periodicals);
                    system("CLS");
                    printf("�޸��ڿ��ɹ���\n");
                    system("pause");
                    system("CLS");
                    break;
                }
            }
            else if(input == 4) //�޸��鼮�۸�
            {
                float price;

                system("CLS");
                printf("�������鼮�۸��0�˳���\n");
                scanf("%f", &price);
                if(price == 0)
                {
                    system("CLS");
                    printf("�˳������ɹ���\n");
                    system("pause");
                    system("CLS");
                    break;
                }
                else
                {
                    Data->Price = price;
                    system("CLS");
                    printf("�޸ļ۸�ɹ���\n");
                    system("pause");
                    system("CLS");
                    break;
                }
            }
            else if(input == 5) //�޸��鼮״̬
            {
                int bookstate;

                system("CLS");
                printf("�������鼮״̬(1Ϊ������ϣ�2Ϊ�ѱ����ģ�3Ϊ�ѱ�����)��0�˳���\n");
                scanf("%d", &bookstate);
                if(bookstate == 0)
                {
                    system("CLS");
                    printf("�˳������ɹ���\n");
                    system("pause");
                    system("CLS");
                    break;
                }
                else
                {
                    Data->BookState.State = bookstate;
                    system("CLS");
                    printf("�޸�״̬�ɹ���\n");
                    system("pause");
                    system("CLS");
                    break;
                }
            }
            else
            {
                system("CLS");
                printf("�����������ѡ��");
            }
        }while(input);
    }
}

void ChangeAdm() //�޸Ĺ���Ա�˺�����
{
    FILE* Fp;
    char Id[IdMaxSize], Password[PasswordMaxSize]; //�µ��˺ź�����

    printf("���������˺Ż���0�˳���\n"); //�˺ŵ��޸�
    scanf("%s", Id);
    if(strcmp(Id, "0") == 0) //�˳�
    {
        system("CLS");
        printf("�˳��޸ĳɹ�\n");
        system("pause");
        system("CLS");
        return;
    }
    printf("���������������0�˳���\n"); //������޸�
    scanf("%s", Password);
    if(strcmp(Password, "0") == 0) //�˳�
    {
        system("CLS");
        printf("�˳��޸ĳɹ�\n");
        system("pause");
        system("CLS");
        return;
    }
    Fp = fopen(AdmLocation, "wb"); //�򿪹���Ա��Ϣ�ļ�
    if(Fp == NULL) //���ļ�ʧ��
    {
        system("CLS");
        printf("�޸Ĺ����г��ִ���δ�ɹ��޸��˻�������\n");
        system("pause");
        system("CLS");
        return;
    }
    fprintf(Fp, "%s %s ", Id, Password); //���µ��˺�����д�����Ա��Ϣ�ļ�
    printf("�޸��˺�����ɹ���\n");
    system("pause");
    system("CLS");
    return;
}

void InitUser(OneUser Reader)
{
    FILE* Fp;
    OneBook book; //��ʱ�鼮�洢λ��
    char BorrowSuffix[7] = "Bw.txt"; //�������ˡ������鼮�Ĵ洢�ļ���׺����Ϊ7
    char BuySuffix[7] = "By.txt"; //�������ˡ������鼮�Ĵ洢�ļ���׺����Ϊ7
    char BorrowFileLocation[IdMaxSize + 7]; //�������ˡ������鼮�Ĵ洢�ļ���
    char BuyFileLocation[IdMaxSize + 7]; //�������ˡ������鼮�Ĵ洢�ļ�

    strcpy(BorrowFileLocation, Reader->UserId); //���ļ����ͺ�׺��������
    strcpy(BuyFileLocation, Reader->UserId);
    strcat(BorrowFileLocation, BorrowSuffix);
    strcat(BuyFileLocation, BuySuffix);

    Fp = fopen(BorrowFileLocation, "rb"); //�򿪽����鼮�ļ�
    if (Fp == NULL)
    {
        Fp = fopen(BorrowFileLocation, "wb");
        fclose(Fp);
        Fp = fopen(BorrowFileLocation, "rb");
        if(Fp == NULL)
        {
            printf("�ڴ治��\n");
            exit(1);
        }
    }
    while(1) //�������н��ĵ��鼮��Ϣ���뵽�����ϵ��
    {
        book = (OneBook)malloc(sizeof(struct BookNode));
        if(book == NULL)
        {
            printf("�ڴ治��\n");
            exit(1);
        }
        book->Next = NULL;
        if(fscanf(Fp, "%d %s %s %f %d ", &book->Num, book->BookName, book->Periodicals, &book->Price, &book->BookState.State) != 5) //��ȡ�鼮�ļ�����
        {
            free(book);
            break;
        }
        if (Reader->UserBorrow->Rear == NULL) //�������鼮���������Ŀ��
        {
            Reader->UserBorrow->Hand = Reader->UserBorrow->Rear = book;
        }
        else
        {
            Reader->UserBorrow->Rear->Next = book;
            Reader->UserBorrow->Rear = book;
        }
    }
    book = NULL;
    fclose(Fp);
    Fp = NULL;
    Fp = fopen(BuyFileLocation, "rb"); //�򿪹����鼮�ļ�
    if (Fp == NULL)
    {
        Fp = fopen(BuyFileLocation, "wb");
        fclose(Fp);
        Fp = fopen(BuyFileLocation, "rb");
        if(Fp == NULL)
        {
            printf("�ڴ治��\n");
            exit(1);
        }
    }
    while(1) //�������й�����鼮��Ϣ���뵽�����ϵ��
    {
        book = (OneBook)malloc(sizeof(struct BookNode));
        if(book == NULL)
        {
            printf("�ڴ治��\n");
            exit(1);
        }
        book->Next = NULL;
        if(fscanf(Fp, "%d %s %s %f %d ", &book->Num, book->BookName, book->Periodicals, &book->Price, &book->BookState.State) != 5) //��ȡ�鼮����
        {
            free(book);
            break;
        }
        if (Reader->UserBuy->Rear == NULL) //�������鼮���빺����Ŀ��
        {
            Reader->UserBuy->Hand = Reader->UserBuy->Rear = book;
        }
        else
        {
            Reader->UserBuy->Rear->Next = book;
            Reader->UserBuy->Rear = book;
        }
    }
    book = NULL;
    fclose(Fp);
    Fp = NULL;
}

void SaveUser(OneUser Reader)
{
    FILE* Fp;
    OneBook book; //��ʱ�鼮�洢λ��
    char BorrowSuffix[7] = "Bw.txt"; //�������ˡ������鼮�Ĵ洢�ļ���׺����Ϊ7
    char BuySuffix[7] = "By.txt"; //�������ˡ������鼮�Ĵ洢�ļ���׺����Ϊ7
    char BorrowFileLocation[IdMaxSize + 7]; //�������ˡ������鼮�Ĵ洢�ļ���
    char BuyFileLocation[IdMaxSize + 7]; //�������ˡ������鼮�Ĵ洢�ļ�

    strcpy(BorrowFileLocation, Reader->UserId); //���ļ����ͺ�׺��������
    strcpy(BuyFileLocation, Reader->UserId);
    strcat(BorrowFileLocation, BorrowSuffix);
    strcat(BuyFileLocation, BuySuffix);
    Fp = fopen(BorrowFileLocation, "wb"); //�򿪽����鼮�ļ�
    if (Fp == NULL)
    {
        printf("�ڴ治��\n");
        exit(1);
    }
    book = Reader->UserBorrow->Hand;
    while(book)
    {
        fprintf(Fp, "%d %s %s %f %d ",  book->Num, book->BookName, book->Periodicals, book->Price, book->BookState.State); //����鼮����
        Reader->UserBorrow->Hand = book->Next;
        free(book);
        book = Reader->UserBorrow->Hand;
    }
    free(Reader->UserBorrow);
    Reader->UserBorrow = NULL;
    book = NULL;
    fclose(Fp);
    Fp = NULL;
    Fp = fopen(BuyFileLocation, "wb"); //�򿪹����鼮�ļ�
    if (Fp == NULL)
    {
        printf("�ڴ治��\n");
        exit(1);
    }
    book = Reader->UserBuy->Hand;
    while(book)
    {
        fprintf(Fp, "%d %s %s %f %d ",  book->Num, book->BookName, book->Periodicals, book->Price, book->BookState.State); //����鼮�ļ�����
        Reader->UserBuy->Hand = book->Next;
        free(book);
        book = Reader->UserBuy->Hand;
    }
    free(Reader->UserBuy);
    Reader->UserBuy = NULL;
    book = NULL;
    fclose(Fp);
    Fp = NULL;
}

void BorrowBook(OneUser Reader, Books AllBooks)
{
    int input;
    OneBook book, newbook;

    while(1)
    {
        book = SearchBooks(AllBooks);
        if(book == NULL)
        {
            return;
        }
        else if(book->BookState.State == 2) //State����1Ϊ������ϣ�����2Ϊ�ѱ����ģ�����3Ϊ�ѱ�����
        {
            system("CLS");
            printf("��Ǹ���Ȿ���Ѿ������˽����ˡ�\n");
        }
        else if(book->BookState.State == 3)
        {
            system("CLS");
            printf("��Ǹ���Ȿ���Ѿ������˹����ˡ�\n");
        }
        else if(book->BookState.State == 1)
        {
            break;
        }
    }
    do
    {
        printf("��ȷ��Ҫ��������鼮����ѡ��\n"
               "******************************\n"
               "****        1.����        ****\n"
               "****        0.������      ****\n"
               "******************************\n");
        scanf("%d", &input);
        if(input == 1)
        {
            book->BookState.State = 2; //State����1Ϊ������ϣ�����2Ϊ�ѱ����ģ�����3Ϊ�ѱ�����
            newbook = (OneBook)malloc(sizeof(struct BookNode));
            if(newbook == NULL)
            {
                printf("�ڴ治��\n");
                exit(1);
            }
            *(newbook) = *(book);
            newbook->Next = NULL;
            if (Reader->UserBorrow->Rear == NULL) //�������鼮���������Ŀ��
            {
                Reader->UserBorrow->Hand = Reader->UserBorrow->Rear = newbook;
            }
            else
            {
                Reader->UserBorrow->Rear->Next = newbook;
                Reader->UserBorrow->Rear = newbook;
            }
            system("CLS");
            printf("�����鼮�ɹ���\n");
            system("pause");
            break;
        }
        else if(input == 0)
        {
            system("CLS");
            printf("ȡ�����ĳɹ�\n");
            system("pause");
        }
        else
        {
            system("CLS");
            printf("ѡ�����");
        }
    }while(input);
}

void ReturnBook(OneUser Reader, Books AllBooks)
{
    int input;
    OneBook book, hand, returnbook;

    while(1)
    {
        book = SearchBooks(Reader->UserBorrow);
        if(book == NULL)
        {
            return;
        }
        else if(book->BookState.State == 2) //State����1Ϊ������ϣ�����2Ϊ�ѱ����ģ�����3Ϊ�ѱ�����
        {
            break;
        }
    }
    do
    {
        printf("��ȷ��Ҫ���ؽ��ĵ�����鼮����ѡ��\n"
               "******************************\n"
               "****        1.����        ****\n"
               "****        0.������      ****\n"
               "******************************\n");
        scanf("%d", &input);
        if(input == 1)
        {
            returnbook = AllBooks->Hand;
            while(returnbook)//˳��Ѱ�Ҳ���
            {
                if (strcmp(returnbook->BookName, book->BookName) == 0)
                {
                    break;
                }
                returnbook = returnbook->Next;
            }
            if(returnbook == NULL) //û�ҵ��鼮
            {
                system("CLS");
                printf("û���ҵ����鼮�����Ϣ��\n");
                system("pause");
                system("CLS");
                return;
            }
            returnbook->BookState.State = 1; //State����1Ϊ������ϣ�����2Ϊ�ѱ����ģ�����3Ϊ�ѱ�����
            hand = Reader->UserBorrow->Hand; //ɾ�������鼮����
            if(hand->Next == NULL) //���ֻ��һ���鼮�����
            {
                Reader->UserBorrow->Hand = Reader->UserBorrow->Rear = NULL;
                free(book);
            }
            else if(hand == book) //�����Ҫɾ�����鼮�ǵ�һ��
            {
                Reader->UserBorrow->Hand = book->Next;
                free(book);
            }
            else//�����Ҫɾ�����鼮���ǵ�һ��
            {
                while(hand->Next) //���Ѱ���鼮����
                {
                    if (hand->Next == book) //�ҵ�����Ҫɾ�����鼮
                    {
                        hand->Next = book->Next; //ɾ������
                        free(book);
                        break;
                    }
                    hand = hand->Next;
                }
                if (hand->Next == NULL) //ɾ����ĵ���
                {
                    Reader->UserBorrow->Rear = hand;
                }
            }
            book = hand = returnbook = NULL;
            system("CLS");
            printf("�����鼮�ɹ���\n");
            system("pause");
            break;
        }
        else if(input == 0)
        {
            system("CLS");
            printf("ȡ�������鼮�ɹ�\n");
            system("pause");
        }
        else
        {
            system("CLS");
            printf("ѡ�����");
        }
    }while(input);
}

void BuyBook(OneUser Reader, Books AllBooks)
{
    int input;
    OneBook book, newbook;

    while(1)
    {
        book = SearchBooks(AllBooks);
        if(book == NULL)
        {
            return;
        }
        else if(book->BookState.State == 2) //State����1Ϊ������ϣ�����2Ϊ�ѱ����ģ�����3Ϊ�ѱ�����
        {
            system("CLS");
            printf("��Ǹ���Ȿ���Ѿ������˽����ˡ�\n");
        }
        else if(book->BookState.State == 3)
        {
            system("CLS");
            printf("��Ǹ���Ȿ���Ѿ������˹����ˡ�\n");
        }
        else if(book->BookState.State == 1)
        {
            break;
        }
    }
    do
    {
        printf("��ȷ��Ҫ��������鼮����ѡ��\n"
               "******************************\n"
               "****        1.����        ****\n"
               "****        0.������      ****\n"
               "******************************\n");
        scanf("%d", &input);
        if(input == 1)
        {
            book->BookState.State = 3; //State����1Ϊ������ϣ�����2Ϊ�ѱ����ģ�����3Ϊ�ѱ�����
            newbook = (OneBook)malloc(sizeof(struct BookNode));
            if(newbook == NULL)
            {
                printf("�ڴ治��\n");
                exit(1);
            }
            *(newbook) = *(book);
            newbook->Next = NULL;
            if (Reader->UserBuy->Rear == NULL) //�������鼮���빺����Ŀ��
            {
                Reader->UserBuy->Hand = Reader->UserBuy->Rear = newbook;
            }
            else
            {
                Reader->UserBuy->Rear->Next = newbook;
                Reader->UserBuy->Rear = newbook;
            }
            system("CLS");
            printf("�����鼮�ɹ���\n");
            system("pause");
            break;
        }
        else if(input == 0)
        {
            system("CLS");
            printf("ȡ������ɹ�\n");
            system("pause");
        }
        else
        {
            system("CLS");
            printf("ѡ�����");
        }
    }while(input);
}

void Cancellation(Users U, OneUser Reader) //ע���������ˡ���Reader�������ˡ���Ϣ�� UΪ���С������ˡ���Ϣ
{
    int input;
    OneUser user; //�������������ˡ���ý��

    do
    {
        printf("��ȷ��Ҫע������ѡ��\n"
               "******************************\n"
               "****        1.ע��        ****\n"
               "****        0.��ע��      ****\n"
               "******************************\n");
        scanf("%d", &input);
        if(input == 0)
        {
            system("CLS");
            printf("ȡ��ע���ɹ�����ֹ����ע�������ѱ�ǿ���˳�Ӧ�á�\n");
            system("pause");
        }
        else if(input == 1)
        {
            DeleteUserFile(Reader->UserId); //ע�����á������ˡ��鼮��ɾ��
            user = U->Hand;
            if(user->Next == NULL) //���ֻ��һ���������ˡ�
            {
                U->Hand = U->Rear = NULL;
                free(user);
            }
            else if(user == Reader) //�����Ҫע���ġ������ˡ������Զ������ǵ�һ��
            {
                U->Hand = Reader->Next;
                free(user);
            }
            else//�����Ҫע���ġ������ˡ������Զ����в��ǵ�һ��
            {
                while(user->Next) //��������������ˡ�����
                {
                    if (user->Next == Reader) //�ҵ�����Ҫע���ġ������ˡ�
                    {
                        user->Next = Reader->Next; //ע������
                        free(Reader);
                        break;
                    }
                    user = user->Next;
                }
                if (user->Next == NULL) //ע����ĵ���
                {
                    U->Rear = user;
                }
            }
            system("CLS");
            printf("ע���óɹ������ѱ�ǿ���˳�Ӧ�á�\n");
            system("pause");
            return;
        }
        else
        {
            system("CLS");
            printf("ѡ�����");
        }
    }while(input);
    return;
}

void ChangeUser(OneUser Reader)
{
    int input;

    do
    {
        printf("����Ҫ�޸�ʲô����ѡ��\n"
               "******************************\n"
               "****      1.�޸��˺�      ****\n"
               "****      2.�޸�����      ****\n"
               "****      0.�˳��޸�      ****\n"
               "******************************\n");
        scanf("%d", &input);
        if(input == 0)
        {
            system("CLS");
            printf("�˳��޸ĳɹ���\n");
            system("pause");
            system("CLS");
            return;
        }
        else if(input == 1) //�˺ŵ��޸�
        {
            char Id[IdMaxSize];

            system("CLS");
            printf("���������˺Ż���0�˳���\n");
            scanf("%s", Id);
            if(strcmp(Id, "0") == 0) //�˳�
            {
                system("CLS");
                printf("�˳��޸��˺ųɹ�\n");
                system("pause");
                system("CLS");
                break;
            }
            else
            {
                //�޸��˺���Ҫ�����������й���ͽ����鼮��Ϣ���ļ�����ɾ��
                DeleteUserFile(Reader->UserId);
                strcpy(Reader->UserId, Id);
                system("CLS");
                printf("�޸��˺ųɹ�\n");
                system("pause");
                system("CLS");
            }
        }
        else if(input == 2) //������޸�
        {
            char password[PasswordMaxSize];

            system("CLS");
            printf("���������������0�˳���\n");
            scanf("%s", password);
            if(strcmp(password, "0") == 0) //�˳�
            {
                system("CLS");
                printf("�˳��޸�����ɹ�\n");
                system("pause");
                system("CLS");
                break;
            }
            else
            {
                strcpy(Reader->UserPassword, password);
                system("CLS");
                printf("�޸�����ɹ�\n");
                system("pause");
                system("CLS");
            }
        }
        else
        {
            system("CLS");
            printf("ѡ�����");
        }
    }while(input);
}

void DeleteUserFile(char* OldFile)
{
    FILE* Fp;

    char BorrowSuffix[7] = "Bw.txt"; //�������ˡ������鼮�Ĵ洢�ļ���׺����Ϊ7
    char BuySuffix[7] = "By.txt"; //�������ˡ������鼮�Ĵ洢�ļ���׺����Ϊ7
    char BorrowFileLocation[IdMaxSize + 7]; //�������ˡ������鼮�Ĵ洢�ļ���
    char BuyFileLocation[IdMaxSize + 7]; //�������ˡ������鼮�Ĵ洢�ļ�

    strcpy(BorrowFileLocation, OldFile); //���ļ����ͺ�׺��������
    strcpy(BuyFileLocation, OldFile);
    strcat(BorrowFileLocation, BorrowSuffix);
    strcat(BuyFileLocation, BuySuffix);

    if((Fp = fopen(BorrowFileLocation, "rb")) != NULL)
    {
        fclose(Fp);
        Fp = NULL;
        remove(BorrowFileLocation);
        if((Fp = fopen(BuyFileLocation, "rb")) != NULL)
        {
            fclose(Fp);
            Fp = NULL;
            remove(BuyFileLocation);
        }
    }
}
