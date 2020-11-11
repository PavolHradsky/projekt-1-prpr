/*
* FIIT STU
* Proceduralne Programovanie
* Autor: Pavol Hradsky

* Program: Projekt 1
*/

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 100 //definovana maximalna velkost stringu

/*      ----FUNKCIA V----       
* Otvorenie suboru, porovnanie spravnosti a vypisanie hodnot
*/
int v(FILE **fr){ //ready
    //argument - poineter na premennu typu FILE
    char str[MAX];
    int poc = 0;
    //otvorenie subotu pacienti.txt, ak sa nepodari otvorit, vypise a vrati -1
    if((*fr = fopen("pacienti.txt", "r")) == NULL){
        printf("Neotvoreny subor\n");
        return -1;
    }
    //spocitanie riadkov v subore, citanie suboru poriadkoch pomocou fgets
    while ((fgets(str, MAX, *fr)) != NULL){
        poc++;
    }
    rewind(*fr); //vrati kurzor na zaciatok

    int velkost = poc/7 + 1; //vypocita velkost - pocet zaznamov
    //citanie suboru po riadkoch pomocou fgets
    for(int i = 0; i < poc; i++){
        fgets(str, MAX, *fr);
        switch (i%7) //sledujeme cislo riadku a jeho zvysok po deleni 7 (po 7 riadkoch sa typy zaznamov opakuju)
                     //pri kazdom pripade skontrolujeme ci je udaj spravny a vypiseme ho spolu s popisom pred nim
        {
        case 0: //  MENO
            if(strlen(str) > 50 && (atoll(str)%11==0)){ //sledujeme, ci je meno dlhsie ako  50 znakov a ci je delitelne 11
                printf("Nekorektne zadany vstup: meno\n"); //ak ano, program vypise chybu a vrati -1
                return -1;
            }
            printf("meno a priezvisko: %s", str); //vypise nasledujuci retazec a riadok
            break;
        case 1: //  RODNE CISLO
            if (strlen(str) != 11){ //sledujeme, ci je rodne cislo dlhe 11 znakov (aj so znakom konca riadku)
                printf("Nekorektne zadany vstup: rodne cislo\n"); //ak nie, program vypise chybu a vrati -1
                return -1;
            }else{
                printf("rodne cislo: %s", str); //vypise nasledujuci retazec a riadok
            }
            break;
        case 2: //  DIAGNOZA
            if(str[0] > 64 && str[0] < 91 && str[1] >= 48 && str[1] <= 57 && str[2] >= 48 && str[2] <= 57 && strlen(str) == 4){
                //sledujeme, ci je prvy znak velke pismeno a druhy a treti cislo (podla ascii)
                printf("diagnoza: %s", str); //vypise nasledujuci retazec a riadok
            }else{
                printf("Nekorektne zadany vstup: diagnoza\n"); //ak nie, program vypise chybu a vrati -1
                return -1;
            }
            break;
        case 3: //  VYSETRENIE
            if(strlen(str) > 50){ //sledujeme, ci je znakovy retazec kratsi ako 50 znakov
                printf("Nekorektne zadany vstup: vysetrenie\n"); //ak nie, program vypise chybu a vrati -1
                return -1;
            }
            printf("vysetrenie: %s", str); //vypise nasledujuci retazec a riadok
            break;
        case 4: //  VYSLEDOK
            if(atof(str) >= 0 && atof(str) <= 1000){ //sledujeme, ci je realne cislo v intervale <0; 1000>
            printf("vysledok: %s", str);  //vypise nasledujuci retazec a riadok
            }else{
                printf("Nekorektne zadany vstup: vysledok\n"); //ak nie, program vypise chybu a vrati -1
                return -1;
            }
            break;
        case 5: //  DATUM
            if(atoi(str) > 9999999 && atoi(str) < 100000000){ //sledujeme, ci ma cislo 8 cifier
            printf("datum: %s", str); //vypise nasledujuci retazec a riadok
            }else{
                printf("Nekorektne zadany vstup: datum\n"); //ak nie, program vypise chybu a vrati -1
                return -1;
            }
            break;
        case 6: //  KONIEC
            printf("\n"); //vypise novy riadok
        default:
            break;
        }
        
    }
    printf("\n"); //vypise 2 nove riadky pre prehladnost
    printf("\n");

    return velkost; //vrati velkost suboru (pocet zaznamov)

}

