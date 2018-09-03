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


string GotoLine(unsigned int num)
{
	fstream file ("example.txt");
	file.seekg(std::ios::beg);
	string line;
	int number_of_lines = 0;

	while (std::getline(file, line))
	{
		++number_of_lines;
		if (num == number_of_lines)
		{
			file.close();
			return line;
		}
	}
	
	file.close();
	return "ERROR!!!";
}


int main(int argc, char* argv[])
{
	sem_t *sem;
	random_device rd;
	mt19937 rng(rd());
	uniform_int_distribution<int> uni_big(0, 100000);
	uniform_int_distribution<int> uni_small(0, 200);
	int number_of_lines = 0;

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
			cout << "ERROR on semaphore " << flush;
		}
		*/

		int num = uni_small(rng);
		string k = GotoLine(num);
		cout << "\n------------>  " << k << "@ " << num <<flush;
	//	sem_post(sem);
		i++;
		/*
		   ts.tv_sec = uni_small(rng);
		   ts.tv_nsec = uni_big(rng);
		   nanosleep(&ts, NULL);
		   */
	}

	sem_close(sem);
	return 0;
}
