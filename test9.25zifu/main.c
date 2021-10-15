#include <stdio.h>
#include <stdlib.h>

int main()
{
    for (int i=0;i<4;i++)
    {
        for (int j=0;j<i;j++)
        {
            printf("%s","  ");

        }printf("%s\n","*****");
    }return 0;
}