/*      ----FUNKCIA O----       
* najcastejsie vysetrovana diagnoza do daneho datumu
* input DATUM
*/
int o(FILE *fr){ //ready
    //argument - premenna s otvorenym suborom
    char str[MAX];
    int poc1 = 0;

    //otvorenie subotu pacienti.txt, ak sa nepodari otvorit, vypise a vrati -1
    if(fr == NULL){
        printf("Neotvoreny subor\n");
        return 1;
    }
    rewind(fr); //vrati kurzor na zaciatok

    //spocitanie riadkov v subore, citanie suboru poriadkoch pomocou fgets
    while ((fgets(str, MAX, fr)) != NULL){
        poc1++;
    }
    rewind(fr); //vrati kurzor na zaciatok
    int velkost = poc1/7 + 1; //vypocita velkost - pocet zaznamov

    //vytvori a alokuje dynamicke polia na diagnozy (2D - pole stringov) a datumy velkosti "velkost"
    char **p_diagnoza;
    int *p_datum;
    p_diagnoza = (char**) calloc(velkost, sizeof(char*));
    p_datum = (int*) calloc(velkost, sizeof(int));

    //citanie suboru po riadkoch pomocou fgets
    for(int i = 0; i < poc1; i++){
        fgets(str, MAX, fr);
        switch (i%7) //sledujeme cislo riadku a jeho zvysok po deleni 7 (po 7 riadkoch sa typy zaznamov opakuju)
                     //sledujeme 2 riadok - diagnoza a 5 riadok - datum
        {
        case 2: //  DIAGNOZA
            str[strlen(str)-1] = 0; //odreze posledny znak - \n
            p_diagnoza[i/7] = strdup(str); //ulozi kopiu riadku do pola diagnoz
            break;
        case 5: //  DATUM
            p_datum[i/7] = atoi(strdup(str)); //skonvertuje na int a ulozi kopiu riadku do pola datumov
            break;
        default:
            break;
        }
    }

    int datum, pocet = 0;
    
    scanf("%d", &datum); //nacita datum

    //pocet zaznamov do daneho datumu
    for(int i = 0; i < velkost; i++){ //postupne prejde vsetky prvky v poli datumy, a porovna ich so zadanym datumom
        if(datum >= p_datum[i]){
            pocet++;  
        }
    }

    //vytvori a alokuje dynamicke polia na diagnozy (2D - pole stringov) a datumy velkosti "pocet" (udaje ktore su do daneho datumu)
    char **arr_diagnozy = (char**) calloc(pocet, sizeof(char*));
    int *arr_pocty = (int*) calloc(pocet, sizeof(int));

    //zisti diagnozy vykonane do daneho datumu a zapise ich do pola arr_diagnozy
    int j = 0; //pocet zaznamov do daneho datumu
    for(int i = 0; i < velkost; i++){
        if(datum >= p_datum[i]){
            arr_diagnozy[j] = p_diagnoza[i];
            j++;
        }
    }

    //zisti pocet kazdej diagnozy v poli, zapise ich paralelne do pola arr_pocty
    //to znamena, ze kazdy prvok arr_diagnozy ma "suseda" v poli arr_pocty s rovnakym indexom, ktory reprezentuje pocet danej diagnozy v poli arr_diagnozy
    int poc = 0;
    for (int i = 0; i < pocet; i++){
        for (int j = 0; j < pocet; j++){ //pre kazdy prvok pola porovna hodnotu s kazdym ostatnym prvkom v tom istom poli
            if(strcmp(arr_diagnozy[i], arr_diagnozy[j]) == 0){
                poc++;
            }
        }
        arr_pocty[i] = poc; //pocet zapise do arr_pocty s rovnakym indexom
        poc = 0;
    }
    //zisti najvacsiu hodnotu v poli arr_pocty (rovnaky index ukazuje na konkretnu diagnozu)
    int max = 0;
    for (int i = 0; i < pocet; i++){
        if(arr_pocty[i] >= max){
            max = arr_pocty[i];
        }
    }

    //zisti ktory prvy prvok arr_pocty je maximum
    for (int i = 0; i < pocet; i++){
        if(arr_pocty[i] == max){
            printf("Najcastejsie vysetrovana diagnoza do %d je %s.\n", datum, arr_diagnozy[i]); //pre najdeny prvok vypise nasledujuci retazec s prvkom z arr_diagnozy s rovnakym indexom
            return 0;
        }
    }

    //uvolni alkovovane polia
    free(p_datum);
    free(p_diagnoza);
    free(arr_diagnozy);
    free(arr_pocty);
} 

