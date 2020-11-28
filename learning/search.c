#include <stdio.h>
#define N 10

void Input(int a[], int n);
int Search(int a[], int n, int x);

int main(void)
{
    int cScore[N], x, t;

    printf("输入数组cSrore的%d个元素:\n", N);
    Input(cScore, N);
    printf("输入要查找的数据 x：");
    scanf("%d", &x);
    t = Search(cScore, N, x);
    if (t != -1)
        printf("查找%d 成功，他的序号为%d\n", x, t);
    else
        printf("查找%d 失败", x);

    return 0;
}

void Input(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);
}

int Search(int a[], int n, int x)
{
    int i = 0;
    while (i < n)
    {
        if (a[i] == x)
            break;
        i++;
    }
    if (i < n)
        return i + 1;

    return -1;
}
