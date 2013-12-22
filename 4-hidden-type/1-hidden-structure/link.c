#include <stdlib.h>
#include "link.h"

link lnk__empty()
{
	link l = { .head = NULL, .tail = NULL };
	return l;
}

int lnk__is_end(const lelement* e)
{
	return e == NULL;
}

void lnk__add_head(link* l, lelement* c)
{
	c->next = l->head;
	
	l->head = c;
	
	if(c->next == NULL)
		l->tail = c;
}

void lnk__remove_head(link* l)
{
	if(l->head != NULL)
	{
		lelement* c = l->head;
		
		l->head = l->head->next;
		if(l->tail == c)
			l->tail = NULL;
		free(c);
	}
}

void lnk__add_tail(link* l, lelement* c)
{
	if(l->tail == NULL)
		lnk__add_head(l, c);
	else
	{
		c->next = NULL;
		
		l->tail->next = c;
		l->tail = c;
	}
}

void lnk__remove_after(link* l, lelement* c)
{
	if(c == NULL)
		lnk__remove_head(l);
	else if(c != l->tail)
	{
		lelement* c2 = c->next;
		c->next = c2->next;
		if(l->tail == c2)
			l->tail = c;
		free(c2);
	}
}

int are_disjoint_link(link const * sq1, link const * sq2)
{
	for (lelement const * p1 = sq1->head; lnk__is_end(p1); p1 = p1->next)
		for (lelement * p2 = sq2->head; lnk__is_end(p2); p2 = p2->next)
			if (p1->data == p2->data)
				return 0;
	return 1;
}