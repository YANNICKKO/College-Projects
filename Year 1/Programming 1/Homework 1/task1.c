#include <stdio.h>

#define MAX 8

int main()
{
    unsigned int instructiune, N, Op[MAX], operatii, Dim;
    scanf("%d", &instructiune);

    N = (instructiune >> 29) + 1;

    operatii = (instructiune << 3);

    printf("%d ", N);

    for (unsigned int i = 0; i < N; i++)
    {
        Op[i] = operatii >> 30;
        operatii <<= 2;
    }

    for (unsigned int i = 0; i < N; i++)
    {
        switch (Op[i])
        {
        case 3:
            printf("/ ");
            break;
        case 2:
            printf("* ");
            break;
        case 1:
            printf("- ");
            break;
        default:
            printf("+ ");
            break;
        }
    }

    Dim = (operatii >> 28) + 1;

    printf("%d\n", Dim);

    return 0;
}