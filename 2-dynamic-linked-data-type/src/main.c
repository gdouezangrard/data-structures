#include "main.h"

int tests_run = 0;

static char * test_set__is_empty() {
	mu_assert("-> set__is_empty(set__empty()) != false", set__is_empty(set__empty()) == 1);
	mu_assert("-> set__is_empty(set__add(set__empty(), 'a') != true", set__is_empty(set__add(set__empty(), 'a')) == 0);
	return 0;
}

static char * test_set__add() {
	mu_assert("-> set__is_empty(set__add(set__remove(set__empty(),'a'),'a')) == true", set__is_empty(set__add(set__remove(set__empty(),'a'),'a')) == 0);
	mu_assert("-> set__is_empty(set__remove(set__add(set__empty(),'a'),'a')) == false", set__is_empty(set__remove(set__add(set__empty(),'a'),'a')) == 1);
	mu_assert("-> set__find(set__add(set__empty(),'a'),'a') == false", set__find(set__add(set__empty(),'a'),'a') == 1);
	return 0;
}

static char * test_set__remove() {
	mu_assert("-> set__is_empty(set__remove(set__empty() == false", set__is_empty(set__remove(set__empty(),'a')) == 1);
	mu_assert("-> set__size(set__remove(set__add(set__empty(),'b'),'a')) != 1", set__size(set__remove(set__add(set__empty(),'b'),'a')) == 1);
	return 0;
}

static char * test_set__find() {
	mu_assert("-> set__find(set__empty(),'a') == true", set__find(set__empty(),'a') == 0);
	mu_assert("-> set__size(set__remove(set__add(set__empty(),'b'),'a')) == false", set__find(set__add(set__empty(),'a'),'a') == 1);
	return 0;
}

static char * test_set__size() {
	mu_assert("-> set__size(set__empty()) == 0", set__size(set__empty()) == 0);
	mu_assert("-> set__size(set__add(set__empty(),'a')) == 1", set__size(set__add(set__empty(),'a')) == 1);
	return 0;
}

static char * all_tests() {
	mu_run_test(test_set__is_empty);
	mu_run_test(test_set__add);
	mu_run_test(test_set__remove);
	mu_run_test(test_set__find);
	mu_run_test(test_set__size);
	return 0;
}

int main(int argc, char ** argv) {
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
}

/* LINK
   ---- */
void link__print(struct link * link) {
	struct element * e = link->head;
	printf("LINK : ");
	while (e != NULL) {
		printf("%c ", e->data);
		e = e->next;
	}
	printf("\n");
}
struct link link__empty() {
	struct link link = { NULL };
	return link;
}
int link__is_empty(struct link * link) {
	return (link->head == NULL);
}
int link__is_end_mark(struct link * link, struct element * element) {
	return (element->next == NULL);
}
void link__add_head(struct link * link, struct element * element) {
	struct element * tmp = link->head;
	link->head = element;
	element->next = tmp;
}
struct element * link__remove_head(struct link * link) {
	if (!link__is_empty(link)) {
		struct element * tmp = link->head->next;
		struct element * removed = link->head;
		link->head = tmp;
		return removed;
	}
	return NULL;
}
void link__add_after(struct link * link, struct element * after, struct element * toAdd) {
	struct element * tmp = after->next;
	after->next = toAdd;
	toAdd->next = tmp;
}
struct element * link__remove_after(struct link * link, struct element * after) {
	if (!link__is_end_mark(link, after)) {
		struct element * element = after->next;
		after->next = after->next->next;
		return element;
	}
}
void link__add_tail(struct link * link, struct element * element) {
	if (link__is_empty(link)) {
		link__add_head(link, element);
	}
	else {
		struct element * tmp = link->head;
		while (!link__is_end_mark(link, tmp)) {
			tmp = tmp->next;
		}
		tmp->next = element;
	}
}
struct element * link__remove_tail(struct link * link) {
	if (!link__is_empty(link) && !link__is_end_mark(link, link->head)) {
		struct element * tmp = link->head;
		while (!link__is_end_mark(link, tmp->next)) {
			tmp = tmp->next;
		}
		struct element * save = tmp->next;
		tmp->next = tmp->next->next;
		return save;
	}
	else if (link__is_end_mark(link, link->head)) {
		struct element * save = link->head;
		link->head = link->head->next;
		return save;
	}
	return NULL;
}

/* SET
   --- */
struct set * set__empty() {
	struct set * set = NULL;
	if ((set = malloc(sizeof(struct set))) == NULL) {
		exit(1);
	}
	set->link = NULL;
	if ((set->link = malloc(sizeof(struct link))) == NULL) {
		exit(1);
	}
	set->link->head = NULL;
	return set;
}
int set__is_empty(struct set * set) {
	return link__is_empty(set->link);
}
struct set * set__add(struct set * set, char c) {
	struct element * element = malloc(sizeof(struct element));
	element->data = c;
	struct element * after = set->link->head;
	if (!set__is_empty(set)) {
		char head = 0;
		struct element * before = NULL;
		while (!link__is_end_mark(set->link, after) && after->data < c) {
			before = after;
			after = after->next;
		}
		if (before == NULL) {
			link__add_head(set->link, element);
		}
		else if (link__is_end_mark(set->link, after)) {
			link__add_tail(set->link, element);
		}
		else {
			link__add_after(set->link, before, element);
		}
	}
	else {
		link__add_head(set->link, element);
	}
	return set;
}
struct set * set__remove(struct set * set, char c) {
	if (!set__is_empty(set)) {
		struct element * after = set->link->head;
		if (after->data == c) {
			free(link__remove_head(set->link));
		}
		else {
			struct element * before = NULL;
			while (!link__is_end_mark(set->link, after) && after->data != c) {
				before = after;
				after = after->next;
			}
			if (before != NULL) {
				if (after->data == c) {
					free(link__remove_after(set->link, before));
				}
			}
		}
	}
	return set;
}
int set__find(struct set * set, char c) {
	if (!link__is_empty(set->link)) {
		struct element * after = set->link->head;
		while (!link__is_end_mark(set->link, after)) {
			if (after->data == c) {
				return 1;
			}
			after = after->next;
			if (link__is_end_mark(set->link, after)) {
				return (after->data == c);
			}
		}
		if (link__is_end_mark(set->link, after)) {
			return (after->data == c);
		}
	}
	return 0;
}
int set__size(struct set * set) {
	int count = 0;
	if (link__is_empty(set->link)) {
		return 0;
	}
	else {
		struct element * element = set->link->head;
		count++;
		while (!link__is_end_mark(set->link, element)) {
			element = element->next;
			count++;
		}
		return count++;
	}
}
void set__unalloc(struct set * set) {
	if (!set__is_empty(set)) {
		struct element * e = set->link->head;
		struct element * tmp = NULL;
		while (!link__is_end_mark(set->link, e)) {
			tmp = e;
			e = e->next;
			free(tmp);
		}
		free(e);
	}
	free(set->link);
	free(set);
}