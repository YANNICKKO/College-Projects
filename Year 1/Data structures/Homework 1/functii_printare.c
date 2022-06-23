/*KONING YANNICK 312CB*/
#include "structuri.h"

int cautareLungime(void *element, size_t lungime)
{
    TLungime *lung = (TLungime *)element;
    return (lung->lungime == lungime);
}

int cautaFrecventaMica(void *element, int frecventa)
{
    TCuvant *cuvant = (TCuvant *)element;
    if (cuvant->frecventa <= frecventa)
        return 1;
    return 0;
}

int cautaFrecventaMare(void *element, int frecventa)
{
    TLungime *lung = (TLungime *)element;
    TLG *LG = &lung->lista;

    if (!*LG)
    {
        return 0;
    }
    for (; *LG != NULL; LG = &(*LG)->urm)
    {
        if (cautaFrecventaMica((*LG)->info, frecventa))
            return 1;
    }
    return 0;
}

void afisareCuvant1(void *element)
{
    TCuvant *cuvant = (TCuvant *)element;
    printf("%s/%d", cuvant->nume, cuvant->frecventa);
}

void afisareCuvant2(void *element)
{
    TCuvant *cuvant = (TCuvant *)element;
    printf(", %s/%d", cuvant->nume, cuvant->frecventa);
}

void Afisare(TLG *aL)
{
    int ok = 0;
    if (!*aL)
    {
        printf("Lista vida\n");
        return;
    }

    for (; *aL; aL = &(*aL)->urm)
    {
        if (ok == 1)
            afisareCuvant2((*aL)->info); /*daca nu e primul*/
        else
            afisareCuvant1((*aL)->info); /*daca e primul*/
        ok = 1;
    }
}

void afisareLungime(void *element)
{
    TLungime *lung = (TLungime *)element;
    printf("(%zu:", lung->lungime);
    Afisare(&lung->lista);
    printf(")");
}

int afisareCuvant1Frecv(void *element, int frecventa)
{
    TCuvant *cuvant = (TCuvant *)element;
    if (cuvant->frecventa <= frecventa)
    {
        printf("%s/%d", cuvant->nume, cuvant->frecventa);
        return 1;
    }
    return 0;
}

void afisareCuvant2Frecv(void *element, int frecventa)
{
    TCuvant *cuvant = (TCuvant *)element;
    if (cuvant->frecventa <= frecventa)
        printf(", %s/%d", cuvant->nume, cuvant->frecventa);
}

void AfisareFrecv(TLG *aL, int frecventa)
{
    if (!*aL)
    {
        printf("Lista vida\n");
        return;
    }
    int ok = 0;
    for (; *aL; aL = &(*aL)->urm)
    {
        if (ok == 1)
            afisareCuvant2Frecv((*aL)->info, frecventa); /*daca nu e primul*/
        else
        {
            if (afisareCuvant1Frecv((*aL)->info, frecventa)) /*daca e primul*/
                ok = 1;
        }
    }
}

void afisareLungimeFrecv(void *element, int frecventa)
{
    TLungime *lung = (TLungime *)element;

    if (cautaFrecventaMare(element, frecventa))
    {
        printf("(%zu: ", lung->lungime);
        AfisareFrecv(&lung->lista, frecventa);
        printf(")");
    }
}

void print1(TH *ah)
{
    TLG p, el;
    long unsigned int i;
    for (i = 0; i < ah->M; i++)
    {
        p = ah->v[i];
        if (p)
        {
            printf("pos %ld: ", i);
            for (el = p; el != NULL; el = el->urm)
            {
                afisareLungime(el->info);
            }
            printf("\n");
        }
    }
}

void print2(TH *ah, int frecventa)
{
    TLG p, el;
    long unsigned int i;
    for (i = 0; i < ah->M; i++)
    {
        int ok = 0;
        p = ah->v[i];
        if (p)
        {
            for (el = p; el != NULL && ok == 0; el = el->urm)
            {
                if (cautaFrecventaMare(el->info, frecventa)) /*cautam daca exista acea frecventa*/
                    ok = 1;
            }
            if (ok == 1) /*daca exista acea frecventa printam*/
            {
                printf("pos%ld: ", i);
                for (el = p; el != NULL; el = el->urm)
                {
                    afisareLungimeFrecv(el->info, frecventa);
                }
                printf("\n");
            }
        }
    }
}

void print3(TH *ah, int cod, int lungime)
{
    TLG p, el;
    p = ah->v[cod];
    if (p)
    {
        for (el = p; el != NULL; el = el->urm)
        {
            if (cautareLungime(el->info, lungime))
            {
                afisareLungime(el->info);
                printf("\n");
                break;
            }
        }
    }
}
