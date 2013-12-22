#ifndef __SET__
#define __SET__

#define color(param) printf("\033[%sm",param);

#include <stdlib.h>
#include "set_errno.h"
#include "minunit.h"
#include "link.h"

typedef struct _set set;
typedef struct _sequence sequence;

void   set__free(set *);
set *  set__empty();
size_t set__size(const set *);
int    set__add(set *, char);
int    set__remove(set *, char);
int    set__is_empty(const set *);
int    set__find(const set *, char);
int    set__inter(const set * s1, const set * s2, set * si);
int    set__union(const set * s1, const set * s2, set * su);
int    are_disjoint_sequence(sequence * sq1, sequence * sq2);

// Sequence
sequence * 	sequence__init(set *);
sequence * 	sequence__next(sequence *);
int 		sequence__is_end(sequence *);
int 		sequence__getE(sequence *);
void 		sequence__free(sequence *);
void 		print_set(set *);

// Filters
int 	is_vowel(char c);
link * 	filter(char (*map)(char), sequence *);
char 	filter_vowel_map(char c);

#endif