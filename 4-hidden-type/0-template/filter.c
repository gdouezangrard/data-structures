#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "set.h"
#include "link.h"

int is_vowel(char * c)
{
	char voyelles[] = "AEIOUY";
	char * v = voyelles;
	while (*v) {
		if (*v == toupper(*c))
			return 1;
		v++;
	}
	return 0;
}

void * filter_vowel_map(void * p)
{
	char * c = p;
	if (is_vowel(c))
		return c;
	return NULL;
}

void * filter_lower_map(void * p)
{
	char * c = p;
	if (toupper(*c) != *c)
		return c;
	return NULL;
}

link * filter(void* (*map)(void*), sequence * s) {
	link * l = malloc(sizeof(link));
	*l = lnk__empty();
	void * c;
	for (sequence * p = s; !sequence__is_end(p); sequence__next(p)) {
		if ((c = map(sequence__getE(p))) != NULL) {
			lelement* e = malloc(sizeof(lelement));
			e->data = c;
			lnk__add_tail(l, e);
		}
	}
	return l;
}