void printList( List l )
{
    while ( l != NULL )
    {
        if ( l->mark == 0 ) // Conditie pentru elementele care trebuiesc sterse
        {
            printf("%d %.2f\n", l->timestamp, l->value);
            l = l->next;
        }
        else
        {
            l = deleteItem(l, l->value, l->timestamp);
        }
    }
}

List initList( double value , int timestamp )
{
    List new_item = ( List ) malloc ( sizeof ( struct list ) );
    new_item->value = value;
    new_item->timestamp = timestamp;
    new_item->mark = 0;
    new_item->next = NULL;
    new_item->prev = NULL;
    return new_item;
}

List addLast(List l, double value, int timestamp)
{
    List item, tmp = NULL;
    item = initList(value, timestamp);
    if (l == NULL)
    {
        return item;
    }
    else
    {
        tmp = l;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = item;
        item->prev = tmp;
        item->next = NULL;
        return l;
    }
}

List deleteList( List l)
{
    List tmp;
    while (l != NULL)
    {
        tmp = l;
        l = l->next;
        free(tmp);
    }
    return NULL;
}

List deleteItem(List l, double value, int timestamp)
{
    List p, q;
    p = initList(value, timestamp);
    q = initList(value, timestamp);
    p = q = l;
    while (p != NULL && value != p->value && timestamp != p->timestamp)
    {
        q = p;
        p = p->next;
    }
    
    if (p->value == value && p->timestamp == timestamp)
    {
        if (q == p)
            l = l->next;
        else
        {
            q->next = p->next;
            q->prev = p->prev;
        }
        return l;
    }
    return NULL;
}

void insertList(List a , List new , List b)
{
    List finish = new;
    while ( finish->next != NULL)
    {
        finish = finish->next; // memorez ultimul nod
    }
    a->next = new; //refac conexiunile
    new->prev = a;
    finish->next = b;
    b->prev = finish;
}
//--------------------------------------------------------------------------------------------------------------------------
