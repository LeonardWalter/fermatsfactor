#include <math.h>
#include <stdio.h>
#include <time.h>

/**
 * @param t cpu clock timer to calculate the time it takes
 *          to factor a number
*/

clock_t t;

/**
 * Function that is requesting the user to type an odd 
 * number and reading input from command line 
 * 
 * @param n The reading from command line input
 * @returns {n}
*/

unsigned long get_input () {
  unsigned long n = 0;
  while(!n){
    printf("Enter an odd integer: ");
    scanf("%ld", &n);
    if(!(n&1)){
      printf("%lu is not odd you fool\n", n);
      n = 0;
    }
  }
  t = clock();
  return n;
}

/**
 * Function that prints the resulting factors and the time it
 * took to compute them.
 * 
 * @param f1 factor 1
 * @param f2 factor 2
*/

void prt_result (unsigned long f1, unsigned long f2) {
  if(f2 == 1)
    printf ("%lu is a prime number\n", f1);
  else
    printf ("Found factors: %lu, %lu.\n", f1, f2);
  printf ("Factorization took %f seconds\n", 
          ((double)clock()-t)/CLOCKS_PER_SEC);
  t = clock();
}

/**
 * Simplest form of fermats factorization method
 * 
 * @param N odd number for that we want to find factors
 * @param a fermats starting value (square root of N rounded up)
 * @param b2 value that we test if it is b*b
 * @param b square root of b2 casted as integer, if the square
 *          root is not an integer, all decimals are dropped.
 * 
 * If an even square is found, we got a pair of factors and call
 * the prt_result function.
 * 
*/


void factor (unsigned long N) {
  unsigned long b, b2, a = ceil(sqrt(N));
  while(1){
    b2 = a*a-N;
    b = (unsigned long)sqrt(b2);
    if(b*b == b2) break;
    a++;
  }
  prt_result(a+b, a-b);
}

/**
 * Fermats factorization method with modulo 16 sieve for
 * faster computation.
 * 
 * Basically the same as factor() function but with some added 
 * functionality to reduce unneccessary sqrt() computations.
 * 
 * A filter for numbers that have module 16 congruence of 
 * 0,1,4 or 9 was added. Only these numbers can have an integer 
 * as square root.
 * 
 * binary and (&) is used because it is more performant than modulo
 */


void factor_sieve (unsigned long N) {
  unsigned long b, b2, a = ceil(sqrt(N));
  while(1){
    b2 = a*a-N;
    switch((int)(b2 & 0xF)){
    case 0: case 1: case 4: case 9:
      b = (unsigned long)sqrt(b2);
      if(b*b == b2){
        prt_result(a+b, a-b);
        return;
      }
    default:
      a++;
    }
  }
}

/**
 * Main function that runs a loop and calls all
 * other functions to do both of the factorization functions 
 * so they can be compared
 * 
 * @param t cpu clock timer to calculate the time it takes
 *          to factor a number
 * @param N our number, for that we search prime factors
 * 
*/

int main() {
  while(1){
    unsigned long N = get_input();
    factor(N);
    factor_sieve(N);
  }
  return 0;
}


/**
 * Complexity of the algorithm:
 * 
 * Ideally, Fermats factorization will at most take N/2 - sqrt(N) steps if our number
 * N is a prime. So complexity is O(N)
 * The sieve can get rid of some more unneccessary computations, decresing 
 * complexity closer to the range of N/8 - sqrt(N), but for big O notation
 * complexity is still O(N)
 *
 * In reality, we have to consider this algorithm as pseudo polynomial. Since simple 
 * computations become more complex with a growing input number N. I.e. it is more
 * complex to add two 10 digit numbers than adding two 5 digit numbers.
*/
