#include <stdio.h>
//字符排序
void SelectSort(int r[], int n);

const int N = 6;

int main(void)
{
    int a[N];

    printf("输入%d个整数：\n", N);
    for (int i = 0; i < N; i++)
        scanf("%d", &a[i]);
    SelectSort(a, N);

    printf("排序后结果为：");
    for (int i = 0; i < N; i++)
        printf("%d ", a[i]);
    printf("\n");

    return 0;
}

void SelectSort(int r[], int n)
{
    int i, j, mink, m;
    for (i = 0; i < n - 1; i++)
    {
        mink = i;
        for (j = i + 1; j < n; j++)
        {
            if (r[mink] > r[j])
                mink = j;
        }
        if (mink != i)
        {
            int t;
            t = r[i];
            r[i] = r[mink];
            r[mink] = t;
        }
    }
}
