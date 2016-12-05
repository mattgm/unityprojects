#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/* (code below)
COMBINE1:

No optimization: 
	1k time: .000001
	1k CPE: 1 * 10^(-8)
	2k time: .000002
	2k CPE: 1 * 10^(-8)

-g optimization:
	1k time: .000001
	1k CPE: 1 * 10^(-8)
	2k time: .000002
	2k CPE: 1 * 10^(-8)

-O2 optimization:
	1k time: .000001
	1k CPE: 1 * 10^(-8)
	2k time: .000002
	2k CPE: 1 * 10^(-8)

COMBINE2:
No optimization: 
	1k time: .000001
	1k CPE: 1 * 10^(-8)
	2k time: .000002
	2k CPE: 1 * 10^(-8)

-g optimization:
	1k time: .000001
	1k CPE: 1 * 10^(-8)
	2k time: .000002
	2k CPE: 1 * 10^(-8)

-O2 optimization:
	1k time: .000001
	1k CPE: 1 * 10^(-8)
	2k time: .000002
	2k CPE: 1 * 10^(-8)

COMBINE3:
No optimization: 
	1k time: .000001
	1k CPE: 1 * 10^(-8)
	2k time: .000002
	2k CPE: 1 * 10^(-8)
	
-g optimization:
	1k time: .000001
	1k CPE: 1 * 10^(-8)
	2k time: .000002
	2k CPE: 1 * 10^(-8)

-O2 optimization:
	1k time: .000001
	1k CPE: 1 * 10^(-8)
	2k time: .000002
	2k CPE: 1 * 10^(-8)

TABLE:

Method 			Integer 	Floating Point
abstract -g     42.06, 41.86	41.44, 160.0
abstract -O2	31.25, 33.25	32.25, 143.0 
move vec length 20.66, 21.25	21.15, 135.00
data access 	6.00, 9.00		8.00, 117.00
accum in temp	2.00, 4.00		3.00, 5.00
*/


typedef struct {
	int len;
	int *data;
} vec_rec, *vec_ptr;

vec_ptr new_vec(int len){
	vec_ptr result = (vec_ptr) malloc(sizeof(vec_rec));
	if (!result) return NULL;

	if (len > 0) {
		int *data = (int *)calloc(len, sizeof(int));
		if (!data) {
			free ((void *)result);
			return NULL;
		}
		result->data = data;
	} else {
		result->data = NULL;
	}
	return result;
}

int get_vec_element(vec_ptr v, int i, int *dest) {
	if (i < 0 || i >= v->len) {
		return 0;
	}
	*dest = v->data[i];
	return 1;
}

int *get_vec_start(vec_ptr v) {
	return v->data;
}

int vec_length(vec_ptr v) {
	return v->len;
}

void combine1( vec_ptr v, int *dest ) {
	int i; 
	*dest = 0;
	for( i=0; i<vec_length(v); i++){ 
		int val ;
		get_vec_element( v, i , &val ); 
		*dest += val;
	}
}

void combine2(vec_ptr v, int *dest) {
	int i;
	int length = vec_length(v);
	int *data = get_vec_start(v);
	*dest = 0;
	for (i = 0; i < length; i++) {
		*dest += data[i];
	}
}

void combine3(vec_ptr v, int *dest)
{
  int i;
  int length = vec_length(v);
  int *data = get_vec_start(v);
  *dest = 0;
  for (i = 0; i < length; i++) {
    *dest += data[i];
}
}

void abstract_combine3( vec_ptr v, data_t *dest){
	int i;
	int length = vec_length(v);
	data_t *data = get_vec_start(v);
	data t = IDENT;
	for (i = 0; i < length; i++) {
		t = t OP data[i];
	}
	*dest = t;
}


int main() {

	clock_t begin, end;
	double time_spent;

	vec_ptr v1k = new_vec(1000);
	for (int i = 0; i < 1000; i++) {
		v1k->data[i] = i;
	}
	vec_ptr v2k = new_vec(2000);
	for (int i = 0; i < 2000; i++) {
		v2k->data[i] = i;
	}

	int sum = 0;
	begin = clock();
	combine2(v1k, &sum);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	
	printf("%f\n", time_spent);

}
