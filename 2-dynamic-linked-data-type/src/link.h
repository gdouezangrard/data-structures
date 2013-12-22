#ifndef LINK_H_INCLUDED
#define LINK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

struct element {
	char data;
	struct element * next;
};

struct link {
	struct element * head;
};

#endif