/*      ----FUNKCIA N----       
* prepise subor do dynamickych poli pre kazdy udaj
*/
int n(FILE *fr, char ***p_meno, char ***p_diagnoza, char ***p_vysetrenie, char ***p_rcislo, double **p_vysledok, int **p_datum){ //ready
    //argumenty - otvoreny subor a pointre na vsetky polia
    char str[MAX];
    int poc = 0;

    //otvorenie subotu pacienti.txt, ak sa nepodari otvorit, vypise a vrati -1
    if(fr == NULL){
        printf("Neotvoreny subor\n");
        return 1;
    }
    rewind(fr); //vrati kurzor na zaciatok

    //spocitanie riadkov v subore, citanie suboru poriadkoch pomocou fgets
    while ((fgets(str, MAX, fr)) != NULL){
        poc++;
    }
    rewind(fr); //vrati kurzor na zaciatok
    int velkost = poc/7 + 1; //vypocita velkost - pocet zaznamov

    //dynamicky alokuje polia (niektore ako 2D - polia stringov) velkosti "velkost"
    *p_meno = (char**) calloc(velkost, sizeof(char*));
    *p_diagnoza = (char**) calloc(velkost, sizeof(char*));
    *p_vysetrenie = (char**) calloc(velkost, sizeof(char*));
    *p_rcislo = (char**) calloc(velkost, sizeof(char*));
    *p_datum = (int*) calloc(velkost, sizeof(int));
    *p_vysledok = (double*) calloc(velkost, sizeof(double));

    //citanie suboru po riadkoch pomocou fgets
    for(int i = 0; i < poc; i++){
        fgets(str, MAX, fr); 
        switch (i%7) //sledujeme cislo riadku a jeho zvysok po deleni 7 (po 7 riadkoch sa typy zaznamov opakuju)
                     //kazdy riadok prekonvertujem na spravnu formu a zapisem ho do spravneho pola
        {
        case 0:
            str[strlen(str)-1] = 0; //z riadku vymazeme posledny znak (\n)
            (*p_meno)[i/7] = strdup(str); //riadok skopirujeme do spravneho pola
            break;
        case 1:
            str[strlen(str)-1] = 0; //z riadku vymazeme posledny znak (\n)
            (*p_rcislo)[i/7] = strdup(str); //riadok skopirujeme do spravneho pola
            break;
        case 2:
            str[strlen(str)-1] = 0; //z riadku vymazeme posledny znak (\n)
            (*p_diagnoza)[i/7] = strdup(str); //riadok skopirujeme do spravneho pola
            break;
        case 3:
            str[strlen(str)-1] = 0; //z riadku vymazeme posledny znak (\n)
            (*p_vysetrenie)[i/7] = strdup(str); //riadok skopirujeme do spravneho pola
            break;
        case 4:
            (*p_vysledok)[i/7] = atof(strdup(str)); //riadok prekonvertujeme na float a skopirujeme do spravneho pola
            break;
        case 5:
            (*p_datum)[i/7] = atoi(strdup(str)); //riadok prekonvertujeme na int a skopirujeme do spravneho pola
            break;
        default:
            break;
        }
    }
    return velkost; //vrati pocet zaznamov v subore
}

