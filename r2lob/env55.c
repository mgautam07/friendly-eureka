#include <stdio.h>

int main()
{
	char *shell = (char *) getenv("MYSHELL");
	if(shell)
	{
		printf("val: %s\n", shell);
		printf("addr: %x\n", (unsigned int)shell);
	}
	return 1;
}
