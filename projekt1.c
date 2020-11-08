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


int v(){ //ready
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
            if (strlen(str) != 11){
                printf("Nekorektne zadany vstup: rodne cislo\n");
                return -1;
            }else{
                printf("rodne cislo: %s", str);
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

int o(int velkost, int *p_datum, char **p_diagnoza){ //ready, este treba upravit aby to islo aj bez alokovanych poli
    int datum, pocet = 0;
    char **arr_diagnozy = (char**) calloc(velkost, sizeof(char*));
    int *arr_pocty = (int*) calloc(velkost, sizeof(int));
    scanf("%d", &datum);
    for(int i = 0; i < velkost; i++){
        if(datum >= p_datum[i]){
            arr_diagnozy[i] = p_diagnoza[i];
            pocet++;
        }
    }
    
    int poc = 0;
    for (int i = 0; i < pocet; i++){
        for (int j = 0; j < pocet; j++){
            if(strcmp(arr_diagnozy[i], arr_diagnozy[j]) == 0){
                poc++;
            }
        }
        arr_pocty[i] = poc;
        poc = 0;
    }
    int max = 0;
    for (int i = 0; i < pocet; i++){
        if(arr_pocty[i] >= max){
            max = arr_pocty[i];
        }
        //printf("%d, ", arr_pocty[i]);
        //printf("%s, ", arr_diagnozy[i]);
    }
    for (int i = 0; i < pocet; i++){
        if(arr_pocty[i] == max){
            printf("Najcastejsie vysetrovana diagnoza do %d je %s.\n", datum, arr_diagnozy[i]);
            return 0;
        }
    }
    free(arr_diagnozy);
    free(arr_pocty);
} 

int n(char ***p_meno, char ***p_diagnoza, char ***p_vysetrenie, char ***p_rcislo, double **p_vysledok, int **p_datum){ //ready
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
    *p_rcislo = (char**) calloc(velkost, sizeof(char*));
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
            str[strlen(str)-1] = 0;
            (*p_rcislo)[i/7] = strdup(str);
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
        printf("%s\n", (*p_meno)[j]);
        printf("%s\n", (*p_rcislo)[j]);
        printf("%s\n", (*p_diagnoza)[j]);
        printf("%s\n", (*p_vysetrenie)[j]);
        printf("%.4lf\n", (*p_vysledok)[j]);
        printf("%d\n", (*p_datum)[j]);
        printf("\n");
    }
*/
    return velkost;
}

int s(int velkost, char **p_vysetrenie, char **p_rcislo, double *p_vysledok){ //ready
    long long rcislo;
    scanf("%lld", &rcislo);
    printf("%s\n", p_rcislo[1]);
    for(int i = 0; i < velkost; i++){
        if(rcislo == atoll(p_rcislo[i])){
            printf("Vysledky vysetreni, ktore boli vykonane pacientovi s rodnym cislom %lld su nasledovne:\n%s: %.2lf\n", atoll(p_rcislo[i]), p_vysetrenie[i], p_vysledok[i]);
            break;
        }
    }
}

void h(int velkost, char **p_rcislo, char **p_diagnoza){ //ready AF
    char diagn[MAX];
    scanf("%s", diagn);
    int vek = 0, j = 0;
    for(int i = 0; i < velkost; i++){
        if (strcmp(diagn, p_diagnoza[i]) == 0){
            j++;
        }
    }
    int pohlavie = 0;
    char **arr_pohlavie = (char**) calloc(j, sizeof(char*));
    int *arr_vek = (int*) calloc(j, sizeof(int));
    j = 0;
    for(int i = 0; i < velkost; i++){
        if (strcmp(diagn, p_diagnoza[i]) == 0){
            if(atoll(p_rcislo[i])/100000000 > 20){
                vek = 2020 - (1900 + atoll(p_rcislo[i])/100000000);
                arr_vek[j] = vek;
            }else{
                vek = 2020 - (2000 + atoll(p_rcislo[i])/100000000);
                arr_vek[j] = vek;
            }
            pohlavie = (atoll(p_rcislo[i])/1000000)%100;
            if(pohlavie < 50){
                arr_pohlavie[j] = "Muz";
            }else{
                arr_pohlavie[j] = "Zena";
            }
            j++;
        }
    }
    int *arr_vek_ktory_uz_bol = (int*) calloc(j, sizeof(int));
    int vek_ktory_uz_bol = 0;
    vek = 0;
    int cislo = 0;
    
    printf("Muzi\n");
    for (int i = 0; i < j; i++){
        if(strcmp(arr_pohlavie[i], "Muz") == 0){
            for(int l = 0; l < j; l++){
                if (arr_vek[i] == arr_vek_ktory_uz_bol[l]){
                    vek_ktory_uz_bol = 1;
                }
            }
            if(vek_ktory_uz_bol == 0){
                if(arr_vek[i] == vek){
                cislo++;
            }else{
                vek = arr_vek[i];
            }
            for (int k = 0; k < j; k++){
                if(arr_vek[k] == vek && strcmp(arr_pohlavie[k], "Muz") == 0){
                    cislo++;
                }else{
                    vek = arr_vek[i];
                }
            }
            printf("%d: %d\n", arr_vek[i], cislo);
            }
            arr_vek_ktory_uz_bol[i] = arr_vek[i]; 
        }
        cislo = 0;
        vek_ktory_uz_bol = 0;
    }
    
    for (int i = 0; i < j; i++){
        arr_vek_ktory_uz_bol[i] = 0;
    }
    
    
    printf("Zeny\n");
    for (int i = 0; i < j; i++){
        if(strcmp(arr_pohlavie[i], "Zena") == 0){
            for(int l = 0; l < j; l++){
                if (arr_vek[i] == arr_vek_ktory_uz_bol[l]){
                    vek_ktory_uz_bol = 1;
                }
            }
            if(vek_ktory_uz_bol == 0){
                if(arr_vek[i] == vek){
                cislo++;
            }else{
                vek = arr_vek[i];
            }
            for (int k = 0; k < j; k++){
                if(arr_vek[k] == vek && strcmp(arr_pohlavie[k], "Zena") == 0){
                    cislo++;
                }else{
                    vek = arr_vek[i];
                }
            }
            printf("%d: %d\n", arr_vek[i], cislo);
            }
            arr_vek_ktory_uz_bol[i] = arr_vek[i]; 
        }
        cislo = 0;
        vek_ktory_uz_bol = 0;
    }
}

void p(int velkost, char **p_meno, char **p_diagnoza, char **p_vysetrenie, char **p_rcislo, double *p_vysledok, int *p_datum){//ready
    int datum;
    long long rcislo;
    char vysetrenie[MAX];
    double vysledok;
    scanf("%lld", &rcislo);
    scanf("%s", &vysetrenie);
    scanf("%d", &datum);
    scanf("%lf", &vysledok);
    for(int i = 0; i < velkost; i++){
        if(rcislo == atoll(p_rcislo[i]) && strcmp(vysetrenie, p_vysetrenie[i]) == 0){
            printf("Pacientovi s rodnym cislom %lld bol zmeneny vysledok vysetrenia %s z povodnej hodnoty %.2lf na novu hodnotu %.2lf\n", atoll(p_rcislo[i]), p_vysetrenie[i], p_vysledok[i], vysledok);
            p_vysledok[i] = vysledok;
            p_datum[i] = datum;
            FILE *fr;
            fr = fopen("pacienti.txt", "w");
            for(int j = 0; j < velkost; j++){
                fprintf(fr, "%s\n", p_meno[j]);
                fprintf(fr, "%s\n", p_rcislo[j]);
                fprintf(fr, "%s\n", p_diagnoza[j]);
                fprintf(fr, "%s\n", p_vysetrenie[j]);
                fprintf(fr, "%.2lf\n", p_vysledok[j]);
                fprintf(fr, "%d\n", p_datum[j]);
                fprintf(fr, "\n");
            }
            
            break;
        }
    }
    
}

void z(int velkost, char **p_meno, char **p_vysetrenie, int *p_datum, double *p_vysledok){ //ready
    int date1, date2;
    double max1 = 0, max2 = 0, max3 = 0;
    char vysetrenie[MAX];
    scanf("%d", &date1);
    scanf("%d", &date2);
    scanf("%s", &vysetrenie);
    double *vysledok = (double*) calloc(velkost, sizeof(double));
    
    for (int i = 0; i < velkost; i++)
    {
        if(p_datum[i] >= date1 && p_datum[i] <= date2 && strcmp(vysetrenie, p_vysetrenie[i]) == 0){
            vysledok[i] = p_vysledok[i];
        }
    }
    
    for (int i = 0; i < velkost; i++)
    {
        if (vysledok[i] >= max1){
            max1 = vysledok[i];
        }else if (vysledok[i] >= max2){
            max2 = vysledok[i];
        }else if (vysledok[i] >= max3){
            max3 = vysledok[i];
        }
    }
    for (int i = 0; i < velkost; i++)
    {
        if(max1 == p_vysledok[i]){
            printf("%s (%.2lf)\n", p_meno[i], max1);
        }
        if(max2 == p_vysledok[i]){
            printf("%s (%.2lf)\n", p_meno[i], max2);
        }
        if(max3 == p_vysledok[i]){
            printf("%s (%.2lf)\n", p_meno[i], max3);
        }
    }
    free(vysledok);
}

void k(char ***p_meno, char ***p_diagnoza, char ***p_vysetrenie, char ***p_rcislo, double **p_vysledok, int **p_datum){ //empty
    free(*p_meno);
    free(*p_diagnoza);
    free(*p_vysetrenie);
    free(*p_rcislo);
    free(*p_vysledok);
    free(*p_datum);
}

int main(void){ //main

    char **meno, **diagnoza, **vysetrenie, **rcislo;
    int *datum;
    double *vysledok;

    v();
    int velkost = n(&meno, &diagnoza, &vysetrenie, &rcislo, &vysledok, &datum);
    //o(velkost, datum, diagnoza);
    //s(velkost, vysetrenie, rcislo, vysledok);
    //p(velkost, meno, diagnoza, vysetrenie, rcislo, vysledok, datum);
    //h(velkost, rcislo, diagnoza);
    //z(velkost, meno, vysetrenie, datum, vysledok);
    k(&meno, &diagnoza, &vysetrenie, &rcislo, &vysledok, &datum);
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
