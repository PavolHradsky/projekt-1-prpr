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

#define MAX 100

int main(void){

    FILE *fr;
    char str[MAX];
    int poc = 0;
    fr = fopen("pacienti.txt", "r");

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

    return 0;
}










/*
int main(void){

    char znak;
    char *meno = (char*) calloc(10, MAX + 1);
    char riadok[MAX];

    FILE *fr;
    fr = fopen("pacienti.txt", "r");
    int poc = 0;
    while((fgets(riadok, MAX, fr)) != NULL){
        poc++;
    }
    rewind(fr);
    while((fgets(riadok, MAX, fr)) != NULL){
        
    }


    return 0;
}
*/









/*
int main(void){


    char **meno, **diagnoza, **vysetrenie;
    int *rcislo, *datum;
    double *vysledok;

    FILE *fr;
    char riadok[MAX];
    fr = fopen("pacienti.txt", "r");

    int i = 0;
    while(fgets(riadok, MAX, fr) != NULL){
        i++;
    }

    int velkost = i / 7;
    printf("%d\n", velkost);
    fseek(fr, 0, SEEK_SET);

    meno = (char**) malloc(velkost * sizeof(char*));
    diagnoza = (char**) malloc(velkost * sizeof(char*));
    vysetrenie = (char**) malloc(velkost * sizeof(char*));
    rcislo = (int*) malloc(velkost * sizeof(int));
    datum = (int*) malloc(velkost * sizeof(int));
    vysledok = (double*) malloc(velkost * sizeof(double));

    i = 0;
    while(fgets(riadok, MAX, fr) != NULL){
        switch (i%7){
            case 0:
                meno[i * velkost] = strdup(riadok);
                break;
            case 1:
                sscanf(riadok, "%d", *(rcislo + velkost));
                break;
            case 2:
                diagnoza[i] = strdup(riadok);
                break;
            case 3:
                vysetrenie[i] = strdup(riadok);
                break;
            case 4:
                sscanf(riadok, "%.4lf", *(vysledok + velkost));
                break;
            case 5:
                sscanf(riadok, "%d", *(datum + velkost));
                break;
            default:
                break;
                

        strcpy(riadok, "");
        i++;
        }
    }

    for(int j = 0; j <= velkost; j++){
        printf("%s", meno[j]);
    }

    fclose(fr);

    return 0;
}
*/