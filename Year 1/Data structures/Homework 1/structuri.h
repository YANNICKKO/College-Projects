/*KONING YANNICK 312CB*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#ifndef _TAB_HASH_
#define _TAB_HASH_

typedef int (*TFHash)(void *); /*cod hash*/

typedef struct celulag
{
    void *info;          /* adresa informatie */
    struct celulag *urm; /* adresa urmatoarei celule */
} TCelulaG, *TLG;

/*hash*/
typedef struct
{
    size_t M;
    TFHash fh;
    TLG *v;
} TH;

/*prima structura cu nr de litere si o lista*/
typedef struct
{
    size_t lungime;
    TLG lista;
} TLungime;

/*a doua structura cu un string si o frecventa*/
typedef struct
{
    char nume[50];
    int frecventa;
} TCuvant;

/*functii inserari*/
TH *InitTH(size_t M, TFHash fh); 			/*functie de initializare tabela Hash (laborator)*/

int cmpLungime(void *e1, void *e2);          		/*functie de comparat lungimea (litere)*/
TLungime *Ins_IncLG1(TLG *aL, char *cuvant); 		/*functie de inserare celula in prima lista (cea din vector)*/

int cmpNume(void *el, char *cuv2);                 	/*functie de compararea cuvintelor (egale sau mai mare)*/	
void schimbFrecv(void *el, int *frecv);            	/*functie de schimbare de frecventa*/
int cmpFrecv(void *e1, int frecv2);                	/*functie comparat frecvente*/
int Ins_IncLG2(TLG *aL, char *cuv_str, int frecv); 	/*functie de inserare in a doua lista (cea cu cuvinte)*/

int InsTH(TH *a, char *cuvant); 			/*functia de inserare*/
/*==========================*/


/*functii printare */
int cautaFrecventaMica(void *element, int frecventa); /*functii cautarera de frecv (pt print 2)*/
int cautaFrecventaMare(void *element, int frecventa); /*functii cautarera de frecv (pt print 2)*/

void afisareCuvant1(void *element); 			/*afisarea informatiei 1 (fara virgula)*/
void afisareCuvant2(void *element); 			/*afisarea informatiei 2 (cu virgula pentru 2 sau mai multe elem)*/
void Afisare(TLG *aL);              			/*afisare interiorul celulei*/
void afisareLungime(void *element); 			/*afisare pos*/

/*aceleasi functii de afisare ca mai sus, dar cu frecventa ca parametru pentru print2*/
int afisareCuvant1Frecv(void *element, int frecventa);
void afisareCuvant2Frecv(void *element, int frecventa);
void AfisareFrecv(TLG *aL, int frecventa);
void afisareLungimeFrecv(void *element, int frecventa);

int cautareLungime(void *element, size_t lungime); 	/*functie de cautare de lungime a cuvintelor (pt al print3)*/

void print1(TH *ah);                       /*printarea 1*/
void print2(TH *ah, int frecventa);        /*printarea 2*/
void print3(TH *ah, int cod, int lungime); /*printarea 3*/
/*==========================*/

#endif
