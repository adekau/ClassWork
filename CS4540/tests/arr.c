#include <stdio.h>
#include <stdlib.h>

int main () {
	int *arr = malloc(sizeof *arr * 20);
	int i;
	for (i = 0; i < 20; i++) {
		*arr++ = i;
		printf("%i\n", arr[i]);
	}

	//printf("\n%lu %i\n", arr, *--arr);
}
