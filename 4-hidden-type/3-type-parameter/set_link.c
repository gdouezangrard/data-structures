#include "set.h"
#include "link.h"
#include <stdio.h>
#include <assert.h>

struct _set
{
	link l;
	int size;
	void* (*assign)(void*, void*);
	int (*isEqual)(void*, void*);
	void (*allocate)(void*);
	void (*print)(void*);
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

set * set__empty(void* (*assign)(void*, void*), int (*isEqual)(void*, void*), void (*allocate)(void*), void (*print)(void*))
{
	set * s = malloc(sizeof(set));
	if(s != NULL)
	{
		s->l = lnk__empty();
		s->size = 0;
		s->assign = assign;
		s->isEqual = isEqual;
		s->allocate = allocate;
		s->print = print;
	}
	return s;
}

set * set__set_link(set * target, link * source)
{
	target->l = *source;
	return target;
}

size_t set__size(const set * s)
{
	return s->size;
}

int set__add(set * s, void * c)
{
	if(set__find(s, c))
	{
		set__errno = SET__ELEMENT_DUPLICATION;
		return 1;
	}
	
	lelement* e = malloc(sizeof(lelement));

	s->allocate(&(e->data));
	assert(e->data != NULL);
	s->assign(e->data, c);
	
	lnk__add_tail(&(s->l), e);
	s->size++;
	return 0;
}

int set__remove(set * s, void * c)
{
	lelement* e = s->l.head;
	
	if(e != NULL && e->data == c)
	{
		lnk__remove_head(&(s->l));
		s->size--;
		return 0;
	}
	else if(e != NULL && e->next != NULL)
	{
		do {
			if(s->isEqual(e->next->data, c))
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

int set__find(const set * s, void * c)
{
	if(s->size == 0)
		return 0;
	
	lelement* e = s->l.head;
	
	do {
		if(s->isEqual(e->data, c))
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

void * sequence__getE(sequence * seq)
{
	return (seq->e->data);
}

void sequence__free(sequence * seq)
{
	free(seq);
}

int are_disjoint_sequence(sequence * sq1, sequence * sq2)
{
	for (sequence * p1 = sq1; !sequence__is_end(p1); sequence__next(p1))
		for (sequence * p2 = sq2; !sequence__is_end(p2); sequence__next(p2))
			if (sequence__getE(p1) ==  sequence__getE(p2))
				return 0;
	return 1;
}

void print_set(set * s)
{
	sequence * seq = sequence__init(s);
	while(!sequence__is_end(seq)) {
		seq->s->print(sequence__getE(seq));
		sequence__next(seq);
	}
	printf("\n");
	sequence__free(seq);
}