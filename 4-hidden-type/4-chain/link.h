#ifndef __LINK_H__
#define __LINK_H__

typedef struct _lelement
{
	struct _lelement* next;
	unsigned int data;
} lelement;

typedef struct _link
{
	lelement* head;
	lelement* tail;
} link;

link lnk__empty();
int lnk__is_end(const lelement*);
void lnk__add_head(link*, lelement* c);
void lnk__remove_head(link*);
void lnk__add_tail(link*, lelement* c);
void lnk__remove_after(link*, lelement*);

int are_disjoint_link(link const * sq1, link const * sq2);

#endif