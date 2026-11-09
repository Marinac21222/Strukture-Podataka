#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _stack {
    int broj;
    struct _stack* next;
}Stack;
typedef Stack* Position;

int Push(Position head, int broj) {
    Position novi = (Position)malloc(sizeof(Stack));
    if (novi == NULL) {
        printf("Malloc Error\n");
        return -1;
    }

    novi->broj = broj;
    novi->next = head->next;
    head->next = novi;

    return 0;
}

int Pop(Position head) {
    if (head->next == NULL) {
        printf("Prazan Stog\n");
        exit(1);
    }

    Position temp = head->next;
    int skinuti_broj = temp->broj;

    head->next = temp->next;
    free(temp);

    return skinuti_broj;
}

int izracunaj(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) {
                printf("Dijeljenje s nulom\n");
                exit(1);
            }
            return a / b;
        default: return 0;
    }
}

int ObrisiStog(Position head) {
    Position temp = NULL;
    while (head->next != NULL) {
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }
    return 0;
}

int main() {
    Stack head = { .broj = 0, .next = NULL };
    
    FILE* datoteka = fopen("izraz.txt", "r");
    if (datoteka == NULL) {
        printf("fopen error\n");
        return 1;
    }

    char buffer[64];

    while (fscanf(datoteka, "%s", buffer) == 1) {
        if (strcmp(buffer, "+") == 0 || strcmp(buffer, "-") == 0 || 
            strcmp(buffer, "*") == 0 || strcmp(buffer, "/") == 0) {
            
            int x2 = Pop(&head);
            int x1 = Pop(&head);
            
            int rezultat = izracunaj(x1, x2, buffer[0]);
            Push(&head, rezultat);
        } 
        else {
            int broj = atoi(buffer);
            Push(&head, broj);
        }
    }

    fclose(datoteka);

    int konacni_rezultat = Pop(&head);
    printf("%d\n", konacni_rezultat);

    ObrisiStog(&head);

    return 0;
}