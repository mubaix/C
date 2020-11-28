//判断一个数是否是素数
#include <stdio.h>

int main(void)
{
    int m, i;
    printf("请输入数m：");
    scanf("%d", &m);
    for (i = 2; i < m; i++)
    {
        if (m % i == 0)
            break;
    }
    if (i == m)
        printf("%d是素数\n", m);

    else
        printf("%d不是素数\n", m);

    return 0;
}