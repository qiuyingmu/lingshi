#include "Print.h"

void PrinInformation(Contact Con);

void PrinInformation(Contact Con)
{
    if (Con)
    {
        printf(OutputFormat, OutputLocation);
    }
    else
    {
        printf("No one was found.\n");
    }
}
