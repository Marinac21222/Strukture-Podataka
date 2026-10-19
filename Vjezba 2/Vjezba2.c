/*
2. Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
A. dinamički dodaje novi element na početak liste,
B. ispisuje listu,
C. dinamički dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. briše određeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.
*/

/*
typedef struct Person* Position
typedef struct Person (data)
Head element - pocetni
Struct Person Head = {.name = "",.lastName = "",.year=0,.next=NULL}
int insertBegin(char* ime, char* prezime, int god,Position Head){
    Position newPerson = (Position)malloc(sizeof(Person))
    #Provjeri alokaciju
    newPerson->year = god;
    strcpy(newPerson->name, ime);
    newPerson->next = NULL;
}
int insertAfter(Position p, Position newP){
    newP -> next = p -> next;
    p -> next = newP;
}
int printList(Position p){
    while(p!=NULL)
        printf(...)
        p=p->next
}
int insertEnd(){
    while(head->next != NULL)
        head = head->next
    insertAfter(head, newPerson)
}
Position findLastName(Position p, char* prezime){
    for(p=p->next;p!=NULL;p=p->next)
        if(strcmp(p->lastN,prezime)==0)
            return p;
}
int deletePerson(Position p,char* prez){
    Position prev = 0
    Position curr = p-> next
    curr = findLastName(p, prez)
    while(prev->next!=curr)
        prev=prev->next
    prev->next = curr -> next
    free(curr)
}
*/
#define _CRT_SECURE_NO_WARNINGS
#define LEN 30
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person_* Position;

typedef struct Person_
{
    char name[LEN];
    char lastName[LEN];
    int year;
    Position next; 
} Person;

int insertBegin(Position head, char* name, char* lastName, int year){
    Position newPerson = (Position)malloc(sizeof(Person));

    if(newPerson == NULL){
        printf("Malloc Error\n");
        return -1;
    }

    strcpy(newPerson->name,name);
    strcpy(newPerson->lastName,lastName);
    newPerson->year=year;

    newPerson->next=head->next;
    head->next=newPerson;

    return 0;
}

int insertAfter(Position p, Position newP){
    newP->next = p->next;
    p->next = newP;
    return 0;
}

int printList(Position p){
    //jer je u head NULL
    p = p->next;

    while (p != NULL)
    {
        printf("%s %s %d\n",p->name,p->lastName,p->year);
        p = p->next;
    }
    

    return 0;
}

int insertEnd(Position head, char* name, char* lastName, int year){
    Position newP = (Position)malloc(sizeof(Person));
    if(newP == NULL)
    {
        printf("Malloc Error\n");
        return -1;
    }

    strcpy(newP->name, name);
    strcpy(newP->lastName, lastName);
    newP->year = year;
    newP->next = NULL; //Posto je sad newP na kraju liste njegov next mora bit NULL

    Position current = head;
    while (current->next != NULL)
        current = current->next;
    
    insertAfter(current, newP);

    return 0;
}

Position findLastName(Position p, char* lastName){
    for(p = p->next; p != NULL; p = p->next)
        if(strcmp(p->lastName,lastName) == 0)
            return p;

    return NULL;
}

int deletePerson(Position p, char* lastName){
    Position current = findLastName(p, lastName);

    if(current == NULL){
        printf("Osoba s tim prezimenom nije pronadena.\n");
        return -1;
    }

    Position prev = p;
    while (prev->next != current)
        prev = prev->next;

    prev->next = current->next;

    free(current);

    printf("Osoba s prezimenon %s je izbrisana.\n", lastName);

    return 0;
}

int main()
{
    Person head = {.name = "", .lastName = "", .year = 0, .next = NULL};

    printf("Lista:\n");
    insertBegin(&head, "Ivo", "Ivic", 1995);
    insertBegin(&head, "Ana", "Anic", 1999);
    insertEnd(&head, "Mate", "Matic", 2000);
    
    printList(&head);

    char lastNameToFind[] = "Anic";
    Position pFound = findLastName(&head, lastNameToFind);

    if(pFound == NULL)
        printf("Prezime %s nije pronadeno.\n",lastNameToFind);
    else
        printf("Pronadeno prezime %s\n", pFound->lastName);

    deletePerson(&head, "Ivic");
    printList(&head);
    
    return 0;
}