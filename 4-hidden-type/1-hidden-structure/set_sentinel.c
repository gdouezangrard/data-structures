#include "set.h"

#define SET__END_CHAR '\0'
#define SET__SIZE 256

struct _set
{
	char s[SET__SIZE];
	int size;
};

struct _sequence
{
	set * s;
	char * c;
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
		s->s[0] = SET__END_CHAR;
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
	if(s->size == SET__SIZE - 1)
	{
		set__errno = SET__CAPACITY_EXCEEDED;
		return 1;
	}
	else if(c == SET__END_CHAR)
	{
		set__errno = SET__ELEMENT_UNKNOWN;
		return 1;
	}
	else if(set__find(s, c))
	{
		set__errno = SET__ELEMENT_DUPLICATION;
		return 1;
	}
	else
	{
		set__errno = 0;
		s->s[s->size] = c;
		s->s[++(s->size)] = SET__END_CHAR;
		return 0;
	}
}

int set__remove(set * s, char c)
{
	int i = 0;
	while(s->s[i] != SET__END_CHAR && s->s[i] != c) i++;
	if(s->s[i] != SET__END_CHAR)
	{
		s->s[i] = s->s[s->size-1];
		s->s[--(s->size)] = SET__END_CHAR;
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
	for(int i = 0; s->s[i] != SET__END_CHAR; i++)
		if(s->s[i] == c)
			return 1;
	return 0;
}

int set__inter(const set * s1, const set * s2, set * si)
{
	for(int i = 0; i < s1->size; i++)
		if(set__find(s2, s1->s[i]))
			set__add(si, s1->s[i]);
	return 0;
}

int set__union(const set * s1, const set * s2, set * su)
{
	int r = 0;
	for(int i = 0; i < s1->size && r == 0; i++)
	{
		r = set__add(su, s1->s[i]);
		if(set__errno == SET__ELEMENT_DUPLICATION)
			r = 0;
	}
	for(int i = 0; i < s2->size && r == 0; i++)
	{
		r = set__add(su, s2->s[i]);
		if(set__errno == SET__ELEMENT_DUPLICATION)
			r = 0;
	}
	return r;
}

int are_disjoint_array(char const * sq1, char const * sq2)
{
	for (char const * p1 = sq1; '\0' != *p1; ++p1)
		for (char const * p2 = sq2; '\0' != *p2; ++p2)
			if (*p1 == *p2)
				return 0;
	return 1;
}

sequence * sequence__init(set * s)
{
	sequence * seq = malloc(sizeof(sequence));
	seq->s = s;
	seq->c = s->s;
	return seq;
}

sequence * sequence__next(sequence * seq)
{
	if (seq->c != 0) {
		seq->c++;
	}
	return seq;
}

int sequence__is_end(sequence * seq)
{
	return *(seq->c) == 0;
}

int sequence__getE(sequence * seq)
{
	return *(seq->c);
}

void sequence__free(sequence * seq)
{
	free(seq);
}