/*
* FIIT STU
* Proceduralne Programovanie
* Autor: Pavol Hradsky

* Program: Projekt 1
*/

#include<stdio.h>//poznamka
#include<stdlib.h>
#include<string.h>

#define MAX 50

void v(){
    FILE *fr;
    char riadok[MAX];
    fr = fopen("pacienti.txt", "r");
    
    while(fgets(riadok, MAX, fr) != NULL){
        printf("%s", riadok);
    }
    
    fclose(fr);
}

int main(void){

    v();

    return 0;
}