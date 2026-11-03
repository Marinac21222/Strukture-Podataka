/*
4. Napisati program za zbrajanje i množenje polinoma. Koeficijenti i eksponenti se
čitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nužno sortirani.
*/
/*
unutar .txt koef,exp,koef,exp,...
- ucitat iz dat.
typedef struct Poly* Position;
typedef struct Poly{
    int coeff;
    int pow;
    Position next;
} polynom;
polynom head=...
polynom headF
polynom headS
Position newPoly -> alokacija + unos pod
if(q.next == NULL)
    insertbegin(q,newPoly)
if(q.next!=NULL && newPoly.pow > q.next.pow)
    insertBegin(q,newPoly)
if(q.next!=NULL && newPoly.pow < q.next.pow)
    q=q.next
koef 0 ne smije bit u listi
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Poly;
typedef struct Poly* Position;
typedef struct Poly {
    int coeff;
    int pow;
    Position next;
} polynom;

Position mallocPoly(int coef, int pow){
    if(coef == 0)
        return NULL;
    
    Position newPoly = (Position)malloc(sizeof(polynom));
    if(newPoly == NULL){
        printf("Malloc Error\n");
        return NULL;
    }
    newPoly->coeff = coef;
    newPoly->pow = pow;
    newPoly->next = NULL;
    return newPoly;
}

int insertSorted(Position head, int coef, int pow) {
    Position newPoly = mallocPoly(coef, pow);
    //ako je NULL ili koef 0
    if (newPoly == NULL) {
        return 0;
    }

    Position q = head;
    while (q->next != NULL && q->next->pow > newPoly->pow) {
        q = q->next;
    }

    if (q->next != NULL && q->next->pow == newPoly->pow) {
        q->next->coeff += newPoly->coeff; // Zbrojimo koeficijente
        
        if (q->next->coeff == 0) {
            Position temp = q->next;
            q->next = temp->next;
            free(temp);
        }
        free(newPoly);
    } 
    else {
        newPoly->next = q->next;
        q->next = newPoly;
    }

    return 0;
}

int readPolyFromFile(Position head, char* filename, int red) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Greška pri otvaranju datoteke!\n");
        return -1;
    }

    int trenutniRed = 1;
    int coef, pow;
    char ch;

    while (trenutniRed < red) {
        while ((ch = fgetc(fp)) != '\n' && ch != EOF);
        trenutniRed++;
    }

    while (fscanf(fp, "%d %d", &coef, &pow) == 2) {
        insertSorted(head, coef, pow);

        ch = fgetc(fp);
        if (ch == '\n' || ch == EOF) {
            break;
        }
        ungetc(ch, fp); //potrebno da nastavimo dalje citat ako nije novi red, vraca taj char nazad
    }

    fclose(fp);
    return 0;
}

int printPoly(Position head) {
    if (head == NULL || head->next == NULL) {
        printf("Polinom je prazan!\n");
        return 0;
    }

    Position p = head->next;
    int prviClan = 1;

    while (p != NULL) {
        if (p->coeff > 0) {
            if (!prviClan) {
                printf(" + ");
            }
            // Ako je koeficijent 1, a eksponent veci od 0, ne moramo pisati 1x, nego samo x, ako je eksponent 0, onda moramo ispisati 1
            if (p->coeff != 1 || p->pow == 0) {
                printf("%d", p->coeff);
            }
        } else if (p->coeff < 0) {
            printf(" - ");
            if (p->coeff != -1 || p->pow == 0) {
                printf("%d", -p->coeff); 
            } else if (p->coeff == -1 && p->pow == 0) {
                printf("1");
            }
        }

        if (p->pow > 0) {
            if (p->pow == 1) {
                printf("x");
            } else {
                printf("x^%d", p->pow);
            }
        }

        prviClan = 0;
        p = p->next;
    }
    printf("\n");
    return 0;
}

Position zbrojiPolinome(Position head1, Position head2) {
    Position headZbroj = (Position)malloc(sizeof(polynom));
    if (headZbroj == NULL) {
        printf("Malloc Error\n");
        return NULL;
    }
    headZbroj->coeff = 0;
    headZbroj->pow = 0;
    headZbroj->next = NULL;

    Position p1 = head1->next;
    Position p2 = head2->next;

    while (p1 != NULL && p2 != NULL) {
        if (p1->pow > p2->pow) {
            insertSorted(headZbroj, p1->coeff, p1->pow);
            p1 = p1->next;
        } 
        else if (p1->pow < p2->pow) {
            insertSorted(headZbroj, p2->coeff, p2->pow);
            p2 = p2->next;
        } 
        else {
            int zbrojKoef = p1->coeff + p2->coeff;
            insertSorted(headZbroj, zbrojKoef, p1->pow);
            p1 = p1->next;
            p2 = p2->next;
        }
    }

    while (p1 != NULL) {
        insertSorted(headZbroj, p1->coeff, p1->pow);
        p1 = p1->next;
    }

    while (p2 != NULL) {
        insertSorted(headZbroj, p2->coeff, p2->pow);
        p2 = p2->next;
    }

    return headZbroj;
}

int freePoly(Position head) {
    Position temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}

Position mnoziPolinome(Position head1, Position head2) {

    Position headMnozenje = (Position)malloc(sizeof(polynom));
    if (headMnozenje == NULL) {
        printf("Greška pri alokaciji memorije za umnožak!\n");
        return NULL;
    }
    headMnozenje->coeff = 0;
    headMnozenje->pow = 0;
    headMnozenje->next = NULL;

    Position p1 = head1->next;
    Position p2 = head2->next;

    while (p1 != NULL) {
        p2 = head2->next; 
        while (p2 != NULL) {
            int noviKoef = p1->coeff * p2->coeff;
            int noviExp = p1->pow + p2->pow;

            insertSorted(headMnozenje, noviKoef, noviExp);

            p2 = p2->next;
        }
        p1 = p1->next;
    }

    return headMnozenje;
}

int main() {
    Position headF = (Position)malloc(sizeof(polynom));
    headF->coeff = 0; headF->pow = 0; headF->next = NULL;
    readPolyFromFile(headF, "poly.txt", 1);

    Position headS = (Position)malloc(sizeof(polynom));
    headS->coeff = 0; headS->pow = 0; headS->next = NULL;
    readPolyFromFile(headS, "poly.txt", 2);

    printf("Prvi polinom:  ");
    printPoly(headF);

    printf("Drugi polinom: ");
    printPoly(headS);

    Position headZbroj = zbrojiPolinome(headF, headS);
    printf("Zbroj:         ");
    printPoly(headZbroj);

    Position headUmnozak = mnoziPolinome(headF, headS);
    printf("Umnozak:       ");
    printPoly(headUmnozak);

    freePoly(headF);
    freePoly(headS);
    freePoly(headZbroj);
    freePoly(headUmnozak);

    return 0;
}