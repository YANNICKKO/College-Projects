#include <stdio.h>
#include <string.h>

char rotire(char rotit, int nr_rotiri)
{
    char cifru;
    if (rotit >= 'a' && rotit <= 'z')
    {
        cifru = (rotit - nr_rotiri - 'z') % 26 + 'z';
    }
    else if (rotit >= 'A' && rotit <= 'Z')
    {
        cifru = (rotit - nr_rotiri - 'Z') % 26 + 'Z';
    }
    else if (rotit >= '0' && rotit <= '9')
    {
        cifru = (rotit - nr_rotiri - '9') % 10 + '9';
    }
    return cifru;
}

int main()
{
    char cod[10], text[1000];
    int cheie_1, cheie_3;
    char cheie_2[10], numar_1[1000], numar_2[1000];
    char cifru_tot[1000];
    scanf("%s", cod);

    if (!(strcmp(cod, "caesar")))
    {
        scanf("%d", &cheie_1);
        scanf("%s", text);
        cifru_tot[strlen(text)] = '\0';
        for (unsigned int i = 0; i < strlen(text); i++)
        {
            cifru_tot[i] = rotire(text[i], cheie_1);
        }
    }

    //-----------------------

    else if (!(strcmp(cod, "vigenere")))
    {
        scanf("%s", cheie_2);
        scanf("%s", text);
        cifru_tot[strlen(text)] = '\0';
        for (long unsigned int i = 0; i < strlen(text); i++)
        {
            cifru_tot[i] = rotire(text[i], cheie_2[i % (strlen(cheie_2))] - 'A');
        }
    }

    //------------------------

    else if (!(strcmp(cod, "addition")))
    {
        int ramas = 0;
        long unsigned int maxim_length = 0;
        scanf("%d\n", &cheie_3);
        scanf("%s", numar_1);
        scanf("%s", numar_2);

        for (long unsigned int i = 0; i < strlen(numar_1); i++)
            numar_1[i] = rotire(numar_1[i], cheie_3);
        for (long unsigned int i = 0; i < strlen(numar_2); i++)
            numar_2[i] = rotire(numar_2[i], cheie_3);

        maxim_length = (strlen(numar_1) > strlen(numar_2)) ? strlen(numar_1) : strlen(numar_2);

        cifru_tot[maxim_length + 1] = '\0';

        for (unsigned int i = 0; i < maxim_length; i++)
        {
            cifru_tot[maxim_length - i] = (strlen(numar_1) > i) ? numar_1[strlen(numar_1) - 1 - i] : '0';
            cifru_tot[maxim_length - i] += (strlen(numar_2) > i) ? numar_2[strlen(numar_2) - 1 - i] : '0';
            cifru_tot[maxim_length - i] += ramas;
            if (cifru_tot[maxim_length - i] - '0' > '9')
            {
                cifru_tot[maxim_length - i] = ((cifru_tot[maxim_length - i] - '0') % ('9' + 1)) + '0';
                ramas = 1;
            }
            else
            {
                cifru_tot[maxim_length - i] -= '0';
                ramas = 0;
            }
        }
        cifru_tot[0] = ramas + '0';

        // scoatere de 0-uri
        if (cifru_tot[0] == '0')
        {
            unsigned int nr_0_uri = 0;
            while (cifru_tot[nr_0_uri] == '0' && nr_0_uri != maxim_length)
                nr_0_uri++;
            memmove(cifru_tot, cifru_tot + nr_0_uri, maxim_length - nr_0_uri + 2);
        }
    }

    printf("%s\n", cifru_tot);

    return 0;
}