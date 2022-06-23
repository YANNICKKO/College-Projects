/*KONING YANNICK 312CB*/
#include "structuri.h"

TH *InitTH(size_t M, TFHash fh)
{
    TH *h = (TH *)calloc(sizeof(TH), 1);
    if (!h)
    {
        printf("eroare alocare hash\n");
        return NULL;
    }

    h->v = (TLG *)calloc(M, sizeof(TLG));
    if (!h->v)
    {
        printf("eroare alocare vector de pointeri TLG in hash\n");
        free(h);
        return NULL;
    }

    h->M = M;
    h->fh = fh;
    return h;
}

int cmpLungime(void *e1, void *e2)
{
    TLungime *lung1 = (TLungime *)e1;
    TLungime *lung2 = (TLungime *)e2;

    if (lung1->lungime < lung2->lungime)
        return 0;
    return 1;
}

TLungime *Ins_IncLG1(TLG *aL, char *cuvant)
{
    TLG aux = malloc(sizeof(TCelulaG));
    if (!aux)
        return 0;
    TLungime *lung = malloc(sizeof(TLungime));
    lung->lungime = strlen(cuvant);
    lung->lista = NULL;
    aux->info = lung;

    TLG el, ant;

    for (ant = NULL, el = *aL; el != NULL; ant = el, el = el->urm)
    {
        if (cmpLungime(el->info, aux->info) == 1) /*cautam unde sa inseram in fucntie de nr de litere*/
        {
            break;
        }
    }
    if (ant == NULL)
    {
        aux->urm = *aL;
        *aL = aux;
        return lung;
    }
    else
    {
        ant->urm = aux;
        aux->urm = el;
        return lung;
    }
}

int cmpNume(void *el, char *cuv2)
{
    TCuvant *cuv1 = (TCuvant *)el;

    if (strcmp(cuv1->nume, cuv2) == 0)
        return 2;
    else if (strcmp(cuv1->nume, cuv2) > 0)
        return 1;
    return 0;
}

void schimbFrecv(void *el, int *frecv)
{
    TCuvant *cuv = (TCuvant *)el;
    *frecv = cuv->frecventa;
}

int cmpFrecv(void *e1, int frecv2)
{
    TCuvant *cuv1 = (TCuvant *)e1;

    if (cuv1->frecventa < frecv2)
        return 2;
    if (cuv1->frecventa == frecv2)
        return 1;
    return 0;
}

int Ins_IncLG2(TLG *aL, char *cuv_str, int frecv)
{
    TLG aux = malloc(sizeof(TCelulaG));
    if (!aux)
        return 0;
    TCuvant *cuvant = malloc(sizeof(TCuvant));
    strcpy(cuvant->nume, cuv_str);
    cuvant->frecventa = frecv;
    aux->info = cuvant;

    TLG ant = NULL, el;

    for (ant = NULL, el = *aL; el != NULL; ant = el, el = el->urm)
    {
        if (cmpNume(el->info, cuv_str) == 2)
        {
            schimbFrecv(el->info, &frecv);
            frecv++; /*crestem frecventa daca gasim cuvantul*/
            /*dezalocam celula si apelam din nou functia cu o frecventa mai mare*/
            free(cuvant);
            free(aux);

            if (ant != NULL)
            {
                ant->urm = el->urm;
            }
            else
            {
                *aL = el->urm;
            }
            free(el->info);
            free(el);
            Ins_IncLG2(aL, cuv_str, frecv);
            return 1;
        }
    }
    for (ant = NULL, el = *aL; el != NULL; ant = el, el = el->urm)
    {
        /*cautam unde sa inseram in functie de frecventa mai mare si oridine lesico-grafica*/
        if (cmpFrecv(el->info, cuvant->frecventa) == 2)
            break;
        else if (cmpFrecv(el->info, cuvant->frecventa) && cmpNume(el->info, cuv_str))
            break;
    }
    if (ant != NULL)
    {
        ant->urm = aux;
        aux->urm = el;
        return 1;
    }

    aux->urm = *aL;
    *aL = aux;
    return 1;
}

int InsTH(TH *a, char *cuvant)
{
    int cod = a->fh(cuvant), ok = 0;
    TLG el;
    TLungime *lung;

    for (el = a->v[cod]; el != NULL && ok == 0; el = el->urm)
    {
        TLungime *lung_aux = (TLungime *)el->info;
        /*cautam daca exista celula deja*/
        if (lung_aux->lungime == strlen(cuvant))
        {
            lung = lung_aux;
            ok = 1;
        }
    }
    if (ok == 0)
    {
        /*daca nu exista o inseram*/
        lung = Ins_IncLG1(a->v + cod, cuvant);
    }
    /*inseram in a doua lista*/
    Ins_IncLG2(&lung->lista, cuvant, 1);

    return 1;
}
