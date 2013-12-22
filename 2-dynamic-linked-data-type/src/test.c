#include "test.h"

/* TESTS
   ----- */
void print_test(struct test * test) {
	printf("Function %s:\t%d/%d tests passed", test->function, test->passed, test->failed + test->passed);
	if (test->failed == 0) {
		color("32");
		printf("\tSUCCESS\n");
		color("0");
	}
	else {
		color("31");
		printf("\tFAILED\n");
		color("0");
	}
}

void test_set__size() {
	struct test test = {0, 0, "set__size"};

	// set__size(set__empty()) = 0
	struct set s = set__empty();
	if (set__size(&s) != 0) {
		test.failed++;
	}
	else {
		test.passed++;
	}

	// set__size(set__add(s,c)) = set__size(s) + 1 (if set__find(s,c) = false)
	set__add(&s, 'a');
	if (set__size(&s) != 1) {
		test.failed++;
	}
	else {
		test.passed++;
	}

	// set__size(set__add(s,c)) = set__size(s) (if set__find(s,c) = true)
	set__add(&s, 'a');
	if (set__size(&s) != 1) {
		test.failed++;
	}
	else {
		test.passed++;
	}

	print_test(&test);
}

void test_set__is_empty() {
	struct test test = {0, 0, "set__is_empty"};

	// set__is_empty(set__empty()) = true
	struct set s = set__empty();
	if (!set__is_empty(&s)) {
		test.failed++;
	}
	else {
		test.passed++;
	}

	// set__is_empty(set__add(s, c)) = true
	set__add(&s, 'a');
	if (set__is_empty(&s)) {
		test.failed++;
	}
	else {
		test.passed++;
	}

	print_test(&test);
}

void test_set__find() {
	struct test test = {0, 0, "set__find"};

	// set__find(set__empty(), c) = false
	struct set s = set__empty();
	if (set__find(&s, 'a') != -1) {
		test.failed++;
	}
	else {
		test.passed++;
	}

	// set__find(set__add(s, c), c) = true
	set__add(&s, 'a');
	if (set__find(&s, 'a') == -1) {
		test.failed++;
	}
	else {
		test.passed++;
	}

	// set__find(set__add(s, c), c') = set__find(s, c')
	set__add(&s, 'b');
	if (set__find(&s, 'b') == -1) {
		test.failed++;
	}
	else {
		test.passed++;
	}
	if (set__find(&s, 'd') != -1) {
		test.failed++;
	}
	else {
		test.passed++;
	}

	print_test(&test);
}

void test_set__add() {
	struct test test = {0, 0, "set__add"};

	// set__add(s, c) = s (if set__find(s,c = true))
	struct set s1 = set__empty();
	set__add(&s1, 'a');
	set__add(&s1, 'a');
	struct set s2 = set__empty();
	set__add(&s2, 'a');
	if (strcmp(s1.s, s2.s)) {
		test.failed++;
	}
	else {
		test.passed++;
	}

	print_test(&test);
}

void test_set__remove() {
	struct test test = {0, 0, "set__remove"};

	// set__remove(set__empty(), c) = set__empty()
	struct set s1 = set__empty();
	set__remove(&s1, 'a');
	struct set s2 = set__empty();
	if (strcmp(s1.s, s2.s)) {
		test.failed++;
	}
	else {
		test.passed++;
	}

	// set__remove(set__add(s, c), c) = s
	s1 = set__empty();
	set__add(&s1, 'a');
	set__remove(&s1, 'a');
	if (strcmp(s1.s, s2.s)) {
		test.failed++;
	}
	else {
		test.passed++;
	}

	// set__remove(set__add(s, c'), c) = set__add(set__remove(s, c'), c)
	s1 = set__empty();
	set__add(&s1, 'a');
	set__remove(&s1, 'b');
	set__remove(&s2, 'b');
	set__add(&s2, 'a');
	if (strcmp(s1.s, s2.s)) {
		test.failed++;
	}
	else {
		test.passed++;
	}
	
	print_test(&test);
}