/*      ----FUNKCIA S----       
* podla zadaneho rodneho cisla vypise vysetrenie a vysledok
* input RODNE CISLO
*/
int s(int velkost, char **p_vysetrenie, char **p_rcislo, double *p_vysledok){ //ready
    //argumenty - velkost, polia vysetrenie, rcislo a vysledok
    //overenie ci boli polia vytvorene (defoult velkosti je -1, ak boli vytvorene, velkost bude minimalne 0)
    if (velkost == -1)
    {
        printf("Polia nie su vytvorene.\n"); //vypise chybu a ukonci funkciu
        return -1;
    }
    
    //nacita rodne cislo do premennej rcislo typu long long
    long long rcislo;
    scanf("%lld", &rcislo);
    
    //najde v zaznamoch dane rodne cislo a vypise ho s rovnakym indexom v poli vysetreni a vysledkov
    for(int i = 0; i < velkost; i++){
        if(rcislo == atoll(p_rcislo[i])){ //porovnava zadane rodne cislo s rodnym cislom v zaznamoch
            printf("Vysledky vysetreni, ktore boli vykonane pacientovi s rodnym cislom %lld su nasledovne:\n%s: %.2lf\n", atoll(p_rcislo[i]), p_vysetrenie[i], p_vysledok[i]);
            return 0; //ukonci funkciu (spravne)
        }
    }
}

