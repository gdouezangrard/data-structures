#include <stdlib.h>
#include <stdio.h>
#include "set.h"
#include <assert.h>

struct _set
{
	link l;
	int size;
};

int main(int argc, char** argv)
{
	set * truc = set__empty();
	set__add(truc, 'Y');
	set__add(truc, 'O');
	set__add(truc, 'L');
	set__add(truc, 'U');

	sequence * s = sequence__init(truc);
	link * l = filter(filter_vowel_map, s);

	set * p = set__empty();
	p->l = *l;

	print_set(p);

	return EXIT_SUCCESS;
}

int are_disjoint_sequence(sequence * sq1, sequence * sq2)
{
	for (sequence * p1 = sq1; !sequence__is_end(p1); sequence__next(p1))
		for (sequence * p2 = sq2; !sequence__is_end(p2); sequence__next(p2))
			if (sequence__getE(p1) ==  sequence__getE(p2))
				return 0;
	return 1;
}

void print_set(set * s) {
	sequence * seq = sequence__init(s);
	while(!sequence__is_end(seq)) {
		printf("%c ", sequence__getE(seq));
		sequence__next(seq);
	}
	printf("\n");
	sequence__free(seq);
}

set * symetric_diff(set * s1, set * s2) {
	set * diff;
	diff = set__empty();
	sequence * seq = sequence__init(s1);
	char c;
	while(!sequence__is_end(seq)) {
		c = sequence__getE(seq);
		if (!set__find(s2, c)) {
			set__add(diff, c);
		}
		sequence__next(seq);
	}
	sequence__free(seq);
	seq = sequence__init(s2);
	while(!sequence__is_end(seq)) {
		c = sequence__getE(seq);
		if (!set__find(s1, c)) {
			set__add(diff, c);
		}
		sequence__next(seq);
	}
	free(seq);
	return diff;
}