#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	fork();
	int id = fork();
	if (id != 0)
		fork();
	printf("hello world\n");
	
	// if (id == 0)
	// 	printf("we are in shild process\n");
	// else
	// 	printf("we are in main process\n");
}