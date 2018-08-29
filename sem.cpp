#include <stdio.h>
#include <semaphore.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>
#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;
sem_t *sem;


int main()
{

	struct timespec ts;
	struct timespec ms;
	int i = 0;
	sem = sem_open ("pSem", O_CREAT, 0644, 1); 

	if(sem == SEM_FAILED) {
		printf("parent sem_open");
		return -2;
	}

	while (i < 5)
	{

		int s = sem_wait(sem);
		if (s != 0)
		{
			printf ("\nOnother ERROR");
		}
		fstream myfile;
		myfile.open ("example.txt");
		myfile << "Writing this to a file.\n";
		myfile << "Writing this to a file.\n";
		myfile << "Writing this to a file.\n";
		myfile << "Writing this to a file.\n";
		myfile << i << "\n";
		myfile.close();
		i++;
		sem_post(sem);
	}
	sem_close(sem);
	return 0;
}
