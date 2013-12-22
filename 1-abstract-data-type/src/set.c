#include "set.h"

/* SET FUNCTIONS
   ------------- */
struct set set__empty() {
	struct set set = { 0 };
	return set;
}

int set__is_empty(struct set * set) {
	return (set->s[0] == 0);
}

int set__find(struct set * set, char c) {
	int i = 0;
	while (set->s[i]) {
		if (set->s[i] == c) {
			return i;
		}
		i++;
	}
	return -1;
}

void set__add(struct set * set, char c) {
	if (set__find(set, c) == -1) {
		int i = 0;
		char tmp1;
		char tmp2;
		while (set->s[i] < c && set->s[i] != 0) {
			i++;
		}
		tmp1 = c;
		do {
			tmp2 = set->s[i];
			set->s[i] = tmp1;
			tmp1 = tmp2;
			i++;
		} while (set->s[i-1] != 0);
	}
}

void set__remove(struct set * set, char c) {
	int i;
	if ((i = set__find(set, c)) != -1) {
		do {
			set->s[i] = set->s[i+1];
			i++;
		} while (set->s[i-1] != 0);
	}
}

int set__size(struct set * set) {
	int i = 0;
	char * tmp = set->s;
	while (*(tmp++)) {
		i++;
	}
	return i--;
}

struct set set__inter(struct set * s1, struct set * s2) {
	struct set set = {""};
	char * tmp = s1->s;
	char c;
	while(c = *(tmp++)) {
		if (set__find(s2, c)) {
			set__add(&set, c);
		}
	}
	return set;
}

struct set set__union(struct set * s1, struct set * s2) {
	struct set set = {""};
	char * tmp = s1->s;
	char c;
	while(c = *(tmp++)) {
		set__add(&set, c);
	}
	tmp = s2->s;
	while(c = *(tmp++)) {
		set__add(&set, c);
	}
	return set;
}

/* SET2 FUNCTIONS
   -------------- */
struct set2 set2__empty() {
	struct set2 set = { 0 };
	return set;
}

int set2__is_empty(struct set2 * set) {
	for (int i = 0 ; i < SET__SIZE2 ; i++) {
		if (set->bits[i] != 0) {
			return 0;
		}
	}
	return 1;
}

int set2__find(struct set2 * set, char c) {
	int i = c / 32;
	return ((set->bits[i] & (1 << 31 - (c - 32*i))) != 0);
}

void set2__add(struct set2 * set, char c) {
	int i = c / 32;
	set->bits[i] = set->bits[i] | (1 << 31 - (c - 32*i));
}

void set2__remove(struct set2 * set, char c) {
	int i = c / 32;
	set->bits[i] = (set->bits[i] & ~(1 << 31 - (c - 32*i)));
}

int set2__size(struct set2 * set) {
	int nb = 0;
	for (int j = 0 ; j < SET__SIZE2 ; j++) {
		int i = set->bits[j];
	    i = i - ((i >> 1) & 0x55555555);
	    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
	    i = ((i + (i >> 4)) & 0x0F0F0F0F);
	    nb += (i*(0x01010101))>>24;
	}
	return nb;
}

struct set2 set2__inter(struct set2 * s1, struct set2 * s2) {
	struct set2 set = { 0 };
	for (char i = 0 ; i < 255 ; i++) {
		if (set2__find(s1, i) && set2__find(s2, i)) {
			set2__add(&set, i);
		}
	}
	return set;
}

struct set2 set2__union(struct set2 * s1, struct set2 * s2) {
	struct set2 set = { 0 };
	for (char i = 0 ; i < 255 ; i++) {
		if (set2__find(s1, i)) {
			set2__add(&set, i);
		}
		if (set2__find(s2, i)) {
			set2__add(&set, i);
		}
	}
	return set;
}

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

/* TESTS2
   ------ */
