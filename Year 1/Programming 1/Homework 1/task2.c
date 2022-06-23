#include <stdio.h>

#define MAX 8

int main()
{
    unsigned int instructiune, N, Op[MAX], operatii, Dim, n_nr = 0;
    unsigned short nr_operanzi, operanzi[MAX + 1], contor = 0;
    int rezultat = 0;

    scanf("%d", &instructiune);

    N = (instructiune >> 29) + 1;

    operatii = (instructiune << 3);

    for (unsigned int i = 0; i < N; i++)
    {
        Op[i] = (operatii >> 30);
        operatii <<= 2;
    }

    Dim = (operatii >> 28) + 1;

    if (((N + 1) * Dim) % 16 == 0)
        nr_operanzi = ((N + 1) * Dim) / 16;
    else
        nr_operanzi = ((N + 1) * Dim) / 16 + 1;

    unsigned short operanzi_mari[nr_operanzi];

    for (unsigned short i = 0; i < nr_operanzi; i++)
    {
        scanf("%hd", &operanzi_mari[i]);
        for (unsigned short j = 0; j < 16 / Dim && contor != N + 1; j++)
        {
            operanzi[n_nr + j] = (operanzi_mari[i] << (j * Dim));
            operanzi[n_nr + j] >>= (16 - Dim);
            contor++;
        }
        n_nr += (16 / Dim);
    }

    rezultat = operanzi[0];
    for (unsigned int i = 0; i < N; i++)
    {
        switch (Op[i])
        {
        case 3:
            rezultat /= operanzi[i + 1];
            break;
        case 2:
            rezultat *= operanzi[i + 1];
            break;
        case 1:
            rezultat -= operanzi[i + 1];
            break;
        default:
            rezultat += operanzi[i + 1];
            break;
        }
    }

    printf("%d\n", rezultat);

    return 0;
}