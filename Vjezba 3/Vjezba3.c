/*
3. Prethodnom zadatku dodati funkcije:
A. dinamički dodaje novi element iza određenog elementa,
B. dinamički dodaje novi element ispred određenog elementa,
C. sortira listu po prezimenima osoba,
D. upisuje listu u datoteku,
E. čita listu iz datoteke
*/
/*
int insertBefore(Position head, char* lastN){
    Position newPerson = NULL;
    findLastName(head.next, lastN);
    insertAfter(...)
}
int insertNewAfter(Position head, char* lastN){
    Position newPerson = NULL;
    findLastName(head, lastN);
    insertAfter(...)
}
int sortFun(Position head){
    Position p = head.next
    Position q = head
    Position temp = NULL;
    while(p.next != NULL)
        if(strcmp(p.lastN,p.next.lastN)>0){
            temp = p.next
            q.next = temp
            p.next = temp.next
            temp.next = p

            q = head
            p = q.next
        }
        else{
            q = p
            p = p.next
        } 
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

//DODAVANJE NA 2 ZAD
int insertNewAfter(Position head, char* targetLastName, char* name, char* lastName, int year){
    
    Position found = findLastName(head, targetLastName);
    if(found == NULL){
        printf("Osoba s prezimenom %s nije pronadena.\n", targetLastName);
        return -1;
    }

    Position newPerson = (Position)malloc(sizeof(Person));
    if(newPerson == NULL){
        printf("Malloc Error\n");
        return -1;
    }

    strcpy(newPerson->name, name);
    strcpy(newPerson->lastName, lastName);
    newPerson->year = year;

    insertAfter(found, newPerson);
    return 0;
}

int insertBefore(Position head, char* targetLastName, char* name, char* lastName, int year){
    Position current = head;
    
    while(current->next != NULL && strcmp(current->next->lastName, targetLastName) != 0){
        current = current->next;
    }

    if(current->next == NULL){
        printf("Osoba s prezimenom %s nije pronadena.\n", targetLastName);
        return -1;
    }

    Position newPerson = (Position)malloc(sizeof(Person));
    if(newPerson == NULL){
        printf("Malloc Error\n");
        return -1;
    }

    strcpy(newPerson->name, name);
    strcpy(newPerson->lastName, lastName);
    newPerson->year = year;

    insertAfter(current, newPerson);
    
    return 0;
}

int sortFun(Position head){
    if (head->next == NULL || head->next->next == NULL)
        return 0;

    Position p = head->next;
    Position q = head;
    Position temp = NULL;

    while(p->next != NULL){
        if(strcmp(p->lastName, p->next->lastName) > 0){
            temp = p->next;
            q->next = temp;
            p->next = temp->next;
            temp->next = p;

            q = head;
            p = q->next;
        }
        else{
            q = p;
            p = p->next;
        } 
    }
    return 0;
}

int writeToFile(Position head, char* filename){
    FILE* fp = fopen(filename, "w");
    if(fp == NULL){
        printf("Greska pri otvaranju datoteke\n");
        return -1;
    }

    Position p = head->next;
    
    while(p != NULL){
        fprintf(fp, "%s %s %d\n", p->name, p->lastName, p->year);
        p = p->next;
    }
    fclose(fp);
    return 0;
}

int readFromFile(Position head, char* filename){
    FILE* fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Greska pri otvaranju datoteke za citanje!\n");
        return -1;
    }

    char name[LEN];
    char lastName[LEN];
    int year;

    while(fscanf(fp, " %s %s %d", name, lastName, &year) == 3){
        insertEnd(head, name, lastName, year);
    }

    fclose(fp);
    return 0;
}

int freeList(Position head){
    Position current = head->next;
    Position temp = NULL;

    while (current != NULL){
        temp = current;
        current = current->next;
        free(temp);
    }

    head->next = NULL;
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

    insertNewAfter(&head, "Anic", "Marko", "Maric", 1992);
    printList(&head);

    insertBefore(&head, "Anic", "Petar", "Petric", 1988);
    printList(&head);
    printf("SORTIRANO\n");
    sortFun(&head);
    printList(&head);
    
    writeToFile(&head,"Osobe.txt");

    freeList(&head);
    printf("Ucitano iz datoteke:\n");
    readFromFile(&head,"Osobe.txt");
    printList(&head);
    return 0;
}