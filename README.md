# Computational-Physics
Repository for the projects of the 2023-24 course of Computational Physics. <br> 
<b>DISCLAIMER</b>: Here a brief description of each exercise follows. The code is mostly filled with English names for the variables and functions, however sometimes the comments and debug lines are written in Italian, as it was the main language of the course.
## EXERCISE 1: analysis of roundoff and truncation errors in floating-point numbers
This first exercise focuses on the calculation of the sum $\displaystyle\sum_{n=1} ^{N} \frac{1}{n^2}$. To calcute this sum one can follow two different approaches:
1. Starting to calculate the term with $n=1$ by initializing a variable to $1$ and then adding all the others till $\frac{1}{N}$
2. Starting to calculate the term with $n=N$ by initializing a variable to $\frac{1}{N}$ and then adding all the others till $1$

The first approach will encounter problems depending on the chosen data type, because all the terms after the first will need to be adapted to its precision, thus when the difference between 1 and $\frac{1}{N}$ will become smaller than $2^{-M}$ (where M is the number of bits used to represent the mantissa of the number) the code will add zero instead. It is expected that from this point on the second method will produce better results.
## EXERCISE 2: propagation of roundoff and truncation errors in recurrence relations
This exercise focuses on the recurrence relation $\phi^{n+1}=\phi^{n-1}-\phi^n$, which is solved by the two values $\phi_1=\frac{\sqrt{5}-1}{2}$ and $\phi_2=-\frac{\sqrt{5}+1}{2}$. By setting  $\chi_0=1$ and $\chi_1=\phi_1=\frac{\sqrt{5}-1}{2}$ and studying it as $\chi_n=\chi_{n-2}-\chi_{n-1}$ one major proble arises. <br>
As a matter of a fact $\chi_1$ is irrational, so it won't be represented exactely in memory, but rether with an approximation $\bar{\chi_1}$. Due to the fact that this is not a fundamental solution of the relation it will be represented as a linear combination of the solutions, namely $\bar{\chi_1}=\phi_1+\epsilon\phi_2$. <br>
The n-th value of the relation will thus be: $\chi_n=\phi_1^n+\epsilon\phi_2^n$ <br>
The problem lies in the fact that $|\phi_2|>1$ and $|\phi_1|<1$, thus when the two addends in $\chi_n$ will be in the same order of magnitude its value will start to noticeably deviate from the expected value of $\phi_1^n$.
## EXERCISES 3-4-5-6-7: deterministic integration with Simpson rule, Trapezoidal rule, Romberg method and gaussian quadratures.
## EXERCISE 8: calculation of the volume of an M-sphere with the midpoint rule in M dimensions and with Monte Carlo integration.
## EXERCISE 9: analysis with central limit theorem with a discrete distribution and with a uniform distribution.
## EXERCISE 10: Monte Carlo integration and importance sampling.