/*      ----FUNKCIA H----       
* vypise histogram vyskytov diagnozy podla pohlavia a veku
* input DIAGNOZA
*/
int h(int velkost, char **p_rcislo, char **p_diagnoza){ //ready
    //argumenty - velkost, polia rcislo a diagnoza
    //overenie ci boli polia vytvorene (defoult velkosti je -1, ak boli vytvorene, velkost bude minimalne 0)
    if (velkost == -1)
    {
        printf("Polia nie su vytvorene.\n");
        return -1;
    }
 
    //nacita diagnozu do premennej diagn
    char diagn[MAX];
    scanf("%s", diagn);
    int vek = 0, j = 0;

    //zisti pocet vyskytov diagnozy v zaznamoch
    for(int i = 0; i < velkost; i++){
        if (strcmp(diagn, p_diagnoza[i]) == 0){ //porovnava diagn s prvkami s poli diagnoza (ak su rovnake, vrati 0)
            j++;
        }
    }
    //vytvori premennu pohlavie (porovnanie s 50 v rodnom cisle) a polia arr_pohlavie a arr_vek velkosti j
    int pohlavie = 0;
    char **arr_pohlavie = (char**) calloc(j, sizeof(char*));
    int *arr_vek = (int*) calloc(j, sizeof(int));
    
    //kopiruje do poli arr_vek a arr_pohlavie udaje, ktore sa vyskytuju pri danej diagnoze
    j = 0;
    for(int i = 0; i < velkost; i++){ 
        if (strcmp(diagn, p_diagnoza[i]) == 0){ //ak je diagn rovnaka s konkretnym prvkom pola diagnozy
            if(atoll(p_rcislo[i])/100000000 > 20){ //ak je narodeny po roku 2000 (rcislo / 100000000 vrati prve 2 cisla rodneho cisla == roku narodenia)
                vek = 2020 - (1900 + atoll(p_rcislo[i])/100000000); //vyrata sa vek (podla roku narodenia a aktualneho roku)
                arr_vek[j] = vek; //vek sa zapise do pola arr_vek
            }else{ //ak je narodeny pred roku 2000
                vek = 2020 - (2000 + atoll(p_rcislo[i])/100000000); //vyrata sa vek (podla roku narodenia a aktualneho roku)
                arr_vek[j] = vek; //vek sa zapise do pola arr_vek
            }
            pohlavie = (atoll(p_rcislo[i])/1000000)%100; //vyrata pohlavie s rodneho cisla (3 a 4 cislica - mesiac, u zien je vacsia ako 50)
            if(pohlavie < 50){ //ak je mensia ako 50
                arr_pohlavie[j] = "Muz"; //do pola zapise muz
            }else{ //inak
                arr_pohlavie[j] = "Zena"; //do pola zapise zena
            }
            j++; //priratava index pola
        }
    }

    //vytvorenie pola na pamatanie veku ktory uz bol (index bude identicky poliam arr_vek a arr_pohlavie)
    int *arr_vek_ktory_uz_bol = (int*) calloc(j, sizeof(int));
    int vek_ktory_uz_bol = 0;
    vek = 0;
    int cislo = 0;
    
    //vypisovanie muzov
    printf("Muzi\n");
    for (int i = 0; i < j; i++){
        if(strcmp(arr_pohlavie[i], "Muz") == 0){ //ak je pohlavie muz
            for(int l = 0; l < j; l++){ //cyklus, ktory prejde znova vsetky prvky
                if (arr_vek[i] == arr_vek_ktory_uz_bol[l]){ //ak konkretny vek sa uz nachadza v poli arr_vek_ktory_uz_bol
                    vek_ktory_uz_bol = 1; //vek_ktory_uy_bol = 1 (True)
                }
            }
            if(vek_ktory_uz_bol == 0){ //ak vek este nebol
                if(arr_vek[i] == vek){ //ak vek == momentalnemu prvku pola arr_vek
                cislo++; //pocet rovnaych vekov
            }else{
                vek = arr_vek[i]; //vek nadobudne hodnotu momentalneho prvku z pola arr_vek
            }
            for (int k = 0; k < j; k++){ //cyklus, ktory prejde znova vsetky prvky
                if(arr_vek[k] == vek && strcmp(arr_pohlavie[k], "Muz") == 0){ //ak je pohlavie muz a vek je rovny veku ktory prave hladame
                    cislo++; //pocet rovnakych vekov
                }else{
                    vek = arr_vek[i]; //vek nadobudne hodnotu momentalneho prvku z pola arr_vek
                }
            }
            printf("%d: %d\n", arr_vek[i], cislo); //vypise dany vek a pocet rovnaych vekov v poli
            }
            arr_vek_ktory_uz_bol[i] = arr_vek[i]; //momentalny vek sa prida do pola velkov ktore uz boli
        }
        //vynuluju sa premenne cislo a vek ktory uz bol
        cislo = 0;
        vek_ktory_uz_bol = 0;
    }
    //vynuluje sa pole vekov ktore uz boli
    for (int i = 0; i < j; i++){
        arr_vek_ktory_uz_bol[i] = 0;
    }
    
    //rovnaky pricip ako bol pouzity pre muzov, sa pouzie pre zeny
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
    //uvolnia sa vytvorene polia
    free(arr_vek);
    free(arr_vek_ktory_uz_bol);
    free(arr_pohlavie);
}

