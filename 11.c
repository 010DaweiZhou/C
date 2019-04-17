#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generic.h"
#include "11_1.h"

int main()
{
	char result[20] = {};
	getString(result);
	printf("%s\n",result);
	return 0;
}