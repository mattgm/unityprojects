/* HW 4 CS429
   Matt Gmitro */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

unsigned decToHex(int x) {
  if (x == 0) return 0;
  if (x == 0x80000000) return 3472883712u;

  unsigned sign = x & 0x80000000;
  unsigned frac;
  unsigned expo = 150;
  unsigned over;
  unsigned under;

  if (sign) {
    frac = -x;
  } else {
    frac = x;
  }

  unsigned i = frac;
  unsigned change = 2;

  while (i & 0xFF000000) {
    i = (frac + (change / 2)) / change;
    expo++;
    change <<= 1;
  }

  while (i <= 0x007FFFFF) {
    i <<= 1;
    expo--;
  }

  if (0xFF000000 & frac) {
    change = 1 << (expo - 150);
    i = frac / change;
    under = frac % change;
    over = change - under;

    if ((over < under) || ((over == under) & i)) {
      i++;
    }

    frac = i;
  } else {
    while ( frac <= 0x007FFFFF) {
      frac <<= 1;
    }
  }
  
  return (sign) | (expo << 23) | (frac & 0x007FFFFF);

}

const char *decToBin(int x) {
	static char bin[9];
	bin[0] = '\0';

	int check = 128;
	for (check = 128; check > 0; check >>= 1) {
		strcat(bin, ((x & check) == check) ? "1" : "0");
	}

	return bin;
}

/* float floatToInt(unsigned uf) {
	unsigned frac = uf & 0x7FFFFF;
	unsigned expo = (uf >> 23) & 0xFF;
	unsigned  s = uf >> 31;

	unsigned expo = expo + 127

} */

void stringBytes(char *s) {
	while (*s != '\0') {
		int x = *s;
		printf("%s\n", decToBin(x));
		s++;
	}

	printf("%s\n", decToBin((int)*s));
}

int main() {
//1
	unsigned x = decToHex(-131);
	printf("%X\n", *(int *)&x);

//2
	//a
	int a2 = 0;
	unsigned i2a = 0x78;
	int count = 0;
	while (i2a) {
		if (i2a & 1) a2 += pow(2, count);
		i2a >>= 1;
		count++;
	}
	printf("%d\n", a2);

	//b
	//float i2b = 0x11.Ep0;
	float a2b = pow(2, 4) + 1 + (.875);
	printf("%f\n", a2b);

	//c
	float a2c = pow(2, 7) + pow(2, 5) + pow(2, 3) 
				+ pow(2, 2) + pow(2, -1) + pow (2, -3) + pow(2, -4);
	printf("%f\n", a2c);

	//d
	//int i2d = 145;
	printf("%X\n", 145);

	//e
	int a = 0x01234567;
	a = -a;
	printf("%X\n", a);

	//f
	int a2e = 0b01101001 - 0b01010101;
	printf("%s\n", decToBin(a2e));

	//g
	int a2g = (0x01234567 | 0x0F0F0F0F);
	printf("%X\n", a2g);

	//h
	int a2h = ~0x01234567;
	printf("%X\n", a2h);

	//i 
	int a2i = (0x66900000);
	printf("%X\n", a2i);

	//j
	int a2j = 0x01234567 ^ 0x0F0F0F0F;
	printf("%X\n", a2j);

//3
	printf("%f\n", -32.5);
//4 
	printf("Answer to #4 example:\n");
	stringBytes("hello world");


}