/*      ----FUNKCIA P----       
* vypise a zapise do suboru novu hodnotu vysledku a datum u daneho pacienta
* input RODNE CISLO, VYSETRENIE, DATUM, VYSLEDOK
*/
int p(int velkost, char **p_meno, char **p_diagnoza, char **p_vysetrenie, char **p_rcislo, double *p_vysledok, int *p_datum){//ready
    //argumenty - velkost a vsetky polia

    //vytvorenie premennych a nacitanie vstupov
    int datum;
    long long rcislo;
    char vysetrenie[MAX];
    double vysledok;
    scanf("%lld", &rcislo);
    scanf("%s", &vysetrenie);
    scanf("%d", &datum);
    scanf("%lf", &vysledok);

    //hladanie zadaneho rodneho cisla a diagnozy v poliach
    for(int i = 0; i < velkost; i++){
        if(rcislo == atoll(p_rcislo[i]) && strcmp(vysetrenie, p_vysetrenie[i]) == 0){ //musia sa rovnat aj rcislo0 aj vysetrenie
            
            //vytvori premennu a otvori subor na pisanie
            FILE *fw;
            if((fw = fopen("pacienti.txt", "w")) == NULL){ //ak sa subor nepodarilo otvorit, vypise chybovu hlasku a ukonci funkciu
                printf("Neotvoreny subor\n");
                return -1;
            }

            //vypise nasledujuci retazec s rcislom, vysetreni a vyslekom zo zaznamov a novym zadanym vysledkom
            printf("Pacientovi s rodnym cislom %lld bol zmeneny vysledok vysetrenia %s z povodnej hodnoty %.2lf na novu hodnotu %.2lf\n", atoll(p_rcislo[i]), p_vysetrenie[i], p_vysledok[i], vysledok);
            
            //updatne zaznamy vysledkov a datumov na danom indexe
            p_vysledok[i] = vysledok;
            p_datum[i] = datum;

            //cely subor nanovo prepise, s uz novymi udajmy
            for(int j = 0; j < velkost; j++){
                fprintf(fw, "%s\n", p_meno[j]);
                fprintf(fw, "%s\n", p_rcislo[j]);
                fprintf(fw, "%s\n", p_diagnoza[j]);
                fprintf(fw, "%s\n", p_vysetrenie[j]);
                fprintf(fw, "%.2lf\n", p_vysledok[j]);
                if (j == velkost - 1){ //ak je to posledny zaznam, na konci nedava "\n"
                    fprintf(fw, "%d", p_datum[j]);
                } else{
                    fprintf(fw, "%d\n", p_datum[j]);
                }
                if (j != velkost - 1){ //ak to nieje posledny zaznam, nakonci da "\n"
                    fprintf(fw, "\n");
                }
            }
            fclose(fw); //zatvori subor
            
            return 0;
        }
    }
    
}

/*      ----FUNKCIA Z----       
* nacita dva datumy a vysetrenie a vypise troch pacientov s najvacsimi hodnotami s rovnakym vysetrenim
* input DATUM 1, DATUM 2, VYSETRENIE
*/
int z(int velkost, char **p_meno, char **p_vysetrenie, int *p_datum, double *p_vysledok){ //ready
    //argumenty - velkost, polia mien, vysetreni, dattumov a vysledkov

    //overenie ci boli polia vytvorene (defoult velkosti je -1, ak boli vytvorene, velkost bude minimalne 0)
    if (velkost == -1)
    {
        printf("Polia nie su vytvorene.\n");
        return -1;
    }

    //vytvorenie premennych a nacitanie datumov a vysetrenia
    int date1, date2;
    double max1 = 0, max2 = 0, max3 = 0;
    char vysetrenie[MAX];
    scanf("%d", &date1);
    scanf("%d", &date2);
    scanf("%s", &vysetrenie);

    //ak je datum 1 vacsi ako datum 2, vypise chybu a funkcia sa ukonci
    if(date1 > date2){
        printf("Koncovy datum sa nachadza pred pociatocnym datumom.\n");
        return -1;
    }

    //dynamicke alokovanie pola velkosi "velkost" na zapisovanie vysledkov
    double *vysledok = (double*) calloc(velkost, sizeof(double)); //volanie calloc vyplni vsetky hodnoty na defoultnu hodnotu 0
    
    //postupne prejde vsetky zaznamy a porovnava ci je datum v nami zadanom intervale a zaroven ci vysetrenie sedi s nami zadanym vysetrenim
    for (int i = 0; i < velkost; i++)
    {
        if(p_datum[i] >= date1 && p_datum[i] <= date2 && strcmp(vysetrenie, p_vysetrenie[i]) == 0){
            vysledok[i] = p_vysledok[i]; //ak toto vsetko plati, vysledok s danym indexom sa zapise do pola vysledkov
        }
    }
    
    //zistovanie 3 najvacsich vysledkov v poli (zvysok pola su 0)
    for (int i = 0; i < velkost; i++)
    {
        if (vysledok[i] >= max1){ //najvacsi vysledok zapise do max1
            max1 = vysledok[i];
        }else if (vysledok[i] >= max2){
            max2 = vysledok[i]; //2. najvacsi vysledok zapise do max2
        }else if (vysledok[i] >= max3){
            max3 = vysledok[i]; //3. najvacsi vysledok zapise do max2
        }
    }

    //este raz prejde cele pole vysledkov a ak sa vysledok zhoduje s jednym s maxim, vypise ho
    //vysledky nemusia byt v poradi od najvacsieho po najmensie
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

    //uvolni alokovane pole
    free(vysledok);
}

