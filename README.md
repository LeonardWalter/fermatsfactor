# Small implementation of Fermat's factorization method in c

To compile use e.g. gcc and don't forget to link the math.h library. <br>
E.g. use ``gcc fermat.c -lm -o fermat`` <br>
Then you can just execute the program ``./fermat`` <br>

fermat.c features the basic factorization method to find two factors for any <br>
given input number N. It also has an improved version with an added sieve. <br>

fermat_extended.c has additional functionality that uses Fermat's <br>
factorization method to recursively factorize any given number into all  <br>
of it's prime factors.
