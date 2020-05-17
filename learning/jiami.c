#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main()
{
    char key[225] = {0};     //密钥
    char miwen[225] = {0};   //密文
    char mingwen[225] = {0}; //明文
    printf("please input mingwen:");
    gets(mingwen);
    printf("please input key:");
    gets(key);

    strlwr(key);

    int i = 0, j = 0;

    for (i; i < strlen(mingwen); i++)
    {
        if (isalpha(mingwen[i]))
        {
            if (mingwen[i] <= 'Z' && mingwen[i] >= 'A')
                miwen[i] = ((mingwen[i] - 65) + (key[j] - 97)) % 26;

            else if (mingwen[i] <= 'z' && mingwen[i] >= 'a')
                miwen[i] = ((mingwen[i] - 97) + (key[j] - 97)) % 26;

            j++;

            if (j >= strlen(key))
                j = 0;
            
        }
    }

    for (i = 0; i < strlen(mingwen); i++)
    {
        if (isalpha(mingwen[i]))
        {
            if (mingwen[i] <= 'Z' && mingwen[i] >= 'A')
                printf("%c", miwen[i] + 65);

            else if (mingwen[i] <= 'z' && mingwen[i] >= 'a')
                printf("%c", miwen[i] + 97);
        }
        else
            printf("%c", mingwen[i]);
    }
}
