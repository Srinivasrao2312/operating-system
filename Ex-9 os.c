#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
int main()
{
int i;
void *shared_memory;
char buff[100];
int shmid;
printf("Key of shared memory is %d\n",shmid);
printf("Process attached at %p\n",shared_memory);
printf("Data read from shared memory is : %s\n",(char *)shared_memory);
}