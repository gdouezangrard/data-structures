#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "link.h"

int is_vowel(char c) {
	char voyelles[] = "AEIOUY";
	char * v = voyelles;
	while (*v++) {
		if (*v == c)
			return 1;
	}
	return 0;
}

char filter_vowel_map(char c) {
	if (is_vowel(c))
		return c;
	return 0;
}

link * filter(char (*map)(char), sequence * s) {
	link * l = malloc(sizeof(link));
	*l = lnk__empty();
	char c;
	for (sequence * p = s; !sequence__is_end(p); sequence__next(p)) {
		if (c = map((char) sequence__getE(p))) {
			lelement* e = malloc(sizeof(lelement));
			e->data = c;
			lnk__add_tail(l, e);
		}
	}
	return l;
}