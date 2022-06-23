// KONING YANNICK 312CB
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structuri.h"

int codHash(void *element)
{
    TCuvant *cuvant = (TCuvant *)element;
    char *nume = cuvant->nume;
    if (*nume >= 'a' && *nume <= 'z')
        return *nume - 'a';
    return *nume - 'A';
}
/*eliberarea celei de-a doua lista din structura*/
void eliberareSubTH(TLG LG)
{
    TLungime *lung = (TLungime *)LG->info;
    TLG el = lung->lista, aux;
    for (; el != NULL;)
    {
        aux = el;
        el = el->urm;
        free(aux->info);
        free(aux);
    }
}
/*functie distrugere din laborator*/
void DistrTH(TH **ah)
{
    TLG *p, el, aux;

    /* parcurgere cu pointeri */
    for (p = (*ah)->v; p < (*ah)->v + (*ah)->M; p++)
    {
        /* daca exista elemente corespunzatoare acestui hash
        eliberam info din celula si apoi eliberam celula */
        for (el = *p; el != NULL;)
        {
            aux = el;
            el = el->urm;
            eliberareSubTH(aux);
            free(aux->info);
            free(aux);
        }
    }
    free((*ah)->v);
    free(*ah);
    *ah = NULL;
}

int main(int argc, char *argv[])
{
    TH *h = NULL;
    /* calcul dimensiuni maxime pt tabela hash */
    size_t M = ('Z' - 'A' + 1);
    /* initializare tabela hash */
    h = (TH *)InitTH(M, codHash);
    if (h == NULL)
        return 0;

    char str[100], *cuv;

    FILE *f;
    f = fopen(argv[1], "rt");
    if (f == NULL)
        return 0;

    /*citire rand cu rand*/
    while (fgets(str, 100, f))
    {
        cuv = strtok(str, " .,;:?!'\n");
        /*insert sau print*/
        if (!strcmp(cuv, "insert"))
        {
            cuv = strtok(NULL, " .,;:?!'\n");
            while (cuv)
            {
                if (strlen(cuv) >= 3 && (cuv[0] < '0' || cuv[0] > '9'))
                {
                    /*daca cuvantul este mai mare de 3 litere si nu este cifra inseram*/
                    InsTH(h, cuv);
                }
                cuv = strtok(NULL, " .,;:?!'\n");
            }
        }
        else if (!strcmp(cuv, "print"))
        {
            char *prima_com, *a_doua_com;
            prima_com = strtok(NULL, " .,;:?!'\n");
            a_doua_com = strtok(NULL, " .,;:?!'\n");
            /*in functie de existentei celui de-al doilea cuvant
            si de al treilea ne uitam ce tip de printare este*/
            if (prima_com == NULL)
                print1(h);
            else if (a_doua_com == NULL)
                print2(h, atoi(prima_com));
            else
                print3(h, codHash(prima_com), (size_t)(atoi(a_doua_com)));
        }
    }
    /*dezalocare*/
    DistrTH(&h);
    return 0;
}