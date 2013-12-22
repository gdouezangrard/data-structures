#ifndef __LINK_H__
#define __LINK_H__

typedef struct _person {
	char * firstname;
	char * lastname;
	unsigned int year;
	unsigned char month;
	unsigned char day;
} person;

typedef struct _lelement
{
	struct _lelement* next;
	void * data;
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

#endif