/*      ----FUNKCIA K----       
* uvoli vsetky alokovanie polia v maine
*/
void k(char ***p_meno, char ***p_diagnoza, char ***p_vysetrenie, char ***p_rcislo, double **p_vysledok, int **p_datum){ //ready
    //argumenty - pointre na vsetky polia alokovanie v maine

    //uvolnenie vsetkych poli
    free(*p_meno);
    free(*p_diagnoza);
    free(*p_vysetrenie);
    free(*p_rcislo);
    free(*p_vysledok);
    free(*p_datum);
}

/*      ----MAIN----       
* vytvorenie premennych, ktore sa budu neskor alokovat vo funkcii n
* vytvorenie premennej typu FILE, ktora sa bude otvarat vo funkcii v
* nekonecny cyklus ktory sleduje vstupy z klavesnice a spusta jednotlyve funkcie
*/
int main(void){ //main

    //vytvorenie premennych na ktorych sa budu alokovat polia
    char **meno, **diagnoza, **vysetrenie, **rcislo;
    int *datum;
    double *vysledok;

    //vytvorenie premennej typu FILE, na ktorej sa bude otvarat subor
    FILE *subor = NULL;
    char funkcia; //premenna na sledovanie vstupu z klavesnice
    int velkost = -1; //defoultna velkost suboru

    //volanie funkcii
    while(1){ //nekonecny cyklus
        
        scanf("%c", &funkcia); //nacitanie znaku do premennej funkcia
        //funkcia v
        if(funkcia == 'v'){
            if(v(&subor) == -1){ //ak sa vrati -1 (nejaka chyba vo funkcii) program sa ukonci
                return 0;
            }
        }
        //funkcia n
        if(funkcia == 'n'){
            velkost = n(subor, &meno, &diagnoza, &vysetrenie, &rcislo, &vysledok, &datum); //volanie funkcie s argumentom - adresy na premenne na polia
        }
        //funkcia o
        if(funkcia == 'o'){
            o(subor); //volanie funkcie s premennou na otvorenie suboru
        }
        //funkcia s
        if(funkcia == 's'){
            s(velkost, vysetrenie, rcislo, vysledok); //volanie funkcie s argumentmi - vysledok a dane polia
        }
        //funkcia p
        if(funkcia == 'p'){
            if(p(velkost, meno, diagnoza, vysetrenie, rcislo, vysledok, datum) == -1){ //volanie funkcie s argumentmi - vysledok a dane polia, ak sa vrati -1 (chyba vo funkcii) program sa ukonci
                return 0;
            }
        }
        //funkcia h
        if(funkcia == 'h'){
            h(velkost, rcislo, diagnoza); //volanie funkcie s argumentmi - vysledok a dane polia
        }
        //funkcia z
        if(funkcia == 'z'){
            z(velkost, meno, vysetrenie, datum, vysledok); //volanie funkcie s argumentmi - vysledok a dane polia
        }
        //funkcia k
        if(funkcia == 'k'){
            k(&meno, &diagnoza, &vysetrenie, &rcislo, &vysledok, &datum); //volanie funkcie s argumentmi - adresy poli
            break; //odidenie z cyklu
        }
    }

    fclose(subor); //zatvorenie suboru
    
    return 0; //ukoncenie programu
}
