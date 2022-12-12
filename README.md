# Small implementation of Fermat's factorization method in c

To compile use e.g. gcc and don't forget to link the math.h library.
E.g. use ``gcc fermat.c -lm -o fermat``
Then you can just execute the program ``./fermat``

fermat.c features the basic factorization method to find two factors for any
given input number N. It also has an improved version with an added sieve.

fermat_extended.c has additional functionality that uses Fermat's 
factorization method to recursively factorize any given number into all 
of it's prime factors.
