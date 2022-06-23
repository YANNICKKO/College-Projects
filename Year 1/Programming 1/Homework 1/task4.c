#include <stdio.h>

#define MAX 8

int main()
{
    unsigned int instructiune, N, Op[MAX], operatii, Dim, n_nr = 0;
    unsigned short nr_operanzi, operanzi[MAX + 1], contor_numere = 0, parte_numar = 0, contor_rest = 0;
    int rezultat = 0;
    int rezultat_1, rezultat_2, ramas = 0, primul = 0;

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
        scanf("%hd", &operanzi_mari[i]);

    parte_numar = 16 % Dim;

    for (unsigned short i = 0; i < nr_operanzi; i++)
    {
        for (unsigned short j = 0; j < 16 / Dim - contor_rest && contor_numere != N + 1; j++)
        {
            operanzi[n_nr + j] = (operanzi_mari[i] << (j * Dim));
            operanzi[n_nr + j] >>= (16 - Dim);
            contor_numere++;
        }

        n_nr += 16 / Dim - contor_rest;
        if (16 % Dim != 0 && contor_numere != N + 1)
        {
            operanzi[n_nr] = operanzi_mari[i] << (Dim * (16 / Dim - contor_rest));
            operanzi[n_nr] >>= 16 - Dim;
            operanzi[n_nr] += (operanzi_mari[i + 1] >> (16 - Dim + parte_numar));
            operanzi_mari[i + 1] <<= Dim - parte_numar;
            contor_numere++;
            n_nr++;
        }
        parte_numar = 16 - (Dim - parte_numar + (Dim * (16 / Dim - 1)));
        if (Dim - parte_numar + (Dim * (16 / Dim - 1)) >= Dim)
        {
            parte_numar -= Dim;
            contor_rest = 0;
        }
        else
        {
            contor_rest = 1;
        }
    }

    for (int i = 0; i < (int)N; i++)
    {
        if ((Op[i] == 2 || Op[i] == 3) && i != (int)N - 1)
        {
            ramas++;
            if (primul == 0)
            {
                primul = 1;
                rezultat_1 = operanzi[i];
                operanzi[i] = 0;
            }
        }

        else if (Op[i - 1] == 2 || Op[i - 1] == 3)
        {
            for (int j = i - ramas; j < i && primul == 1; j++)
            {

                if (Op[j] == 2)
                {
                    rezultat_1 *= operanzi[j + 1];
                    operanzi[j + 1] = 0;
                }
                else if (Op[j] == 3)
                {
                    rezultat_1 /= operanzi[j + 1];
                    operanzi[j + 1] = 0;
                }
            }
            if (Op[i - ramas - 1] == 0 || i - ramas < 1)
                rezultat_2 += rezultat_1;
            else
                rezultat_2 -= rezultat_1;
            ramas = 0;
            rezultat_1 = 0;
            primul = 0;
        }
    }

    rezultat = operanzi[0];

    for (unsigned int i = 0; i < N; i++)
    {
        if (Op[i] == 0)
            rezultat += operanzi[i + 1];
        else if (Op[i] == 1)
            rezultat -= operanzi[i + 1];
    }

    rezultat += rezultat_2;

    printf("%d\n", rezultat);

    return 0;
}