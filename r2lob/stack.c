#include <stdio.h>

int vul_func(char *str)
{
	char buffer[50];
	strcpy(buffer, str);
	return 1;
}

int main(int argc, char **Argv)
{
	char str[240];
	FILE *badfile;
	badfile = open("badfile", "r");
	fread(str, sizeof(char), 200, badfile);
	vul_func(str);
	printf("Returned\n");
	return 1;
}
