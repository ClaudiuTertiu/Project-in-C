List date ( List l , int * n)
{
    List head , keep , keepNxt , pLeft , pRight , new = NULL ;
    double tmst = 0 , omega = 0 , sumNum = 0 , j , i , sumaL , sumaR ;
    double f;
    int count = 0;
    head = l->next->next;
    while ( head->next->next != NULL ) // am nevoie de 6 elemente in lista
    {
        sumNum = 0;
        int freq ;
        freq = head->next->timestamp - head->timestamp; // diferenta dintre 2 timestamp-uri consecutive
        for ( j = 0 ; j <= 2 ; j++)
        {
            sumNum = sumNum + pow(j/2,2)*0.9 + 0.1; //calculez numitorul de la omega
        }
        if ( freq > 1000 ) // am gasit gap-ul
        {
            keep = head; //tin minte pentru addList
            keepNxt = head->next; //la fel
            tmst = head->timestamp + 200; //il setez cu +200 fata de cel de unde incep sa generez
            while ( tmst < head->next->timestamp) //atata timp cat timestamp-ul viitor nu trece ultima valoare gen de la 200 si eu am interval pana la 390
            {
                double C = (tmst - head->timestamp) / (head->next->timestamp - head->timestamp); //calculez C-ul pentru intervalul curent
                sumaL = 0;
                sumaR = 0;
                omega = 0;
                pLeft = head->prev->prev; // e primul element din left
                pRight = head->next->next->next; // primul element din right
                for ( i = 0 ; i <= 2; i++)
                {
                    omega = ( pow(i/2,2)*0.9 + 0.1 ) / sumNum; //calculez omega in functie de i
                    sumaL = sumaL + omega * pLeft->value; //calculez suma la stanga cu pozitia avansand
                    sumaR = sumaR + omega * pRight->value; //la fel
                    pLeft = pLeft->next; //avansez pozitia odata cu i-ul
                    pRight = pRight->prev; //la fel
                }
                f = ( 1.00 - C ) * sumaL + C * sumaR; //valoarea finala
                count++; // creste elementele initiale cu cele generate
                new = addLast ( new , f , tmst); //adaug intr-o alta lista
                tmst += 200;
            }
            insertList ( keep , new , keepNxt ); //leg lista generata intre nodurile pastrate
            new = NULL;   
        }
        head = head->next;
    }
    *n += count;
    return l;
}  
//-----------------------------------------------------------------------------------------------------------------------
char *strdel(char *str, const char *sub) { // consider un string si un substring
    size_t dim = strlen(sub); // stabilesc dimensiunea string-ului pe care vreau sa il sterg
    if (dim > 0) { // atat timp cat exista
        char *p = str;
        while ((p = strstr(p, sub)) != NULL) { // elimin substringul din string
            memmove(p, p + dim, strlen(p + dim) + 1); //pointez vectorul de caractere spre stringul ramas
        }
    }
    return str;
}
//-----------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------
List aritmetica(List p, int *n)
{
    List aux = p;
    List l = p;
    List head = NULL;
    int i = 0;
    double average;
    
    while (l->next->next->next->next != NULL)
    {
        i++;
        l = l->next;
    }
    
    *n = i;

    while ( aux->next->next->next->next != NULL ) // cat timp al 5-lea element exista
    {
        average = medie(aux);
        head = addLast( head , average , aux->next->next->timestamp);
        aux = aux->next;
    }
    
    return head;
}
//-----------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------
List medianaa( List l , int* q )
{
    List p = l , new = NULL , head ;
    List mediane = NULL;
    int i , count = 0;
    while ( p->next->next->next->next != NULL )
    {
        count++;
        head = p;
        for ( i = 0 ; i<= 4 ; i++ ) // fac o lista de 5 elemente
        {
            mediane = addLast ( mediane , head->value , head->timestamp ); 
            head = head->next;
        }
        // le ordonez crescator
        mediane = bubbleSort(mediane);
        new = addLast(new , mediane->next->next->value , mediane->next->next->timestamp);
        mediane = NULL;
        p = p->next;
    }
    *q = count;
    return new;
}
//-----------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------
List bubbleSort(List l)
{
    List nod;
    int swapped;
    double tmp;
    if (l == NULL)
        return NULL;
    do // bucla care este executata pana schimb variabila swapped
    {
        swapped = 0;
        nod = l;
        while (nod->next != NULL) // pana la final
        {
            if (nod->value > nod->next->value) 
            {   //interschimbare
                tmp = nod->value;
                nod->value = nod->next->value;
                nod->next->value = tmp;
                swapped = 1;
            }
            nod = nod->next;
        }
    } while (swapped);
    return l;
}
//-----------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------
void frecventa( List l )
{
    int freq;
    while (l->next != NULL)
    {
        freq = l->next->timestamp - l->timestamp;
        if (freq >= 100 && freq <= 1000)
        {
            l->next->timestamp = (l->next->timestamp + l->timestamp) / 2;
            l->next->value = (l->next->value + l->value) / 2;
        }
        l = l->next;
    }
}
//--------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------
List modify(List head)
{
    List new = NULL;
    while (head != NULL)
    {
        if (head->mark == 0)
        {
            new = addLast(new, head->value, head->timestamp); // adaug intr-o alta lista elementele nemarcate
        }
        head = head->next; // trec la urmatorul nod si il verific
    }
    return new; // returnez lista cu elementele pe care vreau sa le afisez
}
//--------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------
double medie(List p)
{
    List a = p;
    int i;
    double average = 0;
    for (i = 0; i <= 4; i++)
    {
        average += a->value;
        a = a->next;
    }
    average = average / 5;
    return average;
}
//--------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------
double deviatia(List p, double average)
{
    int i;
    double deviation = 0;
    double pows, sum = 0, valoare;
    List a = p;
    for (i = 0; i <= 4; i++)
    {
        valoare = a->value;
        pows = pow(valoare - average, 2); // scot patratul diferentei
        sum += pows; // al adaug la suma
        a = a->next;
    }
    sum = sum / 5;
    deviation = sqrt(sum); // formula sub forma finala cu radical
    return deviation;
}
//--------------------------------------------------------------------------------------------------------------------------
