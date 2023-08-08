#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

#define THREADS 2

#define device_path "/dev/mynode"
#define buff_len 200
#define accounts 100

void *routine(void *x){
	
	int fd;
	fd = open (device_path, O_WRONLY);
	
	int n;
	char data[buff_len];
	
	for(int i = 0; i <1000000; i++){
		n = rand()%accounts + 1;
		sprintf(data, "e,%d,0,1", n);
		write(fd, data, buff_len);
		printf("%d: WRITE DATA: %s\n", *(int*)x, data);
	}
	
	close(fd);
	
	int *t = (int*)malloc(sizeof(int));
	*t = rand()%1+1;
	pthread_exit((void*)t);
}

int main(void){
	
	pthread_t threads[THREADS];
	int thread_id[THREADS];
	int fd;
	for(int i = 0; i < THREADS; i++){
		thread_id[i] = i;
		pthread_create(&threads[i], NULL, routine, (void *)&thread_id[i]);
	}
	
	int *retval = (int*)malloc(sizeof(int));
	for(int i = 0; i < THREADS; i++){
		pthread_join(threads[i], (void **)&retval);
	}
	
		
	fd = open (device_path, O_WRONLY);
	char data[buff_len];
	read(fd, data, buff_len);
	printf("READ DATA: %s\n", data);
	fflush(stdout);
	close(fd);
}
