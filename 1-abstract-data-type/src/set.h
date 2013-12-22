#ifndef SET_H_INCLUDED
#define SET_H_INCLUDED
#define SET__SIZE 256
#define SET__SIZE2 8
#define color(param) printf("\033[%sm",param)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* Structure definition
   -------------------- */
struct set {
	char s[SET__SIZE];
};
struct set2 {
	unsigned int bits[SET__SIZE2];
};

struct set set__empty();
int set__is_empty(struct set * set);
void set__add(struct set * set, char c);
void set__remove(struct set * set, char c);
int set__find(struct set * set, char c);
int set__size(struct set * set);
struct set set__inter(struct set * s1, struct set * s2);
struct set set__union(struct set * s1, struct set * s2);

struct set2 set2__empty();
int set2__is_empty(struct set2 * set);
void set2__add(struct set2 * set, char c);
void set2__remove(struct set2 * set, char c);
int set2__find(struct set2 * set, char c);
int set2__size(struct set2 * set);
struct set2 set2__inter(struct set2 * s1, struct set2 * s2);
struct set2 set2__union(struct set2 * s1, struct set2 * s2);

/* Tests
   ----- */
struct test {
	int failed;
	int passed;
	char function[20];
};

#endif