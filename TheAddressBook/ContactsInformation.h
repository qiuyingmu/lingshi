#ifndef CONTACTSINFORMATION_H_INCLUDED
#define CONTACTSINFORMATION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#define NameMax 8 //�������ֳ���
#define TPNumsMax 15 //���ĵ绰���볤��
#define GenderMax 3 //�����Ա𳤶�
#define InputFormat "%s %s %s %d " //�����ʽ(д���ļ���ʽ��
#define OutputFormat "Name:%-8s  TelePhoneNums:%-15s  Gender:%-3s  Age:%-3d\n" //�����ʽ
#define TypesOfInformation 4 //��ϵ����Ϣ������
#define InputLocation Con->Name, Con->TelePhoneNums, Con->Gender, &Con->Age //�����λ��
#define OutputLocation Con->Name, Con->TelePhoneNums, Con->Gender, Con->Age //�����λ��

struct Contacts //��ϵ�˻�����Ϣ
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
