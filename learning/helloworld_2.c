#include <stdio.h>
//逐字打印字符
void A(int);
void B(int);
void C(int);

int main(void)
{
    int x = 10;
    A(x);
    return 0;

}

void A(int x)
{
    printf("A收到传递过来的x=%d\n", x);
    x++;
    B(x);

}

void B(int x)
{
    printf("B收到传递过来的x=%d\n", x);
    x++;
    C(x);
}

void C(int x)
{
    printf("C收到传递过来的x=%d\n", x);
    
}