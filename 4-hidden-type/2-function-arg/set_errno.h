#ifndef _SET_ERRNO_H_
#define _SET_ERRNO_H_

#define SET__CAPACITY_EXCEEDED           1
#define SET__ELEMENT_DUPLICATION         2
#define SET__ELEMENT_UNKNOWN             3
#define SET__INDEX_CAPACITY_EXCEEDED     4
#define SET__INDEX_ELEMENT_DUPLICATION   5
#define SET__INDEX_ELEMENT_UNKNOWN       6

extern int set__errno;

#endif