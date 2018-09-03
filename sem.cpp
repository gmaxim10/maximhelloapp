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
#include <sstream>
#include <random>

using namespace std;

void sighandler(int signo)
{
	if (signo == SIGTERM || signo == SIGINT)
	{
		done = 1;
	}
}


std::fstream& GotoLine(std::fstream& file, unsigned int num){
	file.seekg(std::ios::beg);
	for(int i=0; i < num - 1; ++i){
		file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	}
	return file;
}


int main(int argc, char* argv[])
{
	sem_t *sem;
	random_device rd;
	mt19937 rng(rd());
	uniform_int_distribution<int> uni_big(0, 100000);
	uniform_int_distribution<int> uni_small(0, 2);

	if (argc != 2)
	{
		printf ("\nYou must Enter number of iterations");
		return -1;
	}

	struct timespec ts;
	struct timespec ms;
	struct timespec tm;
	int i = 0;
	sem = sem_open ("p1000", O_CREAT, 0644, 1); 

	if(sem == SEM_FAILED) 
	{
		printf("parent sem_open");
		return -2;
	}

	string myStream = argv[1];
	istringstream buffer(myStream);
	int value;
	buffer >> value;
	while (i < value)
	{
		/*
		clock_gettime(CLOCK_REALTIME, &tm);
		tm.tv_nsec += 1;
		int s = sem_timedwait(sem, &tm); //sem_wait(sem);
		if (s != 0 && errno == ETIMEDOUT)
		{
			cout << "TIME OUT ACCURED FOR : " << i << flush;
		}
		*/
		/*
		int s = sem_wait(sem);
		
		if (s != 0)
		{
			cout << "\nSemaphore error : " << flush;
		}
		*/

		fstream myfile;
		myfile.open ("example.txt", std::ios_base::app);
		myfile << "Writing this to a file: " << i << " \n";
		myfile.close();
		i++;
		ts.tv_sec = 2;
		ts.tv_nsec = 10000;
		nanosleep(&ts, NULL);

		//sem_post(sem);
		
		ts.tv_sec = 0;
		ts.tv_nsec = 10000;
		nanosleep(&ts, NULL);
		
	}

	sem_close(sem);
	cout << "\n I ENDED WRITING : " <<  flush;
	return 0;
}
