/*Discussion Section Problem Set #: 2
Student Name: Matt Gmitro
EID: mtg759
CS login: mattgm	
Email address: mattgmitro@utexas.edu
Unique Number: 51475

1.1 
a) 90
b) grep -c "74" nums.txt

1.2
a) 91
b) grep -c "12" nums.txt

1.3
a) 95
b) grep -c "^14" nums.txt

2.
skipper$ time ls
c1.txt	Desktop    Downloads  lab4  lab6   Pictures  public_html  Videos
c3.txt	Documents  Lab2       lab5  Music  Public    Templates

real	0m0.053s //real time between invocation and termination
user	0m0.000s //user CPU time
sys		0m0.001s //system CPU time

Output is as I would expect because it's a small directory with an extremely simple command

3.*/
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int sum(int x, int y){
	return x + y;
}

int main(){
	struct timeval *proc;
	struct timeval *sys;
	struct timezone *tz;

	gettimeofday(proc, tz);
	suseconds_t start = proc->tv_usec;
	sum(5, 7);
	gettimeofday(proc, tz);
	suseconds_t end = proc->tv_usec;

	gettimeofday(sys, tz);
	suseconds_t start2 = proc->tv_usec;
	getuid();
	gettimeofday(sys, tz);
	suseconds_t end2 = proc->tv_usec;

	end = end - start;
	end2 = end2 - start2;
	printf(".%d\n .%d\n", end, end2);
}

/*
4. System call, interrupt, exceptions

5. 3 copies of c with values 6, 4, and 6
