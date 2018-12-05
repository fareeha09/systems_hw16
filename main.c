#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main(){
	key_t key;
	int shmid;

	key = ftok("main.c", 'R');
	shmid = shmget(key, 200, 0644 | IPC_CREAT); //permissions  (rw-r--r--)
	char *data = shmat(shmid, (void *)0, 0);
	
	// if (data == (char *)(-1))
		// printf("error\n");
	
	if (* data){
		printf("Here are the shared contents: %s\n", data);
	}
	else{
		printf("Data just created, no content\n");
	}
	
	printf("Do you want to change the data in the segment?: (yes or no)");
	char answer[200];
	fgets(answer, 200, stdin);
	answer[3]='\0';
	
	if (!strcmp(answer, "yes")){ 
		printf("Enter a new string: ");
		fgets(answer, 200, stdin);
		strcpy(data, answer);
		printf("ok. new string is: %s\n", data);
	} 
	else if (strcmp(answer, "no")){
		printf("ok\n");
	}
	
	printf("Do you want to delete the segment?: (yes or no)");
	fgets(answer, 200, stdin);	
	answer[3]='\0';
	
	if (!strcmp(answer, "yes")){ 
		//printf("woo\n");
		shmdt(data);
		shmctl(shmid, IPC_RMID, NULL);
		printf("ok deleted. bye.\n");
	} 
	else if (strcmp(answer, "no")){
		printf("ok bye.\n");
	}
	
	
}