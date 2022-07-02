#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define AdmLocation "Adm.txt" //管理员信息存储文件
#define UsersLocation "AllUsers.txt" //“读书人”信息存储文件
#define BooksLocation "Books.txt" //书籍信息存储文件
#define OnAShelf 1
#define Borrow 2
#define Buy 3
#define BookNameMaxSize 20 //书籍名的最大长度
#define PeriodicalsMaxSzie 10 //书籍期刊的最大长度
#define IdMaxSize 11 //账号的最大长度
#define PasswordMaxSize 11 //密码的最大长度

//书籍
typedef struct
{
    int State;//State等于1为在书架上，等于2为已被借阅，等于3为已被购买
}bool;
struct BookNode
{
    int Num;              //书籍编号
    char BookName[BookNameMaxSize];    //书籍名字
    char Periodicals[PeriodicalsMaxSzie]; //书籍期刊
    float Price;          //书籍价格
    bool BookState;       //书籍的状态
    struct BookNode* Next; //下一本书籍的地址
};
typedef struct BookNode* OneBook; //重命名书籍信息
struct Book
{
    OneBook Hand; //链表头指针
    OneBook Rear; //链表尾指针
};
typedef struct Book* Books; //重命名书籍信息链表

//“读书人”
struct UserNode
{
    char UserId[IdMaxSize];       //“读书人”账号
    char UserPassword[PasswordMaxSize]; //“读书人”密码
    Books UserBorrow;	   //“读书人”借阅的书籍
    Books UserBuy;         //“读书人”购买的书籍
    struct UserNode* Next; //下一个“读书人”的地址
};
typedef struct UserNode* OneUser; //重命名读书人信息
struct User
{
    OneUser Hand; //链表头指针
    OneUser Rear; //链表尾指针
};
typedef struct User* Users; //重命名“读书人”信息链表

//图书管理员
struct Administrator
{
    char AdmId[IdMaxSize];        //图书管理员的账户
    char AdmPassword[PasswordMaxSize];  //图书管理员的密码
};
typedef struct Administrator* ADM; //重命名图书管理员类型

//函数声明
//操作界面函数
void SelectLogin(); //显示选择登录界面
void Login(int x); //图书管理员以及“读书人”的登录界面
void AdmUI(); //管理员界面
void UserUI(Users U, OneUser Reader); //“读书人”页面
//书籍信息持久化函数
void InitBooks(Books AllBooks); //从磁盘中导入书籍信息
void SaveBooks(Books AllBooks); //把书籍信息导出到磁盘
//管理员与“读书人”功能函数
void ShowAllBooks(Books AllBooks); //展示所有书籍信息
OneBook SearchBooks(Books AllBooks); //展示查询的书籍信息
void AddBook(Books AllBooks); //增加书籍
void DeleteBook(Books AllBooks); //删除书籍
void ChangeBook(Books AllBooks); //修改书籍信息
void ChangeAdm(); //修改管理员账号密码
void InitUser(OneUser Reader); //从磁盘中导入“读书人”借阅书籍情况和购买书籍情况
void SaveUser(OneUser Reader); //把“读书人”借阅书籍情况和购买书籍情况导出到磁盘
void BorrowBook(OneUser Reader, Books AllBooks);  //“读书人”借阅书籍
void BuyBook(OneUser Reader, Books AllBooks);  //“读书人”购买书籍
void ReturnBook(OneUser Reader, Books AllBooks); //“读书人”将借阅的图书还回去
void Cancellation(Users U, OneUser Reader); //注销“读书人”信息，Reader“读书人”信息， U为所有“读书人”信息
void ChangeUser(OneUser Reader); //修改“读书人”账号和密码
void DeleteUserFile(char* OldFile); //修改账号需要将曾经磁盘中购买和借阅书籍信息的文件进行删除,OldFile为旧文件名字

int main()
{
    int i;

    printf("******************************\n"
           "****       欢迎使用       ****\n"
           "****     图书管理系统     ****\n"
           "******************************\n"
           "启动中");
    for(i = 0; i < 5; i++)
    {
        Sleep(500);
        printf(">>>");
    }
    printf("\n启动成功。\n");
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
               "****     1.图书管理员     ****\n"
               "****     2.“读书人”     ****\n"
               "****     0.退出           ****\n"
               "******************************\n"
               "请选择：");
        scanf("%d", &input);
        switch(input)
        {
        case 0:
            system("CLS");
            printf("退出系统成功。\n");
            system("pause");
            break;
        case 1:
            system("CLS");
            Login(1); //调用登录界面
            break;
        case 2:
            system("CLS");
            Login(2); //调用登录界面
            break;
        default:
            system("CLS");
            printf("输入错误，请重新选择。\n");
            break;
        }
    }
    while(input);
}

