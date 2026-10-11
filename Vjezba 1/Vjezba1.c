#define _CRT_SECURE_NO_WARNINGS
#define LEN 30
#define max_br_bod 100

#include <stdio.h>
#include <stdlib.h>


typedef struct {
    char ime[LEN];
    char prezime[LEN];
    int bodovi;
} Student;

int main(){

    FILE* fp = fopen("Studenti.txt", "r");
    if (fp == NULL){
        printf("Fopen Error");
        return -1;
    }

    int brStud = 0;
    char buffer[LEN];
    while(fgets(buffer,LEN,fp)!=NULL)
        brStud++;

    if(brStud == 0){
        printf("Nema Studenata");
        fclose(fp);
        return 0;
    }

    //printf("%d", brStud);

    Student* Studenti = (Student*)malloc(brStud * sizeof(Student));
    if(Studenti == NULL){
        printf("Malloc Error");
        free(Studenti);
        fclose(fp);
        return -2;
    }
    
    //Vrati na pocetak umijesto pnovnog fclose i fopen
    rewind(fp);

    int br = 0;
    while (fscanf(fp, " %s %s %d", Studenti[br].ime, Studenti[br].prezime, &Studenti[br].bodovi) != EOF)
        br++;
    
    for(int i = 0; i < brStud; i++)
        printf("[%d] %s %s %d %d%%\n", i, Studenti[i].ime, Studenti[i].prezime, Studenti[i].bodovi, (Studenti[i].bodovi*100)/max_br_bod);
    
    free(Studenti);
    fclose(fp);

    return 0;
}