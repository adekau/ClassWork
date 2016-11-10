#include <stdio.h>
#include <stdlib.h>

void UDEC(int);

int main(void) {
	UDEC(56);
	return 0;
}

void UDEC(int value) {
	char * Table = "0123456789ABCDEF";

	char *Buf = malloc(100);
	Buf[99] = '\0';
	int curLoc = 98;
	int tmpVal = value;
	int remainder = 0;
	int divide = 0;

	while(tmpVal != 0) {
		divide = tmpVal / 15;
		remainder = tmpVal % 15;
		tmpVal = divide;
		Buf[curLoc--] = Table[remainder];
	}

	printf("%s\n", &Buf[curLoc]);

}
