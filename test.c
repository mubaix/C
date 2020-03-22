# include <stdio.h>
int main(void)
{
    int i,sum;
    i=1;
    sum=0;
    while(i<=10)
    {
        sum=sum+i;
        i++;
    }
    printf("1+2+...+10=%d",sum);
    return 0;
}