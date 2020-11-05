/*
* FIIT STU
* Proceduralne Programovanie
* Autor: Pavol Hradsky

* Program: Projekt 1
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>//poznamka
#include<stdlib.h>
#include<string.h>

#define MAX 50

int v(){
    FILE *fr;
    char str[MAX];
    int poc = 0;
    if((fr = fopen("pacienti.txt", "r")) == NULL){
        printf("Neotvoreny subor\n");
        return -1;
    }

    while ((fgets(str, MAX, fr)) != NULL){
        poc++;
    }
    rewind(fr);
    int velkost = poc/7 + 1;
    long long x;
    for(int i = 0; i < poc; i++){
        fgets(str, MAX, fr);
        switch (i%7)
        {
        case 0:
            printf("meno a priezvisko: %s", str);
            break;
        case 1:
            x = atoll(str);
            if((x > 999999999) && (x < 10000000000) && (x%11 == 0)){
                printf("rodne cislo: %s", str);
            }else{
                printf("Nekorektne zadany vstup: rodne cislo\n");
                return -1;
            }
            break;
        case 2:
            if(str[0] > 64 && str[0] < 91){//doplnit
                printf("diagnoza: %s", str);
            }else{
                printf("Nekorektne zadany vstup: diagnoza\n");
                return -1;
            }
            break;
        case 3:
            printf("vysetrenie: %s", str);
            break;
        case 4:
            if(atof(str) >= 0 && atof(str) <= 1000){
            printf("vysledok: %s", str);
            }else{
                printf("Nekorektne zadany vstup: vysledok\n");
                return -1;
            }
            break;
        case 5:
            if(atoi(str) > 9999999 && atoi(str) < 100000000){
            printf("datum: %s", str);
            }else{
                printf("Nekorektne zadany vstup: datum\n");
                return -1;
            }
            break;
        case 6:
            printf("\n");
        default:
            break;
        }
        
    }
    printf("\n");
    fclose(fr);

    return velkost;

}

int n(char ***p_meno, char ***p_diagnoza, char ***p_vysetrenie, long long **p_rcislo, double **p_vysledok, int **p_datum){
    FILE *fr;
    char str[MAX];
    int poc = 0;
    if((fr = fopen("pacienti.txt", "r")) == NULL){
        printf("Neotvoreny subor\n");
        return 1;
    }

    while ((fgets(str, MAX, fr)) != NULL){
        poc++;
    }
    rewind(fr);
    int velkost = poc/7 + 1;

    *p_meno = (char**) calloc(velkost, sizeof(char*));
    *p_diagnoza = (char**) calloc(velkost, sizeof(char*));
    *p_vysetrenie = (char**) calloc(velkost, sizeof(char*));
    *p_rcislo = (long long*) calloc(velkost, sizeof(long long));
    *p_datum = (int*) calloc(velkost, sizeof(int));
    *p_vysledok = (double*) calloc(velkost, sizeof(double));
    for(int i = 0; i < poc; i++){
        fgets(str, MAX, fr);
        switch (i%7)
        {
        case 0:
            str[strlen(str)-1] = 0;
            (*p_meno)[i/7] = strdup(str);
            break;
        case 1:
            (*p_rcislo)[i/7] = atoll(strdup(str));
            break;
        case 2:
            str[strlen(str)-1] = 0;
            (*p_diagnoza)[i/7] = strdup(str);
            break;
        case 3:
            str[strlen(str)-1] = 0;
            (*p_vysetrenie)[i/7] = strdup(str);
            break;
        case 4:
            (*p_vysledok)[i/7] = atof(strdup(str));
            break;
        case 5:
            (*p_datum)[i/7] = atoi(strdup(str));
            break;
        default:
            break;
        }
    }
    fclose(fr);
/*
    for (int j = 0; j < velkost; j++){
        printf("%s", (*p_meno)[j]);
        printf("%lld\n", (*p_rcislo)[j]);
        printf("%s", (*p_diagnoza)[j]);
        printf("%s", (*p_vysetrenie)[j]);
        printf("%.4lf\n", (*p_vysledok)[j]);
        printf("%d\n", (*p_datum)[j]);
        printf("\n");
    }
*/
    return velkost;
}

int s(int velkost, char **p_vysetrenie, long long *p_rcislo, double *p_vysledok){
    long long rcislo;
    scanf("%lld", &rcislo);
    printf("%lld\n", p_rcislo[1]);
    for(int i = 0; i < velkost; i++){
        if(rcislo == p_rcislo[i]){
            printf("Vysledky vysetreni, ktore boli vykonane pacientovi s rodnym cislom %lld su nasledovne:\n%s: %.2lf\n", p_rcislo[i], p_vysetrenie[i], p_vysledok[i]);
            break;
        }
    }
}

