#include "set.h"

#define SET__TAB_SIZE 8
#define SET__END_CHAR '\0'
#define SET__CASE_SIZE (8 * sizeof(unsigned long))

struct _set
{
	unsigned long bits[SET__TAB_SIZE];
	int size;
};

struct _sequence
{
	unsigned long * bits;
	int size;
};

void set__free(set * s)
{
	free(s);
}

set * set__empty()
{
	set * s = malloc(sizeof(set));
	if(s != NULL)
	{
		for(unsigned int i = 0; i < SET__TAB_SIZE; i++)
			s->bits[i] = 0;
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
	unsigned char b = (unsigned char) c;
	if(!set__find(s, c))
	{
		unsigned int i = b / SET__CASE_SIZE;
		s->size++;
		s->bits[i] = s->bits[i] | (((unsigned long)1) << (b % SET__CASE_SIZE));
		return 0;
	}
	else
	{
		set__errno = SET__ELEMENT_DUPLICATION;
		return 1;
	}
	
	return 0;
}

int set__remove(set * s, char c)
{
	unsigned char b = (unsigned char) c;
	unsigned int i = b / SET__CASE_SIZE;
	unsigned int j = b % SET__CASE_SIZE;
	
	if((s->bits[i] >> j) & 1)
	{
		s->bits[i] = s->bits[i] & ~(((unsigned long)1) << j);
		s->size--;
		return 0;
	}
	else
	{
		set__errno = SET__ELEMENT_UNKNOWN;
		return 1;
	}
}

int set__is_empty(const set * s)
{
	return s->size == 0;
}

int set__find(const set * s, char c)
{
	unsigned char b = (unsigned char) c;
	return (s->bits[b / SET__CASE_SIZE] >> (b % SET__CASE_SIZE) & 1) ? 1 : 0;
}

int set__inter(const set * s1, const set * s2, set * si)
{
	for(unsigned int i = 0; i < SET__TAB_SIZE; i++)
	{
		si->bits[i] = s1->bits[i] & s2->bits[i];
		for(unsigned int j = 0; j < SET__CASE_SIZE; j++)
			si->size += (si->bits[i] >> j) & 1;
	}
	return 0;
}

int set__union(const set * s1, const set * s2, set * su)
{
	for(unsigned int i = 0; i < SET__TAB_SIZE; i++)
	{
		su->bits[i] = s1->bits[i] | s2->bits[i];
		for(unsigned int j = 0; j < SET__CASE_SIZE; j++)
			su->size += (su->bits[i] >> j) & 1;
	}
	return 0;
}