void Login(int x)
{
    FILE* Fp;

    if(x == 1) //管理员登录功能
    {
        if((Fp = fopen(AdmLocation, "rb")) == NULL)
        {
            printf("管理员登录异常，请重新选择。\n");
            return;
        }
        else
        {
            ADM adm;
            char Id[IdMaxSize], Password[PasswordMaxSize]; //输入账号和输入密码

            adm = (ADM)malloc(sizeof(struct Administrator));
            if(adm == NULL)
            {
                printf("设备内存不足。\n");
                return;
            }
            fscanf(Fp, "%s %s", adm->AdmId, adm->AdmPassword); //先从文件中读取管理员的信息
            fclose(Fp);
            while(1)
            {
                printf("管理员初始账号为：ADM，初始密码为：123456。如果你已修改，请忽略这句话\n");
                printf("请输入账号或0退出：\n");
                scanf("%s", Id);
                if(strcmp(Id, adm->AdmId) == 0)//判断账号是否正确
                {
                    while(1)
                    {
                        printf("账号正确，请输入密码或0退出：\n");
                        scanf("%s", Password);
                        if(strcmp(Password, adm->AdmPassword) == 0)//判断密码是否正确
                        {
                            int i;

                            free(adm);
                            printf("密码正确，登录中>>");//交互设计
                            for(i = 0; i < 5; i++)
                            {
                                Sleep(500);
                                printf(">>");
                            }
                            system("CLS");
                            printf("登录成功！\n");
                            system("pause");
                            system("CLS");//交互设计
                            AdmUI();
                            adm = NULL;
                            break;
                        }
                        else if(strcmp(Password, "0") == 0)
                        {
                            printf("退出登录成功。\n");
                            break;
                        }
                        else
                        {
                            system("CLS");
                            printf("密码输入错误，");
                        }
                    }
                    break;
                }
                else if(strcmp(Id, "0") == 0)
                {
                    system("CLS");
                    printf("退出登录成功。\n");
                    system("pause");
                    system("CLS");
                    break;
                }
                else
                {
                    system("CLS");
                    printf("账号不存在。\n");
                }
            }
        }
    }
    else if(x == 2) //“读书人”登录功能
    {
        int input; //选项
        Users users; //所有“读书人”信息

        users = (Users)malloc(sizeof(struct User));
        users->Hand = users->Rear = NULL;
        if(users == NULL)
        {
            printf("内存不足。\n");
            return;
        }
        Fp = fopen(UsersLocation, "rb"); //打开所有“读书人”信息的文件
        if(Fp == NULL)
        {
            printf("内存不足。\n");
            return;
        }
        while(1) //将文件中的“读书人”信息导入
        {
            OneUser user;

            user = (OneUser)malloc(sizeof(struct UserNode));
            if(user == NULL)
            {
                printf("内存不足。\n");
                return;
            }
            user->Next = NULL;
            user->UserBuy = (Books)malloc(sizeof(struct Book));
            if(user->UserBuy == NULL)
            {
                printf("内存不足。\n");
                return;
            }
            user->UserBorrow = (Books)malloc(sizeof(struct Book));
            if(user->UserBorrow == NULL)
            {
                printf("内存不足。\n");
                return;
            }
            user->UserBuy->Hand = user->UserBorrow->Hand = NULL;
            user->UserBuy->Rear = user->UserBorrow->Rear = NULL;
            if((fscanf(Fp, "%s %s ", user->UserId, user->UserPassword)) != 2) //一次导入操作
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
        while(1) //“读书人”登录或者注册界面
        {
            system("CLS");
            printf("******************************\n"
                   "****   1.“读书人”登录   ****\n"
                   "****   2.“读书人”注册   ****\n"
                   "****        0.退出        ****\n"
                   "******************************\n"
                   "请选择：");
            scanf("%d", &input);
            if(input == 1)
            {
                OneUser hand; //查找“读书人”的媒介
                char Id[IdMaxSize], Password[PasswordMaxSize]; //输入账号和输入密码

                system("CLS");
                while(1) //“读书人”登录操作
                {
                    printf("请输入账号或0退出：\n");
                    scanf("%s", Id);
                    if(strcmp(Id, "0") == 0)//退出登录操作
                    {
                        system("CLS");
                        printf("退出登录成功。\n");
                        system("pause");
                        break;
                    }
                    else
                    {
                        hand = users->Hand;
                        while(hand) //在所有“读书人”中搜索输入账号
                        {
                            if(strcmp(Id, hand->UserId) == 0) //找到输入账号
                            {
                                while(1)
                                {
                                    printf("账号正确，请输入密码或0退出：\n");
                                    scanf("%s", Password);
                                    if(strcmp(Password, hand->UserPassword) == 0)//判断密码是否正确
                                    {
                                        int i;

                                        printf("密码正确，登录中>>");//交互设计
                                        for(i = 0; i < 5; i++)
                                        {
                                            Sleep(500);
                                            printf(">>");
                                        }
                                        system("CLS");
                                        printf("登录成功！\n");
                                        system("pause");
                                        system("CLS");//交互设计
                                        UserUI(users, hand); //读书人界面
                                        break;
                                    }
                                    else if(strcmp(Password, "0") == 0) //退出操作
                                    {
                                        system("CLS");
                                        printf("退出登录成功。\n");
                                        system("pause");
                                        system("CLS");
                                        break;
                                    }
                                    else
                                    {
                                        system("CLS");
                                        printf("密码输入错误，");
                                    }
                                }
                                break;
                            }
                            else //搜索操作
                            {
                                hand = hand->Next;
                            }
                        }
                        if(hand == NULL) //在所有“读书人”中未找到输入账号
                        {
                            system("CLS");
                            printf("账号不存在，");
                        }
                        else //找到输入账号的正常步骤
                        {
                            break;
                        }
                    }
                }
            }
            else if(input == 2)
            {
                OneUser newuser;

                newuser = (OneUser)malloc(sizeof(struct UserNode)); //创建一个空的“读书人”
                if(newuser == NULL)
                {
                    printf("内存不足。\n");
                    return;
                }
                printf("请输入注册“读书人”的账号和密码；\n");
                scanf("%s %s", newuser->UserId, newuser->UserPassword); //输入注册的账号和密码到空“读书人”
                newuser->Next = NULL; //新注册的“读书人”信息初始化
                newuser->UserBorrow = newuser->UserBuy = NULL; //新注册的“读书人”信息初始化
                if (users->Rear == NULL) //将新注册的“读书人”放到所有读书人中
                {
                    users->Hand = users->Rear = newuser;
                }
                else
                {
                    users->Rear->Next = newuser;
                    users->Rear = newuser;
                }
                printf("注册成功！\n");
                system("pause");
                system("CLS");
            }
            else if(input == 0)
            {
                //将读书人信息导出到磁盘文件
                Fp = fopen(UsersLocation, "wb"); //打开所有“读书人”信息的文件
                if(Fp == NULL)
                {
                    printf("内存不足。\n");
                    return;
                }
                OneUser saveuser = users->Hand; //将“读书人”所有信息中的第一个人的信息拿到
                while(saveuser) //进行单个循环导出到磁盘
                {
                    fprintf(Fp, "%s %s ", saveuser->UserId, saveuser->UserPassword); //导出操作
                    users->Hand = saveuser->Next; //导出后的调整下一个“读书人”操作
                    free(saveuser);
                    saveuser = users->Hand;
                }
                free(users); //回收空间
                users = NULL;
                saveuser = NULL;
                fclose(Fp);
                Fp = NULL;
                system("CLS");
                printf("退出登录成功。\n");
                system("pause");
                system("CLS");
                break;
            }
            else
            {
                printf("选择错误重新选择\n");
            }
        }
    }
}

void AdmUI() //管理员界面
{
    int input;
    Books AllBooks;//全部书籍信息

    AllBooks = (Books)malloc(sizeof(struct Book));
    if(AllBooks == NULL)
    {
        printf("内存不足\n");
        exit(1);
    }
    AllBooks->Hand = AllBooks->Rear = NULL;
    InitBooks(AllBooks); //将磁盘中的书籍信息导入
    system("CLS");
    do
    {
        printf("******************************\n"
               "****    1.展示所有书籍    ****\n"
               "****    2.查询单个书籍    ****\n"
               "****    3.增加书籍        ****\n"
               "****    4.删除书籍        ****\n"
               "****    5.修改书籍信息    ****\n"
               "****    6.修改账号密码    ****\n"
               "****    0.退出管理员系统  ****\n"
               "******************************\n"
               "请选择：");
        scanf("%d", &input);
        switch(input)
        {
            case 1:
                system("CLS");
                ShowAllBooks(AllBooks); //展示所有书籍
                system("CLS");
                break;
            case 2:
                system("CLS");
                SearchBooks(AllBooks); //查询单个书籍
                system("CLS");
                break;
            case 3:
                system("CLS");
                AddBook(AllBooks); //增加书籍
                system("CLS");
                break;
            case 4:
                system("CLS");
                DeleteBook(AllBooks); //删除书籍
                system("CLS");
                break;
            case 5:
                system("CLS");
                ChangeBook(AllBooks); //修改书籍信息
                system("CLS");
                break;
            case 6:
                system("CLS");
                ChangeAdm(); //修改管理员账号密码
                system("CLS");
                break;
            case 0:
                SaveBooks(AllBooks); //将书籍信息导出到磁盘
                system("CLS");
                printf("退出成功！\n");
                system("pause");
                system("CLS");
                break;
            default :
                system("CLS");
                printf("输入错误。\n");
        }
    }while(input);
    AllBooks = NULL;
    return;
}

void UserUI(Users U, OneUser Reader) //“读书人”界面，Reader“读书人”信息，U为所有“读书人”信息
{
    int input;
    Books AllBooks;//全部书籍信息

    AllBooks = (Books)malloc(sizeof(struct Book));
    if(AllBooks == NULL)
    {
        printf("内存不足\n");
        exit(1);
    }
    AllBooks->Hand = AllBooks->Rear = NULL;
    Reader->UserBorrow = (Books)malloc(sizeof(struct Book));
    if(Reader->UserBorrow == NULL)
    {
        printf("内存不足\n");
        exit(1);
    }
    Reader->UserBuy = (Books)malloc(sizeof(struct Book));
    if(Reader->UserBuy == NULL)
    {
        printf("内存不足\n");
        exit(1);
    }
    Reader->UserBorrow->Hand = Reader->UserBorrow->Rear = Reader->UserBuy->Hand = Reader->UserBuy->Rear = NULL;
    InitBooks(AllBooks); //将磁盘中的书籍信息导入
    InitUser(Reader); //将磁盘中的借阅和导出信息导入
    system("CLS");
    do
    {
        printf("******************************\n"
               "****    1.展示所有书籍    ****\n"
               "****    2.查询单个书籍    ****\n"
               "****    3.借阅书籍        ****\n"
               "****    4.还回书籍        ****\n"
               "****    5.购买书籍        ****\n"
               "****    6.注销账号        ****\n"
               "****    7.修改账号密码    ****\n"
               "****  8.自己借阅书籍情况  ****\n"
               "****  9.自己购买书籍情况  ****\n"
               "**** 0.退出“读书人”系统 ****\n"
               "******************************\n"
               "请选择：");
        scanf("%d", &input);
        switch(input)
        {
            case 1:
                system("CLS");
                ShowAllBooks(AllBooks); //展示所有书籍
                system("CLS");
                break;
            case 2:
                system("CLS");
                SearchBooks(AllBooks); //查询单个书籍
                system("CLS");
                break;
            case 3:
                system("CLS");
                BorrowBook(Reader, AllBooks); //借阅书籍
                system("CLS");
                break;
            case 4:
                system("CLS");
                ReturnBook(Reader, AllBooks); //借阅书籍
                system("CLS");
                break;
            case 5:
                system("CLS");
                BuyBook(Reader, AllBooks); //购买书籍
                system("CLS");
                break;
            case 6:
                system("CLS");
                Cancellation(U, Reader); //注销账号
                system("CLS");
                break;
            case 7:
                system("CLS");
                ChangeUser(Reader); //修改“读书人”账号密码
                system("CLS");
                break;
            case 8:
                system("CLS");
                ShowAllBooks(Reader->UserBorrow); //展示该“读书人”借阅书籍的情况
                system("CLS");
                break;
            case 9:
                system("CLS");
                ShowAllBooks(Reader->UserBuy); //展示该“读书人”购买书籍的情况
                system("CLS");
                break;
            case 0:
                system("CLS");
                printf("退出成功！\n");
                system("pause");
                system("CLS");
                break;
            default :
                system("CLS");
                printf("输入错误。\n");
        }
        if(input == 6) //判断是否注销
        {
            break;
        }
    }while(input);
    if(input != 6) //如果注销则不进行导出借阅和购买书籍信息到磁盘
    {
        SaveUser(Reader); //导出借阅和购买书籍信息到磁盘
    }
    SaveBooks(AllBooks); //将书籍信息导出到磁盘
    AllBooks = NULL;
    return;
}

void InitBooks(Books AllBooks)
{
    FILE* Fp;
    OneBook book; //临时书籍存储位置

    Fp = fopen(BooksLocation, "rb"); //打开书籍文件
    if (Fp == NULL)
    {
        printf("内存不足\n");
        exit(1);
    }
    while (1)
    {
        book = (OneBook)malloc(sizeof(struct BookNode));
        if(book == NULL)
        {
            printf("内存不足\n");
            exit(1);
        }
        book->Next = NULL;
        if(fscanf(Fp, "%d %s %s %f %d ", &book->Num, book->BookName, book->Periodicals, &book->Price, &book->BookState.State) != 5) //读取书籍文件操作
        {
            free(book);
            break;
        }
        if (AllBooks->Rear == NULL) //将单个书籍放入所有书籍中
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
    OneBook book; //临时书籍存储位置

    Fp = fopen(BooksLocation, "wb"); //打开书籍文件
    if (Fp == NULL)
    {
        printf("内存不足\n");
        exit(1);
    }
    book = AllBooks->Hand;
    while(book)
    {
        fprintf(Fp, "%d %s %s %f %d ",  book->Num, book->BookName, book->Periodicals, book->Price, book->BookState.State); //存放书籍文件操作
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
        printf("一本书都没有！\n");
    }
    while(book) //将书籍信息逐个输出到屏幕
    {
        printf("编号：%-5d 书名：%-20s 期刊：%-10s 价格：%-5.2f ", book->Num, book->BookName, book->Periodicals, book->Price);
        if(book->BookState.State == OnAShelf)
        {
            printf("状态：在书架上\n");
        }
        else if(book->BookState.State == Borrow)
        {
            printf("状态：已被借阅\n");
        }
        else if(book->BookState.State == Buy)
        {
            printf("状态：已被购买\n");
        }
        book = book->Next;
    }
    system("pause");
    system("CLS");
}

OneBook SearchBooks(Books AllBooks)
{
    OneBook book;
    char name[BookNameMaxSize]; //存放想要查找的书籍的书名位置

    book = AllBooks->Hand;
    if(book == NULL) //没有书籍
    {
        system("CLS");
        printf("书架上没有书籍！\n");
        system("pause");
        system("CLS");
        return NULL;
    }
    printf("请输入书籍名字或者0退出。\n");
    scanf("%s", name);
    if(strcmp(name, "0") == 0) //退出操作
    {
        system("CLS");
        printf("退出功能成功！\n");
        system("pause");
        system("CLS");
        return NULL;
    }
    else //顺序寻找操作
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
    if(book == NULL) //没找到书籍
    {
        system("CLS");
        printf("没有找到该书籍相关信息。\n");
        system("pause");
        system("CLS");
        return NULL;
    }
    else //找到了书籍的相关信息并打印到屏幕
    {
        system("CLS");
        printf("找到这本书籍了，它的信息如下：\n");
        printf("编号：%-5d 书名：%-20s 期刊：%-10s 价格：%-5.2f ", book->Num, book->BookName, book->Periodicals, book->Price);
        if(book->BookState.State == OnAShelf)
        {
            printf("状态：在书架上\n");
        }
        else if(book->BookState.State == Borrow)
        {
            printf("状态：已被借阅\n");
        }
        else if(book->BookState.State == Buy)
        {
            printf("状态：已被购买\n");
        }
        system("pause");
        system("CLS");
        return book;
    }
}

void AddBook(Books AllBooks)
{
    OneBook book; //临时书籍存储位置

    book = (OneBook)malloc(sizeof(struct BookNode));
    if(book == NULL)
    {
        printf("内存不足\n");
        exit(1);
    }
    book->Next = NULL;
    printf("请输入书籍编号或0退出：\n"); //书籍编号
    scanf("%d", &book->Num);
    if(book->Num == 0)
    {
        printf("退出操作成功\n");
        system("pause");
        system("CLS");
        return;
    }
    printf("请输入书籍名字或0退出：\n");
    scanf("%s", book->BookName);
    if(strcmp(book->BookName, "0") == 0) //书籍名字
    {
        printf("退出操作成功\n");
        system("pause");
        system("CLS");
        return;
    }
    printf("请输入书籍期刊或0退出：\n");
    scanf("%s", book->Periodicals);
    if(strcmp(book->Periodicals, "0") == 0) //书籍期刊
    {
        printf("退出操作成功\n");
        system("pause");
        system("CLS");
        return;
    }
    printf("请输入书籍价格或0退出：\n");
    scanf("%f", &book->Price);
    if(book->Price == 0) //书籍价格
    {
        printf("退出操作成功\n");
        system("pause");
        system("CLS");
        return;
    }
    printf("请输入书籍状态(1为在书架上，2为已被借阅，3为已被购买)或0退出：\n"); //书籍状态
    scanf("%d", &book->BookState.State);
    if(book->BookState.State == 0)
    {
        printf("退出操作成功\n");
        system("pause");
        system("CLS");
        return;
    }
    if (AllBooks->Rear == NULL) //将单个书籍放入所有书籍操作
    {
        AllBooks->Hand = AllBooks->Rear = book;
    }
    else
    {
        AllBooks->Rear->Next = book;
        AllBooks->Rear = book;
    }
    system("CLS");
    printf("书籍增加成功！\n");
    system("pause");
    system("CLS");
}

void DeleteBook(Books AllBooks)
{
    int input;
    OneBook book, Data;

    if (AllBooks->Hand == NULL) //书架上没有可供删除的书籍
    {
        printf("书架上没有书籍！\n");
        system("pause");
        system("CLS");
        return;
    }
    Data = SearchBooks(AllBooks); //查找需要删除的书籍
    if(Data == NULL) //没找到该书籍
    {
        return;
    }
    do //找到该书籍，删除该书籍的操作
    {
        printf("你确定要删除该书籍？\n"
                "******************************\n"
                "****        1.删除        ****\n"
                "****        0.不删了      ****\n"
                "******************************\n");
        scanf("%d", &input);
        if(input == 0) //取消删除书籍
        {
            system("CLS");
            printf("取消删除成功。\n");
            system("pause");
            return;
        }
        else if(input == 1) //确认删除书籍
        {
            system("CLS");
            printf("删除该书籍成功。\n");
            system("pause");
            break;
        }
    }while(input);
    book = AllBooks->Hand; //删除书籍操作
    if(book->Next == NULL) //如果只有一本书籍的情况
    {
        AllBooks->Hand = AllBooks->Rear = NULL;
        free(book);
    }
    else if(book == Data) //如果需要删除的书籍是第一本
    {
        AllBooks->Hand = Data->Next;
        free(book);
    }
    else//如果需要删除的书籍不是第一本
    {
        while(book->Next) //向后寻找书籍操作
        {
            if (book->Next == Data) //找到了需要删除的书籍
            {
                book->Next = Data->Next; //删除操作
                free(Data);
                break;
            }
            book = book->Next;
        }
        if (book->Next == NULL) //删除后的调整
        {
            AllBooks->Rear = book;
        }
    }
    return;
}

void ChangeBook(Books AllBooks)
{
    OneBook Data;

    if (AllBooks->Hand == NULL) //书架上没有可供删除的书籍
    {
        printf("书架上没有书籍！\n");
        system("pause");
        system("CLS");
        return;
    }
    Data = SearchBooks(AllBooks); //查找需要修改的书籍
    if(Data == NULL)
    {
        return;
    }
    else
    {
        int input;

        do
        {
            printf("你想要修改什么：\n"
                   "******************************\n"
                   "****      1.书籍编号      ****\n"
                   "****      2.书籍名字      ****\n"
                   "****      3.书籍期刊      ****\n"
                   "****      4.书籍价格      ****\n"
                   "****      5.书籍状态      ****\n"
                   "****      0.退出修改      ****\n"
                   "******************************\n");
            scanf("%d", &input);
            if(input == 0)
            {
                system("CLS");
                printf("退出修改成功。\n");
                system("pause");
                system("CLS");
                return;
            }
            else if(input == 1) //修改书籍编号
            {
                int Num;

                system("CLS");
                printf("请输入书籍编号或0退出：\n");
                scanf("%d", &Num);
                if(Num == 0)
                {
                    system("CLS");
                    printf("退出操作成功。\n");
                    system("pause");
                    system("CLS");
                    break;
                }
                else
                {
                    Data->Num = Num;
                    system("CLS");
                    printf("修改编号成功。\n");
                    system("pause");
                    system("CLS");
                    break;
                }
            }
            else if(input == 2) //修改书籍名字
            {
                char name[BookNameMaxSize];

                system("CLS");
                printf("请输入书籍名字或0退出：\n");
                scanf("%s", name);
                if(strcmp(name, "0") == 0)
                {
                    system("CLS");
                    printf("退出操作成功。\n");
                    system("pause");
                    system("CLS");
                    break;
                }
                else
                {
                    strcpy(Data->BookName, name);
                    system("CLS");
                    printf("修改名字成功。\n");
                    system("pause");
                    system("CLS");
                    break;
                }
            }
            else if(input == 3) //修改书籍期刊
            {
                char periodicals[PeriodicalsMaxSzie];

                system("CLS");
                printf("请输入书籍期刊或0退出：\n");
                scanf("%s", periodicals);
                if(strcmp(periodicals, "0") == 0)
                {
                    system("CLS");
                    printf("退出操作成功。\n");
                    system("pause");
                    system("CLS");
                    break;
                }
                else
                {
                    strcpy(Data->Periodicals, periodicals);
                    system("CLS");
                    printf("修改期刊成功。\n");
                    system("pause");
                    system("CLS");
                    break;
                }
            }
            else if(input == 4) //修改书籍价格
            {
                float price;

                system("CLS");
                printf("请输入书籍价格或0退出：\n");
                scanf("%f", &price);
                if(price == 0)
                {
                    system("CLS");
                    printf("退出操作成功。\n");
                    system("pause");
                    system("CLS");
                    break;
                }
                else
                {
                    Data->Price = price;
                    system("CLS");
                    printf("修改价格成功。\n");
                    system("pause");
                    system("CLS");
                    break;
                }
            }
            else if(input == 5) //修改书籍状态
            {
                int bookstate;

                system("CLS");
                printf("请输入书籍状态(1为在书架上，2为已被借阅，3为已被购买)或0退出：\n");
                scanf("%d", &bookstate);
                if(bookstate == 0)
                {
                    system("CLS");
                    printf("退出操作成功。\n");
                    system("pause");
                    system("CLS");
                    break;
                }
                else
                {
                    Data->BookState.State = bookstate;
                    system("CLS");
                    printf("修改状态成功。\n");
                    system("pause");
                    system("CLS");
                    break;
                }
            }
            else
            {
                system("CLS");
                printf("输入错误，重新选择");
            }
        }while(input);
    }
}

void ChangeAdm() //修改管理员账号密码
{
    FILE* Fp;
    char Id[IdMaxSize], Password[PasswordMaxSize]; //新的账号和密码

    printf("请输入新账号或者0退出：\n"); //账号的修改
    scanf("%s", Id);
    if(strcmp(Id, "0") == 0) //退出
    {
        system("CLS");
        printf("退出修改成功\n");
        system("pause");
        system("CLS");
        return;
    }
    printf("请输入新密码或者0退出：\n"); //密码的修改
    scanf("%s", Password);
    if(strcmp(Password, "0") == 0) //退出
    {
        system("CLS");
        printf("退出修改成功\n");
        system("pause");
        system("CLS");
        return;
    }
    Fp = fopen(AdmLocation, "wb"); //打开管理员信息文件
    if(Fp == NULL) //打开文件失败
    {
        system("CLS");
        printf("修改过程中出现错误，未成功修改账户和密码\n");
        system("pause");
        system("CLS");
        return;
    }
    fprintf(Fp, "%s %s ", Id, Password); //将新的账号密码写入管理员信息文件
    printf("修改账号密码成功！\n");
    system("pause");
    system("CLS");
    return;
}

void InitUser(OneUser Reader)
{
    FILE* Fp;
    OneBook book; //临时书籍存储位置
    char BorrowSuffix[7] = "Bw.txt"; //“读书人”借阅书籍的存储文件后缀长度为7
    char BuySuffix[7] = "By.txt"; //“读书人”购买书籍的存储文件后缀长度为7
    char BorrowFileLocation[IdMaxSize + 7]; //“读书人”借阅书籍的存储文件名
    char BuyFileLocation[IdMaxSize + 7]; //“读书人”购买书籍的存储文件

    strcpy(BorrowFileLocation, Reader->UserId); //将文件名和后缀连接起来
    strcpy(BuyFileLocation, Reader->UserId);
    strcat(BorrowFileLocation, BorrowSuffix);
    strcat(BuyFileLocation, BuySuffix);

    Fp = fopen(BorrowFileLocation, "rb"); //打开借阅书籍文件
    if (Fp == NULL)
    {
        Fp = fopen(BorrowFileLocation, "wb");
        fclose(Fp);
        Fp = fopen(BorrowFileLocation, "rb");
        if(Fp == NULL)
        {
            printf("内存不足\n");
            exit(1);
        }
    }
    while(1) //将磁盘中借阅的书籍信息导入到这个联系人
    {
        book = (OneBook)malloc(sizeof(struct BookNode));
        if(book == NULL)
        {
            printf("内存不足\n");
            exit(1);
        }
        book->Next = NULL;
        if(fscanf(Fp, "%d %s %s %f %d ", &book->Num, book->BookName, book->Periodicals, &book->Price, &book->BookState.State) != 5) //读取书籍文件操作
        {
            free(book);
            break;
        }
        if (Reader->UserBorrow->Rear == NULL) //将单个书籍放入借阅栏目中
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
    Fp = fopen(BuyFileLocation, "rb"); //打开购买书籍文件
    if (Fp == NULL)
    {
        Fp = fopen(BuyFileLocation, "wb");
        fclose(Fp);
        Fp = fopen(BuyFileLocation, "rb");
        if(Fp == NULL)
        {
            printf("内存不足\n");
            exit(1);
        }
    }
    while(1) //将磁盘中购买的书籍信息导入到这个联系人
    {
        book = (OneBook)malloc(sizeof(struct BookNode));
        if(book == NULL)
        {
            printf("内存不足\n");
            exit(1);
        }
        book->Next = NULL;
        if(fscanf(Fp, "%d %s %s %f %d ", &book->Num, book->BookName, book->Periodicals, &book->Price, &book->BookState.State) != 5) //读取书籍操作
        {
            free(book);
            break;
        }
        if (Reader->UserBuy->Rear == NULL) //将单个书籍放入购买栏目中
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
    OneBook book; //临时书籍存储位置
    char BorrowSuffix[7] = "Bw.txt"; //“读书人”借阅书籍的存储文件后缀长度为7
    char BuySuffix[7] = "By.txt"; //“读书人”购买书籍的存储文件后缀长度为7
    char BorrowFileLocation[IdMaxSize + 7]; //“读书人”借阅书籍的存储文件名
    char BuyFileLocation[IdMaxSize + 7]; //“读书人”购买书籍的存储文件

    strcpy(BorrowFileLocation, Reader->UserId); //将文件名和后缀连接起来
    strcpy(BuyFileLocation, Reader->UserId);
    strcat(BorrowFileLocation, BorrowSuffix);
    strcat(BuyFileLocation, BuySuffix);
    Fp = fopen(BorrowFileLocation, "wb"); //打开借阅书籍文件
    if (Fp == NULL)
    {
        printf("内存不足\n");
        exit(1);
    }
    book = Reader->UserBorrow->Hand;
    while(book)
    {
        fprintf(Fp, "%d %s %s %f %d ",  book->Num, book->BookName, book->Periodicals, book->Price, book->BookState.State); //存放书籍操作
        Reader->UserBorrow->Hand = book->Next;
        free(book);
        book = Reader->UserBorrow->Hand;
    }
    free(Reader->UserBorrow);
    Reader->UserBorrow = NULL;
    book = NULL;
    fclose(Fp);
    Fp = NULL;
    Fp = fopen(BuyFileLocation, "wb"); //打开购买书籍文件
    if (Fp == NULL)
    {
        printf("内存不足\n");
        exit(1);
    }
    book = Reader->UserBuy->Hand;
    while(book)
    {
        fprintf(Fp, "%d %s %s %f %d ",  book->Num, book->BookName, book->Periodicals, book->Price, book->BookState.State); //存放书籍文件操作
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
        else if(book->BookState.State == 2) //State等于1为在书架上，等于2为已被借阅，等于3为已被购买
        {
            system("CLS");
            printf("抱歉，这本书已经被别人借阅了。\n");
        }
        else if(book->BookState.State == 3)
        {
            system("CLS");
            printf("抱歉，这本书已经被别人购买了。\n");
        }
        else if(book->BookState.State == 1)
        {
            break;
        }
    }
    do
    {
        printf("您确定要借阅这把书籍吗？请选择：\n"
               "******************************\n"
               "****        1.借阅        ****\n"
               "****        0.不借阅      ****\n"
               "******************************\n");
        scanf("%d", &input);
        if(input == 1)
        {
            book->BookState.State = 2; //State等于1为在书架上，等于2为已被借阅，等于3为已被购买
            newbook = (OneBook)malloc(sizeof(struct BookNode));
            if(newbook == NULL)
            {
                printf("内存不足\n");
                exit(1);
            }
            *(newbook) = *(book);
            newbook->Next = NULL;
            if (Reader->UserBorrow->Rear == NULL) //将单个书籍放入借阅栏目中
            {
                Reader->UserBorrow->Hand = Reader->UserBorrow->Rear = newbook;
            }
            else
            {
                Reader->UserBorrow->Rear->Next = newbook;
                Reader->UserBorrow->Rear = newbook;
            }
            system("CLS");
            printf("借阅书籍成功。\n");
            system("pause");
            break;
        }
        else if(input == 0)
        {
            system("CLS");
            printf("取消借阅成功\n");
            system("pause");
        }
        else
        {
            system("CLS");
            printf("选择错误，");
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
        else if(book->BookState.State == 2) //State等于1为在书架上，等于2为已被借阅，等于3为已被购买
        {
            break;
        }
    }
    do
    {
        printf("您确定要还回借阅的这把书籍吗？请选择：\n"
               "******************************\n"
               "****        1.还书        ****\n"
               "****        0.不还书      ****\n"
               "******************************\n");
        scanf("%d", &input);
        if(input == 1)
        {
            returnbook = AllBooks->Hand;
            while(returnbook)//顺序寻找操作
            {
                if (strcmp(returnbook->BookName, book->BookName) == 0)
                {
                    break;
                }
                returnbook = returnbook->Next;
            }
            if(returnbook == NULL) //没找到书籍
            {
                system("CLS");
                printf("没有找到该书籍相关信息。\n");
                system("pause");
                system("CLS");
                return;
            }
            returnbook->BookState.State = 1; //State等于1为在书架上，等于2为已被借阅，等于3为已被购买
            hand = Reader->UserBorrow->Hand; //删除借阅书籍操作
            if(hand->Next == NULL) //如果只有一本书籍的情况
            {
                Reader->UserBorrow->Hand = Reader->UserBorrow->Rear = NULL;
                free(book);
            }
            else if(hand == book) //如果需要删除的书籍是第一本
            {
                Reader->UserBorrow->Hand = book->Next;
                free(book);
            }
            else//如果需要删除的书籍不是第一本
            {
                while(hand->Next) //向后寻找书籍操作
                {
                    if (hand->Next == book) //找到了需要删除的书籍
                    {
                        hand->Next = book->Next; //删除操作
                        free(book);
                        break;
                    }
                    hand = hand->Next;
                }
                if (hand->Next == NULL) //删除后的调整
                {
                    Reader->UserBorrow->Rear = hand;
                }
            }
            book = hand = returnbook = NULL;
            system("CLS");
            printf("还回书籍成功。\n");
            system("pause");
            break;
        }
        else if(input == 0)
        {
            system("CLS");
            printf("取消还回书籍成功\n");
            system("pause");
        }
        else
        {
            system("CLS");
            printf("选择错误，");
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
        else if(book->BookState.State == 2) //State等于1为在书架上，等于2为已被借阅，等于3为已被购买
        {
            system("CLS");
            printf("抱歉，这本书已经被别人借阅了。\n");
        }
        else if(book->BookState.State == 3)
        {
            system("CLS");
            printf("抱歉，这本书已经被别人购买了。\n");
        }
        else if(book->BookState.State == 1)
        {
            break;
        }
    }
    do
    {
        printf("您确定要购买这把书籍吗？请选择：\n"
               "******************************\n"
               "****        1.购买        ****\n"
               "****        0.不购买      ****\n"
               "******************************\n");
        scanf("%d", &input);
        if(input == 1)
        {
            book->BookState.State = 3; //State等于1为在书架上，等于2为已被借阅，等于3为已被购买
            newbook = (OneBook)malloc(sizeof(struct BookNode));
            if(newbook == NULL)
            {
                printf("内存不足\n");
                exit(1);
            }
            *(newbook) = *(book);
            newbook->Next = NULL;
            if (Reader->UserBuy->Rear == NULL) //将单个书籍放入购买栏目中
            {
                Reader->UserBuy->Hand = Reader->UserBuy->Rear = newbook;
            }
            else
            {
                Reader->UserBuy->Rear->Next = newbook;
                Reader->UserBuy->Rear = newbook;
            }
            system("CLS");
            printf("购买书籍成功。\n");
            system("pause");
            break;
        }
        else if(input == 0)
        {
            system("CLS");
            printf("取消购买成功\n");
            system("pause");
        }
        else
        {
            system("CLS");
            printf("选择错误，");
        }
    }while(input);
}

void Cancellation(Users U, OneUser Reader) //注销“读书人”，Reader“读书人”信息， U为所有“读书人”信息
{
    int input;
    OneUser user; //搜索出“读书人”的媒介

    do
    {
        printf("您确定要注销吗？请选择：\n"
               "******************************\n"
               "****        1.注销        ****\n"
               "****        0.不注销      ****\n"
               "******************************\n");
        scanf("%d", &input);
        if(input == 0)
        {
            system("CLS");
            printf("取消注销成功，防止恶意注销，您已被强制退出应用。\n");
            system("pause");
        }
        else if(input == 1)
        {
            DeleteUserFile(Reader->UserId); //注销将该“读书人”书籍库删除
            user = U->Hand;
            if(user->Next == NULL) //如果只有一个“读书人”
            {
                U->Hand = U->Rear = NULL;
                free(user);
            }
            else if(user == Reader) //如果需要注销的“读书人”在所以读书中是第一个
            {
                U->Hand = Reader->Next;
                free(user);
            }
            else//如果需要注销的“读书人”在所以读书中不是第一个
            {
                while(user->Next) //向后搜索“读书人”操作
                {
                    if (user->Next == Reader) //找到了需要注销的“读书人”
                    {
                        user->Next = Reader->Next; //注销操作
                        free(Reader);
                        break;
                    }
                    user = user->Next;
                }
                if (user->Next == NULL) //注销后的调整
                {
                    U->Rear = user;
                }
            }
            system("CLS");
            printf("注销该成功，您已被强制退出应用。\n");
            system("pause");
            return;
        }
        else
        {
            system("CLS");
            printf("选择错误，");
        }
    }while(input);
    return;
}

void ChangeUser(OneUser Reader)
{
    int input;

    do
    {
        printf("您想要修改什么？请选择：\n"
               "******************************\n"
               "****      1.修改账号      ****\n"
               "****      2.修改密码      ****\n"
               "****      0.退出修改      ****\n"
               "******************************\n");
        scanf("%d", &input);
        if(input == 0)
        {
            system("CLS");
            printf("退出修改成功。\n");
            system("pause");
            system("CLS");
            return;
        }
        else if(input == 1) //账号的修改
        {
            char Id[IdMaxSize];

            system("CLS");
            printf("请输入新账号或者0退出：\n");
            scanf("%s", Id);
            if(strcmp(Id, "0") == 0) //退出
            {
                system("CLS");
                printf("退出修改账号成功\n");
                system("pause");
                system("CLS");
                break;
            }
            else
            {
                //修改账号需要将曾经磁盘中购买和借阅书籍信息的文件进行删除
                DeleteUserFile(Reader->UserId);
                strcpy(Reader->UserId, Id);
                system("CLS");
                printf("修改账号成功\n");
                system("pause");
                system("CLS");
            }
        }
        else if(input == 2) //密码的修改
        {
            char password[PasswordMaxSize];

            system("CLS");
            printf("请输入新密码或者0退出：\n");
            scanf("%s", password);
            if(strcmp(password, "0") == 0) //退出
            {
                system("CLS");
                printf("退出修改密码成功\n");
                system("pause");
                system("CLS");
                break;
            }
            else
            {
                strcpy(Reader->UserPassword, password);
                system("CLS");
                printf("修改密码成功\n");
                system("pause");
                system("CLS");
            }
        }
        else
        {
            system("CLS");
            printf("选择错误，");
        }
    }while(input);
}

void DeleteUserFile(char* OldFile)
{
    FILE* Fp;

    char BorrowSuffix[7] = "Bw.txt"; //“读书人”借阅书籍的存储文件后缀长度为7
    char BuySuffix[7] = "By.txt"; //“读书人”购买书籍的存储文件后缀长度为7
    char BorrowFileLocation[IdMaxSize + 7]; //“读书人”借阅书籍的存储文件名
    char BuyFileLocation[IdMaxSize + 7]; //“读书人”购买书籍的存储文件

    strcpy(BorrowFileLocation, OldFile); //将文件名和后缀连接起来
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
