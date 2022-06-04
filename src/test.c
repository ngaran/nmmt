#include <stdio.h>

typedef struct
{
	int a, b, c;
}
idk_t;

int main()
{
	idk_t idk;

	printf("%d\n", (int)&(idk.c) - (int)(&idk));

	return 0;
}