void o(int velkost, int *p_datum, char **p_diagnoza){ //not ready
    int date;
    scanf("%d", &date);
    for(int i = 0; i < velkost; i++){
        if(date >= p_datum[i]){
            printf("%s", p_diagnoza[i]);

        }
    }
} 

void p(int velkost, char **p_meno, char **p_diagnoza, char **p_vysetrenie, long long *p_rcislo, double *p_vysledok, int *p_datum){
    int datum;
    long long rcislo;
    char vysetrenie[MAX];
    double vysledok;
    scanf("%lld", &rcislo);
    scanf("%s", &vysetrenie);
    scanf("%d", &datum);
    scanf("%lf", &vysledok);
    for(int i = 0; i < velkost; i++){
        if(rcislo == (p_rcislo)[i] && strcmp(vysetrenie, p_vysetrenie[i]) == 0){
            
            printf("Pacientovi s rodnym cislom %lld bol zmeneny vysledok vysetrenia %s z povodnej hodnoty %.2lf na novu hodnotu %.2lf", p_rcislo[i], p_vysetrenie[i], p_vysledok[i], vysledok);
            
        }
    }
}

int main(void){

    char **meno, **diagnoza, **vysetrenie;
    long long *rcislo;
    int *datum;
    double *vysledok;

    v();
    int velkost = n(&meno, &diagnoza, &vysetrenie, &rcislo, &vysledok, &datum);
    //o(velkost, datum, diagnoza);
    //s(velkost, vysetrenie, rcislo, vysledok);
    //p(velkost, meno, diagnoza, vysetrenie, rcislo, vysledok, datum);

    
    return 0;
}

/*
void o(int velkost, int *datum, char **diagnoza){
    int date;
    scanf("%d", &date);
    for(int i = 0; i < velkost; i++){
        if(date >= datum[i]){
            printf("%s", diagnoza[i]);

        }
    }
} 

int s(int velkost, char **p_vysetrenie, long long *p_rcislo, double *p_vysledok){
    long long cislo;
    scanf("%lld", &cislo);
    printf("%lld\n", p_rcislo[1]);
    for(int i = 0; i < velkost; i++){
        if(cislo == p_rcislo[i]){
            printf("Vysledky vysetreni, ktore boli vykonane pacientovi s rodnym cislom %lld su nasledovne:\n%s: %.2lf\n", p_rcislo[i], p_vysetrenie[i], p_vysledok[i]);
            break;
        }
    }
}

int vek(int rc){

}

int h(int velkost, long long *p_rcislo, char **p_diagnoza){
    char diagn[MAX];
    scanf("%s", diagn);

}

int main(void){

    FILE *fr;
    char str[MAX];
    int poc = 0;
    if((fr = fopen("pacienti.txt", "r")) == NULL){
        printf("Neotvoreny subor\n");
        return 1;
    }

    while ((fgets(str, MAX, fr)) != NULL){
        poc++;
    }
    rewind(fr);
    int velkost = poc/7 + 1;

    char **meno = (char**) calloc(velkost, sizeof(char*));
    char **diagnoza = (char**) calloc(velkost, sizeof(char*));
    char **vysetrenie = (char**) calloc(velkost, sizeof(char*));
    long long *rcislo = (long long*) calloc(velkost, sizeof(long long));
    int *datum = (int*) calloc(velkost, sizeof(int));
    double *vysledok = (double*) calloc(velkost, sizeof(double));
    for(int i = 0; i < poc; i++){
        fgets(str, MAX, fr);
        switch (i%7)
        {
        case 0:
            meno[i/7] = strdup(str);
            break;
        case 1:
            rcislo[i/7] = atoll(strdup(str));
            break;
        case 2:
            diagnoza[i/7] = strdup(str);
            break;
        case 3:
            vysetrenie[i/7] = strdup(str);
            break;
        case 4:
            vysledok[i/7] = atof(strdup(str));
            break;
        case 5:
            datum[i/7] = atoi(strdup(str));
            break;
        default:
            break;
        }
    }

    for (int j = 0; j < velkost; j++){
        printf("%s", meno[j]);
        printf("%lld\n", rcislo[j]);
        printf("%s", diagnoza[j]);
        printf("%s", vysetrenie[j]);
        printf("%.4lf\n", vysledok[j]);
        printf("%d\n", datum[j]);
        printf("\n");
    }

    //o(velkost, datum, diagnoza);
    //s(velkost, vysetrenie, rcislo, vysledok);

    return 0;
}
*/