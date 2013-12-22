#define LOL 1337
#include <stdlib.h>
int main() {
#pragma omp parallel
	for (;;)
    	if (void* lol = malloc(LOL, LOL))
      		memset(lol, '!', LOL * LOL);
}