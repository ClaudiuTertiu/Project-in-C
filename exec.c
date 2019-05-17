#include "header.h"
#include "list.h"
#include "functions.h"

int main ( int argc , char **argv ) // preiau argumente
{
    //Declarare variabile 
    List l = NULL, p = NULL, z , head ;
    double average = 0, deviation = 0;
    int i , n , timestamp , interval , var = 0;
    double x ;

    //Citire date din fisier
    scanf("%d", &n); 
    var = n;
    for (i = 0; i <= n - 1; i++) //completez lista
    {
        scanf("%d %lf", &timestamp, &x);
        l = addLast(l, x, timestamp); // creez un nod
    }
    p = l; // il fac pe p sa pointeze spre inceputul listei
    for ( i = 1 ; i < argc ; i++ ) // citire argumente pe cazuri
    {
        if ( strcmp("--e1" , argv[i] ) == 0)
        {
            //task 1.1
            while ( p->next->next->next->next != NULL ) // cat timp al 5-lea element exista
            {
                average = medie(p); //aplic formulele pentru subgrupurile de 5 elemente
                deviation = deviatia( p, average );
                z = p->next->next; //analizez al 3-lea element
                if (z->value > (average - deviation) && z->value < (average + deviation))
                    p = p->next;
                else // marchez elementele ce urmeaza sa fie sterse
                {
                    z->mark = 1;
                    p = p->next;
                    n--;
                }
            }
            l = modify(l);
        }
        else if (strcmp("--e2", argv[i]) == 0)
        {
           l = medianaa ( l , &n );

        }
        else if (strcmp("--e3", argv[i]) == 0)
        {
            l = aritmetica(l, &n );
        }
        else if (strcmp("--u", argv[i]) == 0)
        {
            frecventa(l);
        }
        else if (strcmp("--c", argv[i]) == 0)
        {
            l = date( l, &n );
        }
        else if (strcmp("--st", argv[i]) < 0)
        {
            //bonus
            char substr[] = "--st";
            char sir[50] , sir2[50];
            double maxim = 0 , minim = 0 ;
            double intervalMin = 0 , intervalMax = 0 ;
            int counter = 0 , nextInterval = 0 ;
            List start;
            head = l;
            sscanf(argv[i] ,"%s" , sir); 
            strcpy(sir2, strdel (argv[i] , substr));
            interval = atoi(sir2); // am scos intervalul prin transformare din char in int
            l = bubbleSort(l);
            minim = l->value;
            start = l;
            while ( start->next != NULL) // gasesc minimul
                start = start->next;
            maxim = start->value;
            while ( intervalMin >= minim) // stabilesc intervalul minim
                intervalMin -= interval; // e multiplu de interval
            while ( intervalMax <= maxim) // stabilesc intervalul maxim
                intervalMax += interval; // e multiplu de interval
            int newMin = (int) intervalMin; // cast la int
            int newMax = (int) intervalMax;
            while ( newMin != newMax  ) // pana cand ajung de la intervalul minim la cel maxim
            {
                nextInterval = newMin + interval; // cresc din interval in interval
                p = l;
                counter = 0;
                while ( p != NULL ) //calculez cate elemente apartin intervalului
                {
                    if (  p->value >= newMin && p->value <= nextInterval ) // daca apartine intervalului
                        counter++;
                    p = p->next;
                }
                if ( counter != 0 ) // in caz ca s-au gasit elemente din interval
                    printf("[%d, %d] %d\n", newMin , nextInterval , counter);
                newMin += interval;
            }
            return 0; // ies sa ma asigur ca nu afiseaza si lista
        }
    }
    printf("%d\n" , n);
    if ( l != NULL)
        printList(l);
}
