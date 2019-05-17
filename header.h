#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
typedef struct list
{
    double value;
    int timestamp;
    int freq;
    struct list *next;
    struct list *prev;
    int mark;
} * List;

void printList(List);
void frecventa(List);
void insertNode(List , double , int );
void insertList(List , List , List );
double medie(List);
double deviatia(List, double);
char *strdel(char *, const char *);
List bubbleSort(List);
List date ( List , int*);
List initList(double, int);
List deleteItem(List, double, int);
List addLast(List, double, int);
List modify(List);
List aritmetica(List , int*);
List deleteList(List );
List medianaa( List , int* );

