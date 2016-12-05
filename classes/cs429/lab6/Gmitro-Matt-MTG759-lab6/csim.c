/* Matt Gmitro - MTG759 */

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <math.h>
#include <getopt.h>
#include <unistd.h>

#include "cachelab.h"

typedef unsigned long long int address_t;

typedef struct {
	int s;
	int b;
	int E;
	int S;
	int B;
	int hit;
	int miss;
	int evict;
} parameters_t;

typedef struct {
	int previous;
	int valid;
	address_t tag;
	char *block;
} line;

typedef struct {
	line *lines;
} set;

typedef struct {
	set *sets;
} cache;

int verb;

long long bitp(int e) {
	long long ans = 1;
	ans = ans << e;
	return ans;
}

void printUX(char * argv[]) {
	printf("Use: %s [-hv] -s <num> -E <num> -b <num> -t <file>n", argv[0]);
	printf("Options:\n");
	printf("-h 			Help flag\n");
	printf("-v 			Verbose flag\n");
	printf("-s <num> 	Set index bits\n");
	printf("-E <num>	Lines per set\n");
	printf("-b <num> 	Block offset bits\n");
	printf("-t <file>	Trace file\n");
	printf("\n EXAMPLES:\n");
	printf("%s -s 4 -E 1 -b 4 -t traces/yi.trace\n", argv[0]);
    printf("%s -v -s 8 -E 2 -b 4 -t traces/yi.trace\n", argv[0]);
    exit(0);
}

cache buildCache(long long S, int E, long long B) {
	cache c1;
	set st;
	line ln;
	int setIdx;
	int lineIdx;

	c1.sets = (set *) malloc(sizeof(set) * S);

	for (setIdx = 0; setIdx < S; setIdx++) {
		st.lines = (line *) malloc(sizeof(line) * E);
		c1.sets[setIdx] = st;

		for (lineIdx = 0; lineIdx < E; lineIdx++) {
			ln.previous = 0;
			ln.valid = 0;
			ln.tag = 0;
			st.lines[lineIdx] = ln;
		}
	}

	return c1;
}

void clearCache(cache sim, long long S, int E, long long B) {
	int i;

	for (i = 0; i < S; i++) {
		set st = sim.sets[i];

		if (st.lines != NULL) {
			free(st.lines);
		}
	}
	if (sim.sets != NULL) {
		free(sim.sets);
	}
}

int getEmptyLine(set q, parameters_t p) {
	int E = p.E;
	int i;
	line ln;

	for (i = 0; i < E; i++) {
		ln = q.lines[i];
		if (ln.valid == 0) {
			return i;
		}
	}
	return -1;
}

int getEvictLine(set q, parameters_t par, int *used) {
	int E = par.E;
	int max = q.lines[0].previous;
	int min = q.lines[0].previous;
	int minIdx = 0;

	line ln;
	int i;

	for (i = 0; i < E; i++) {
		ln = q.lines[i];

		if (min > ln.previous) {
			minIdx = i;
			min = ln.previous;
		}

		if (max < ln.previous) {
			max = ln.previous;
		}
	}

	used[0] = min;
	used[1] = max;
	return minIdx;
}

parameters_t simulate(cache sim, parameters_t p, address_t address) {
	int i;
	int full = 1;
	int E = p.E;
	int last_hits = p.hit;
	int tsize = (64 - (p.s + p.b));
	address_t input = address >> (p.b + p.s);
	unsigned long long tmp = address << (tsize);
	unsigned long long setIdx = tmp >> (tsize + p.b);

	set q = sim.sets[setIdx];

	for (i = 0; i < E; i++) {
		line ln = q.lines[i];

		if (ln.valid) {
			if (ln.tag == input) {
				ln.previous++;
				p.hit++;
				q.lines[i] = ln;
			}
		} else if (full && !ln.valid) {
			full = 0;
		}
	}

	if (last_hits == p.hit) {
		p.miss++;
	} else {
		return p;
	}

	int *used = (int*) malloc(sizeof(int) * 2);
	int minIdx = getEvictLine(q, p, used);

	if (full) {
		p.evict++;
		q.lines[minIdx].tag = input;
		q.lines[minIdx].previous = used[1] + 1;
	} else {
		int emptyIdx = getEmptyLine(q, p);
		q.lines[emptyIdx].tag = input;
		q.lines[emptyIdx].valid = 1;
		q.lines[emptyIdx].previous = used[1] + 1;
	}

	free(used);
	return p;
}

int main(int argc, char **argv)
{
	cache sim;
	parameters_t p;
	bzero(&p, sizeof(p));
	long long B;
	long long S;
	char itrace;
	FILE *rtrace;
	address_t address;
	int size;

	char *filename;
	char x;

	while ((x=getopt(argc,argv,"s:E:b:t:vh")) != -1) {
		switch(x) {
			case 's':
				p.s = atoi(optarg);
				break;
			case 'E':
				p.E = atoi(optarg);
				break;
			case 'b':
				p.b = atoi(optarg);
				break;
			case 't':
				filename = optarg;
				break;
			case 'v':
				verb = 1;
				break;
			case 'h':
				printUX(argv);
				exit(0);
			default:
				printUX(argv);
				exit(1);
		}
	}

	if (p.E == 0 || p.s == 0 || p.b == 0 || filename == NULL) {
		printf("%s: Missing arg!\n", argv[0]);
		printUX(argv);
		exit(1);
	}

	S = pow(2.0, p.s);
	B = bitp(p.b);
	p.hit = 0;
	p.miss = 0;
	p.evict = 0;

	sim = buildCache(S, p.E, B);
	rtrace = fopen(filename, "r");

	if (rtrace != NULL) {
		while (fscanf(rtrace, " %c %llx,%d", &itrace, &address, &size) == 3) {
			switch(itrace) {
				case 'I':
					break;
				case 'L':
					p = simulate(sim, p, address);
					break;
				case 'S':
					p = simulate(sim, p, address);
					break;
				case 'M':
					p = simulate(sim, p, address);
					p = simulate(sim, p, address);
					break;
				default:
					break;
			}
		}
	}

    printSummary(p.hit, p.miss, p.evict);
    clearCache(sim, S, p.E, B);
    fclose(rtrace);
    return 0;
}
