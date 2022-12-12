#include <math.h>
#include <stdio.h>
#include <time.h>

/**
 * Requesting user to type a number and
 * reading input from command line 
 * 
 * @param n The reading from command line input
 * 
*/

unsigned long get_input () {
  unsigned long n = 0;
  printf("Enter any positive integer: ");
  scanf("%ld", &n);
  return n;
}

/**
 * Recursively testing if our number {N} is odd
 * if it is not odd, the recursion continues.
 * The function will divide our number {N} by two 
 * and print a 2 to our output of prime factors.
 * 
 * After the recursion is done, N will always be odd.
 * 
 * @param N pointer to our number
 * 
*/

void check_odd (unsigned long *N) {
  if(!(*N & 1)){
    printf ("2 ");
    *N = *N >> 1;
    check_odd(N);
  }
}

/**
 * Recursively factoring our number N with Fermat's
 * factorization method until all prime factors are found.
 * 
 * Also includes a filter for numbers that have module 16 
 * congruence of 0,1,4 or 9 
 * only those can have an integer square root
 * binary and (&) is used because it is more performant than modulo
 * 
 * @param N odd number for that we want to find prime factors
 * @param a fermats starting value (square root of N rounded up)
 * @param b2 value that we test if it is b*b
 * @param b square root of b2 casted as integer, if the square
 *          root is not an integer, all decimals are dropped. 
 * 
*/

void factor_rec (unsigned long N) {
  unsigned long b, b2, a = ceil(sqrt(N));
  while(1){
    b2 = a*a-N;
    switch((int)(b2 & 0xF)){
    case 0: case 1: case 4: case 9:
      b = (unsigned long)sqrt(b2);
      if(b*b == b2) goto out;
    default:
      a++;
    }
  }

out:
  if(a-b == 1) printf ("%lu ", a+b);
  else{
    factor_rec(a-b);
    factor_rec(a+b);
  }
}

/**
 * Main function that runs a loop and calls all
 * other functions to do the prime factorization
 * 
 * @param t cpu clock timer to calculate the time it takes
 *          to factor a number
 * @param N our number, for that we search prime factors
 * 
*/

int main() {
  clock_t t;
  unsigned long N;

  while(1){
    N = get_input();
    printf ("Found following prime factors: ");
    t = clock();

    check_odd(&N);
    factor_rec(N);

    printf ("\nThe Factorization took %f seconds\n", ((double)clock()-t)/CLOCKS_PER_SEC);
    t = clock();
  }
  return 0;
}