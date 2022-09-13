#ifndef CONTACTSINFORMATION_H_INCLUDED
#define CONTACTSINFORMATION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#define NameMax 8 //最大的名字长度
#define TPNumsMax 15 //最大的电话号码长度
#define GenderMax 3 //最大的性别长度
#define InputFormat "%s %s %s %d " //输入格式(写入文件格式）
#define OutputFormat "Name:%-8s  TelePhoneNums:%-15s  Gender:%-3s  Age:%-3d\n" //输出格式
#define TypesOfInformation 4 //联系人信息的种类
#define InputLocation Con->Name, Con->TelePhoneNums, Con->Gender, &Con->Age //输入的位置
#define OutputLocation Con->Name, Con->TelePhoneNums, Con->Gender, Con->Age //输出的位置

struct Contacts //联系人基本信息
{
    char TelePhoneNums[TPNumsMax];
    char Name[NameMax];
    char Gender[GenderMax];
    int Age;
    struct Contacts* Next;
};
typedef struct Contacts* Contact;
struct ContactEndpoint
{
    Contact Hand;
    Contact Rear;
};
typedef struct ContactEndpoint* Endpoint;


#endif // CONTACTSINFORMATION_H_INCLUDED
