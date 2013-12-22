#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define LOGD(string) printf("%d\n", string);
#define LOGS(string) printf("%s\n", string);
#define color(param) printf("\033[%sm",param);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set_link.h"
#include "link.h"
#include "minunit.h"

/* LINK
   ---- */
void link__print(struct link * link);
struct link link__empty();
int link__is_empty(struct link * link);
int link__is_end_mark(struct link * link, struct element * element);
void link__add_head(struct link * link, struct element * element);
struct element * link__remove_head(struct link * link);
void link__add_after(struct link * link, struct element * after, struct element * toAdd);
struct element * link__remove_after(struct link * link, struct element * after);
void link__add_tail(struct link * link, struct element * element);
struct element * link__remove_tail(struct link * link);

/* SET
   --- */
struct set * set__empty();
int set__is_empty(struct set * set);
struct set * set__add(struct set * set, char c);
struct set * set__remove(struct set * set, char c);
int set__find(struct set * set, char c);
int set__size(struct set * set);
void set__unalloc(struct set * set);

#endif