void test_set2__size() {
	struct test test = {0, 0, "set2__size"};

	// set2__size(set2__empty()) = 0
	struct set2 s = set2__empty();
	if (set2__size(&s) != 0) {
		test.failed++;
	}
	else {
		test.passed++;
	}

	// set2__size(set2__add(s,c)) = set2__size(s) + 1 (if set2__find(s,c) = false)
	set2__add(&s, 'a');
	if (set2__size(&s) != 1) {
		test.failed++;
	}
	else {
		test.passed++;
	}

	// set2__size(set2__add(s,c)) = set2__size(s) (if set2__find(s,c) = true)
	set2__add(&s, 'a');
	if (set2__size(&s) != 1) {
		test.failed++;
	}
	else {
		test.passed++;
	}

	print_test(&test);
}

void test_set2__is_empty() {
	struct test test = {0, 0, "set2__is_empty"};

	// set2__is_empty(set2__empty()) = true
	struct set2 s = set2__empty();
	if (!set2__is_empty(&s)) {
		test.failed++;
	}
	else {
		test.passed++;
	}

	// set2__is_empty(set2__add(s, c)) = true
	set2__add(&s, 'a');
	if (set2__is_empty(&s)) {
		test.failed++;
	}
	else {
		test.passed++;
	}

	print_test(&test);
}

void test_set2__find() {
	struct test test = {0, 0, "set2__find"};

	// set2__find(set2__empty(), c) = false
	struct set2 s = set2__empty();
	if (set2__find(&s, 'a')) {
		test.failed++;
	}
	else {
		test.passed++;
	}

	// set2__find(set2__add(s, c), c) = true
	set2__add(&s, 'a');
	if (!set2__find(&s, 'a')) {
		test.failed++;
	}
	else {
		test.passed++;
	}

	// set2__find(set2__add(s, c), c') = set2__find(s, c')
	set2__add(&s, 'b');
	if (!set2__find(&s, 'b')) {
		test.failed++;
	}
	else {
		test.passed++;
	}
	if (set2__find(&s, 'd')) {
		test.failed++;
	}
	else {
		test.passed++;
	}

	print_test(&test);
}

int set2__is_equal(struct set2 * s1, struct set2 * s2) {
	for (int i = 0 ; i < SET__SIZE2 ; i++) {
		if (s1->bits[i] != s2->bits[i]) {
			return 0;
		}
	}
	return 1;
}

void test_set2__add() {
	struct test test = {0, 0, "set2__add"};

	// set2__add(s, c) = s (if set2__find(s,c = true))
	struct set2 s1 = set2__empty();
	set2__add(&s1, 'a');
	set2__add(&s1, 'a');
	struct set2 s2 = set2__empty();
	set2__add(&s2, 'a');
	if (!set2__is_equal(&s1, &s2)) {
		test.failed++;
	}
	else {
		test.passed++;
	}

	print_test(&test);
}


void test_set2__remove() {
	struct test test = {0, 0, "set2__remove"};

	// set2__remove(set2__empty(), c) = set2__empty()
	struct set2 s1 = set2__empty();
	set2__remove(&s1, 'a');
	struct set2 s2 = set2__empty();
	if (!set2__is_equal(&s1, &s2)) {
		test.failed++;
	}
	else {
		test.passed++;
	}

	// set2__remove(set2__add(s, c), c) = s
	s1 = set2__empty();
	set2__add(&s1, 'a');
	set2__remove(&s1, 'a');
	if (!set2__is_equal(&s1, &s2)) {
		test.failed++;
	}
	else {
		test.passed++;
	}

	// set2__remove(set2__add(s, c'), c) = set2__add(set2__remove(s, c'), c)
	s1 = set2__empty();
	set2__add(&s1, 'a');
	set2__remove(&s1, 'b');
	set2__remove(&s2, 'b');
	set2__add(&s2, 'a');
	if (!set2__is_equal(&s1, &s2)) {
		test.failed++;
	}
	else {
		test.passed++;
	}
	
	print_test(&test);
}

void tests() {
	test_set__size();
	test_set__is_empty();
	test_set__find();
	test_set__add();
	test_set__remove();
	test_set2__size();
	test_set2__is_empty();
	test_set2__find();
	test_set2__add();
	test_set2__remove();
}

int main(int argc, char ** argv) {
	tests();
	return 0;
}