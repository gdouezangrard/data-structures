#include <stdlib.h>
#include <stdio.h>
#include "set.h"
#include <assert.h>

// With chars
int isEqual_char(char * c1, char * c2) {
	return *c1 == *c2;
}
void assign_char(char * c1, char * c2) {
	*c1 = *c2;
}
void allocate_char(char ** c) {
	*c = malloc(sizeof(char));
}
void print_char(char * c) {
	printf("%c", *c);
}

int main(int argc, char** argv)
{
	set * pre = set__empty(assign_char, isEqual_char, allocate_char, print_char);
	char c[] = "Bijour !";
	char * i = c;
	while (*i) {
		set__add(pre, i);
		i++;
	}

	sequence * s = sequence__init(pre);
	link * l = filter(filter_lower_map, s);

	set * post = set__empty(assign_char, isEqual_char, allocate_char, print_char);
	set__set_link(post, l);

	print_set(pre);
	print_set(post);

	return EXIT_SUCCESS;
}