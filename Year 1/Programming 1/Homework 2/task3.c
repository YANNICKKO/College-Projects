#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *text, *text_ramas, *temp_char, *mini_text, **n_grama, **temp_matrice;
    int dim_max_text = 1, dim_actuala_text = 0, alocare_check = 0;
    int *nr_aparitii, *temp_int;
    int ok = 0, dim_actuala_matrice = 0, dim_max_matrice = 1;

    // alocare dinamica
    text = (char *)calloc(dim_max_text, sizeof(char));

    if (text == NULL)
    {
        printf("Unde e memoria boss???1");
        return;
    }

    while (alocare_check == 0)
    {
        if (dim_actuala_text > dim_max_text)
        {
            dim_max_text *= 2;
            temp_char = realloc(text, dim_max_text);
            if (temp_char == NULL)
            {
                printf("Unde e memoria, boss???2");
                break;
            }
            else
                text = temp_char;
        }

        text[dim_actuala_text] = getchar();

        switch (text[dim_actuala_text])
        {
        case ',':
        case '.':
        case '!':
        case ';':
            continue;
            break;
        case '\n':
            if (text[dim_actuala_text - 1] == ' ')
                continue;
            else
                text[dim_actuala_text] = ' ';
            break;
        case EOF:
            text[dim_actuala_text] = '\0';
            alocare_check = 1;
            break;
        }

        dim_actuala_text++;
    }

    //========================

    mini_text = strtok(text, " ");
    text_ramas = mini_text;
    mini_text = strtok(NULL, " ");

    n_grama = (char **)calloc(dim_max_matrice, sizeof(char *));
    if (n_grama == NULL)
    {
        printf("Unde e memoria boss???3");
        return;
    }

    nr_aparitii = (int *)calloc(dim_max_matrice, sizeof(int));
    if (nr_aparitii == NULL)
    {
        printf("Unde e memoria boss???4");
        return;
    }

    while (mini_text != NULL)
    {

        if (dim_actuala_matrice > dim_max_matrice)
        {
            dim_max_matrice *= 2;
            temp_matrice = (char **)realloc(n_grama, dim_max_matrice * sizeof(char *));
            temp_int = (int *)realloc(nr_aparitii, dim_max_matrice * sizeof(int));
            if (temp_matrice == NULL)
            {
                printf("Unde e memoria, boss???5%d %d", dim_max_matrice, dim_actuala_matrice);
                break;
            }
            else
                n_grama = temp_matrice;
            if (temp_int == NULL)
            {
                printf("Unde e memoria, boss???6");
                break;
            }
            else
            {
                nr_aparitii = temp_int;
            }
        }
        ok = 0;
        n_grama[dim_actuala_matrice] = (char *)calloc(strlen(mini_text) + strlen(text_ramas) + 4, sizeof(char));

        if (n_grama[dim_actuala_matrice] == NULL)
        {
            for (int i = 0; i < dim_actuala_matrice; i++)
                free(n_grama[i]);
            free(n_grama);
        }

        strcpy(n_grama[dim_actuala_matrice], text_ramas);
        strcat(n_grama[dim_actuala_matrice], " ");
        strcat(n_grama[dim_actuala_matrice], mini_text);

        for (int i = 0; i < dim_actuala_matrice && ok == 0; i++)
        {
            if ((strcmp(n_grama[i], n_grama[dim_actuala_matrice])) == 0)
            {
                free(n_grama[dim_actuala_matrice]);
                nr_aparitii[i]++;
                ok = 1;
            }
        }

        text_ramas = mini_text;
        mini_text = strtok(NULL, " ");

        if (!ok)
        {
            nr_aparitii[dim_actuala_matrice] = 1;
            dim_actuala_matrice++;
        }
    }

    printf("%d\n", dim_actuala_matrice);

    for (int i = 0; i < dim_actuala_matrice; i++)
    {
        printf("%s %d\n", n_grama[i], nr_aparitii[i]);
    }
    for (int i = 0; i < dim_actuala_matrice; i++)
        free(n_grama[i]);
    free(n_grama);
    free(text);
    free(nr_aparitii);

    return 0;
}