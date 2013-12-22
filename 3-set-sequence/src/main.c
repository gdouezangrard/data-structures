#include <stdlib.h>
#include <stdio.h>
#include "set.h"
#include <assert.h>

// Je n'ai pas implémenté la sequence pour les bits parce-qu'avec le code généré sur le set, on recrée la roue pour la sequence... (d'où les #ifndef BITS)

int tests_run = 0;

static char * test_set__is_empty() {
	set * p_s = set__empty();
	mu_assert("-> set__is_empty(set__empty()) != false", set__is_empty(p_s) == 1);

	set__add(p_s, 'a');
	mu_assert("-> set__is_empty(set__add(set__empty(), 'a') != true", set__is_empty(p_s) == 0);

	set__free(p_s);
	return 0;
}

static char * test_set__add() {
	set * p_s = set__empty();
	set__remove(p_s, 'a');
	set__add(p_s, 'a');
	mu_assert("-> set__is_empty(set__add(set__remove(set__empty(),'a'),'a')) == true", set__is_empty(p_s) == 0);
	set__free(p_s);

	p_s = set__empty();
	set__add(p_s, 'a');
	set__remove(p_s, 'a');
	mu_assert("-> set__is_empty(set__remove(set__add(set__empty(),'a'),'a')) == false", set__is_empty(p_s) == 1);
	set__free(p_s);

	p_s = set__empty();
	set__add(p_s, 'a');
	mu_assert("-> set__find(set__add(set__empty(),'a'),'a') == false", set__find(p_s, 'a') == 1);
	set__free(p_s);
	return 0;
}

static char * test_set__remove() {
	set * p_s = set__empty();
	set__remove(p_s, 'a');
	mu_assert("-> set__is_empty(set__remove(set__empty(), 'a')) == false", set__is_empty(p_s) == 1);
	set__free(p_s);

	p_s = set__empty();
	set__add(p_s, 'b');
	set__remove(p_s, 'a');
	mu_assert("-> set__size(set__remove(set__add(set__empty(),'b'),'a')) != 1", set__size(p_s) == 1);
	set__free(p_s);

	return 0;
}

static char * test_set__find() {
	set * p_s = set__empty();
	mu_assert("-> set__find(set__empty(),'a') == true", set__find(p_s, 'a') == 0);

	set__add(p_s, 'a');
	mu_assert("-> set__find(set__add(set__empty(),'a'), 'a') == false", set__find(p_s,'a') == 1);
	set__free(p_s);

	return 0;
}

static char * test_set__size() {
	set * p_s = set__empty();
	mu_assert("-> set__size(set__empty()) == 0", set__size(p_s) == 0);

	set__add(p_s, 'a');
	mu_assert("-> set__size(set__add(set__empty(),'a')) == 1", set__size(p_s) == 1);
	return 0;
}
#ifndef BITS
	static char * test_sequence() {
		set * p_s = set__empty();
		sequence * p_seq = sequence__init(p_s);
		mu_assert("-> sequence__is_end(sequence__init(set__empty())) == false", sequence__is_end(p_seq) == 1);
		set__free(p_s);
		sequence__free(p_seq);

		p_s = set__empty();
		set__add(p_s, 'a');
		p_seq = sequence__init(p_s);
		mu_assert("-> sequence__is_end(sequence__init(set__add(set__empty(), 'a'))) == true", sequence__is_end(p_seq) == 0);
		set__free(p_s);
		sequence__free(p_seq);

		p_s = set__empty();
		set__add(p_s, 'a');
		p_seq = sequence__init(p_s);
		sequence__next(p_seq);
		mu_assert("-> sequence__is_end(sequence__next(sequence__init(set__add(set__empty(), 'a')))) == false", sequence__is_end(p_seq) == 1);
		set__free(p_s);
		sequence__free(p_seq);

		set * p_s1 = set__empty();
		set__add(p_s1, 'a');
		set__add(p_s1, 'c');
		sequence * p_seq1 = sequence__init(p_s1);

		set * p_s2 = set__empty();
		set__add(p_s2, 'a');
		set__add(p_s2, 'b');
		sequence * p_seq2 = sequence__init(p_s2);
		mu_assert("-> sequence__is_equal('a', 'a') == false", (sequence__getE(p_seq1) == sequence__getE(p_seq2)) == 1);
		sequence__next(p_seq1);
		sequence__next(p_seq2);
		mu_assert("-> sequence__is_equal('a', 'b') == true", (sequence__getE(p_seq1) == sequence__getE(p_seq2)) == 0);
		set__free(p_s1);
		sequence__free(p_seq1);
		set__free(p_s2);
		sequence__free(p_seq2);
		return 0;
	}

	static char * test_sequences() {
		set * p_s1 = set__empty();
		set__add(p_s1, 'a');
		set__add(p_s1, 'c');
		set__add(p_s1, 'd');
		sequence * p_seq1 = sequence__init(p_s1);

		set * p_s2 = set__empty();
		set__add(p_s2, 'b');
		set__add(p_s2, 'a');
		set__add(p_s2, 'A');
		sequence * p_seq2 = sequence__init(p_s2);

		mu_assert("-> are_disjoint_sequence([a, c, d], [A, b, a]) == true", are_disjoint_sequence(p_seq1, p_seq2) == 0);

		set__free(p_s1);
		sequence__free(p_seq1);
		set__free(p_s2);
		sequence__free(p_seq2);

		p_s1 = set__empty();
		set__add(p_s1, 'b');
		set__add(p_s1, 'c');
		p_seq1 = sequence__init(p_s1);

		p_s2 = set__empty();
		set__add(p_s2, 'd');
		set__add(p_s2, 'e');
		p_seq2 = sequence__init(p_s2);

		mu_assert("-> are_disjoint_sequence([b, c], [d, e]) == false", are_disjoint_sequence(p_seq1, p_seq2) == 1);

		set__free(p_s1);
		sequence__free(p_seq1);
		set__free(p_s2);
		sequence__free(p_seq2);
		return 0;
	}
#endif

static char * all_tests() {
	// SETS
	mu_run_test(test_set__is_empty);
	mu_run_test(test_set__add);
	mu_run_test(test_set__remove);
	mu_run_test(test_set__find);
	mu_run_test(test_set__size);

	#ifndef BITS
		// SEQUENCES
		mu_run_test(test_sequence);
		mu_run_test(test_sequences);
	#endif

	return 0;
}

int main(int argc, char** argv)
{
	// File characters
	if(argc != 2)
	{
		printf("Usage: %s [filename]\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	FILE* file = fopen(argv[1], "rb");
	if(file == NULL)
	{
		printf("File unreadable\n");
		return EXIT_FAILURE;
	}
	
	int c = fgetc(file);
	set* s = set__empty();
	
	while(c != EOF)
	{
		if (c >= 32 && c < 128) {
			set__add(s, (char) c); // c != SET_END_CHAR
		}
		c = fgetc(file);
	}
	
	printf("Characters found: %d\n", (int) set__size(s));
	for(int i = 32; i < 128; i++)
	{
		if(set__find(s, (char) i))
			printf("Character %c (%d) found.\n", (char) i, i);
	}
	
	set__free(s);
	fclose(file);

	// TESTS
	char *result = all_tests();
	if (result != 0) {
		color("31");
		printf("%s\n", result);
		color("0");
	}
	else {
		color("32");
		printf("ALL TESTS PASSED\n");
		color("0");
	}
	printf("Tests run: %d\n", tests_run);

	return result != 0;

	return EXIT_SUCCESS;
}

#ifndef BITS
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
#endif