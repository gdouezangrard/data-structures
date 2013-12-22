#include "set.h"
#include "link.h"
#include <stdio.h>

struct _set
{
	link l;
	int size;
};

struct _sequence
{
	set * s;
	lelement * e;
};

void set__free(set * s)
{
	while(s->l.head != NULL)
		lnk__remove_head(&(s->l));
	free(s);
}

set * set__empty()
{
	set * s = malloc(sizeof(set));
	if(s != NULL)
	{
		s->l = lnk__empty();
		s->size = 0;
	}
	return s;
}

size_t set__size(const set * s)
{
	return s->size;
}

int set__add(set * s, char c)
{
	if(set__find(s, c))
	{
		set__errno = SET__ELEMENT_DUPLICATION;
		return 1;
	}
	
	lelement* e = malloc(sizeof(lelement));
	e->data = c;
	
	lnk__add_tail(&(s->l), e);
	s->size++;
	return 0;
}

int set__remove(set * s, char c)
{
	lelement* e = s->l.head;
	
	if(e != NULL && (char) e->data == c)
	{
		lnk__remove_head(&(s->l));
		s->size--;
		return 0;
	}
	else if(e != NULL && e->next != NULL)
	{
		do {
			if((char) e->next->data == c)
			{
				lnk__remove_after(&s->l, e);
				s->size--;
				return 0;
			}
			else
				e = e->next;
		} while(e->next != NULL);
	}
	
	set__errno = SET__ELEMENT_UNKNOWN;
	return 1;
}

int set__is_empty(const set * s)
{
	return (s->size == 0);
}

int set__find(const set * s, char c)
{
	if(s->size == 0)
		return 0;
	
	lelement* e = s->l.head;
	
	do {
		if((char) e->data == c)
			return 1;
		e = e->next;
	} while(e != NULL);
	return 0;
}

int set__inter(const set * s1, const set * s2, set * si)
{
	lelement* e = s1->l.head;
	while(e != NULL)
	{
		if(set__find(s2, e->data))
			set__add(si, e->data);
		e = e->next;
	}
	return 0;
}

int set__union(const set * s1, const set * s2, set * su)
{
	lelement* e = s1->l.head;
	while(e != NULL)
	{
		set__add(su, e->data);
		e = e->next;
	}
	
	e = s2->l.head;
	while(e != NULL)
	{
		set__add(su, e->data);
		e = e->next;
	}
	return 0;
}

sequence * sequence__init(set * s)
{
	sequence * seq = malloc(sizeof(sequence));
	seq->s = s;
	seq->e = s->l.head;
	return seq;
}

sequence * sequence__next(sequence * seq)
{
	if (!lnk__is_end(seq->e))
		seq->e = seq->e->next;
	return seq;
}

int sequence__is_end(sequence * seq)
{
	return lnk__is_end(seq->e);
}

int sequence__getE(sequence * seq)
{
	return (seq->e->data);
}

void sequence__free(sequence * seq)
{
	free(seq);
}