# Computational-Physics
Repository for the projects of the 2023-24 course of Computational Physics
## Exercise 1: analysis of roundoff and truncation errors in floating-point numbers
This first exercise focuses on the calculation of the sum $\displaystyle\sum_{n=1} ^{N} \frac{1}{n^2}$. To calcute this sum one can follow two different approaches:
1. Starting to calculate the term with $n=1$ by initializing a variable to $1$ and then adding all the others till $\frac{1}{N}$
2. Starting to calculate the term with $n=N$ by initializing a variable to $\frac{1}{N}$ and then adding all the others till $1$

The first approach will encounter problems depending on the chosen data type, because all the terms after the first will need to be adapted to its precision, thus when the difference between 1 and $\frac{1}{N}$ will become smaller than $2^{-M}$ (where M is the number of bits used to represent the mantissa of the number) the code will add zero instead. It is expected that from this point on the second method will produce better results.
## Exercise 2: propagation of roundoff and truncation errors in recurrence relations
## Exercises 3-4-5-6-7: deterministic integration with Simpson rule, Trapezoidal rule, Romberg method and gaussian quadratures.
## Exercise 8: calculation of the volume of an M-sphere with the midpoint rule in M dimensions and with Monte Carlo integration.
## Exercise 9: analysis with central limit theorem with a discrete distribution and with a uniform distribution.
## Exercise 10: Monte Carlo integration and importance sampling.
