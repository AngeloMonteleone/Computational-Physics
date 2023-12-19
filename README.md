# Computational-Physics
Repository for the projects of the 2023-24 course of Computational Physics. <br> 
<b>DISCLAIMER</b>: Here a brief description of each exercise follows, along with <b>some</b> of the problems and anlyses which were done during the course. The code is mostly filled with English names for the variables and functions, however sometimes the comments and debug lines are written in Italian, as it was the main language of the course.
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
The integrals analyzed in these exercises are the following<br>
1. $I_3=\int_0^5 x^7e^{-x}dx$
2. $I_4=\int_3^8cosh(x)dx$
3. $I_5=\int_{-1}^8(x^2+xsin(4x))dx$
4. $I_6=\int_3^{\infty}x^5e^{-x^2}dx$
5. $I_7=\int_0^{\infty}x^{14}e^{-x^2}dx$
### Trapezoidal and Simson rule
$\int_{x_1}^{x_N} f(x)dx = h[\frac{1}{2}f(x_1)+f(x_2)+...+f(x_{N-1})+\frac{1}{2}f(x_N)] + \mathcal{O}(\frac{1}{N^2})$<br>
$\int_{x_1}^{x_N} f(x)dx = \frac{h}{3}[f(x_1)+4f(x_2)+2f(x_3)+...+2f(x_{N-2})+4f(x_{N-1})+f(x_N)] + \mathcal{O}(\frac{1}{N^4})$<br>
where $h$ represents the width of each interval into which the original integration interval is divided<br>
### Romberg method
$R(J,K)=\frac{4^KR(J,K-1)-R(J-1,K-1)}{4^K-1}$<br>
where $J$ is a parameter linked to the number of points used for the integration and $K$ is a parameter linked to the precision of the method. Increasing the former corresponds to an increase in the number of points, while the latter increases the order in $h$ with which the formula differs from the analytical result.
### Gaussian quadratures
$I=\int_a^bf(x)W(x)dx\simeq\displaystyle\sum_{i=1}^nf(x_i)w_i$<br>
where $W(x)$ is the weight function of a particular set of orthogonal polynomials which needs to appear explicitly in the integral for the formula to work.
In the exercises different sets of polynomials are used:
#### Legendre Polynomials
Weight $W(x)=1$, Integration range: $(-1,1)$.<br>
The only challenge is to shift the original interval $(a,b)$ to $(-1,1)$ but this can be easily done with the transformation: <br>
$x \mapsto \frac{b-a}{2}x+\frac{b+a}{2}$<br>
#### Laguerre Polynomials
Weight $W(x)=e^{-x}$, Integration range: $(0,\infty)$.<br>
Here one may transform the integral through:<br>
$I=\int_a^bf(x)dx=\int_a^{\infty}f(x)dx-\int_b^{\infty}f(x)dx=\int_0^{\infty}[f(x+a)-f(x+b)]e^xe^{-x}dx$<br>
But the first step may not be well-posed as the integrals may diverge and the method may not be stable numerically. This is the case of the function $f(x)=cosh(x)$ for which one has to resort to its definition as sum of real exponentials to transform the integral in a form which is acceptable for the use of these polynomials.
#### Hermite Polynomials
Weight $W(x)=e^{-x^2}$, Integration range: $(-\infty,\infty)$.<br>
## EXERCISE 8: calculation of the volume of an M-sphere with the midpoint rule in M dimensions and with Monte Carlo integration.
## EXERCISE 9: analysis with central limit theorem with a discrete distribution and with a uniform distribution.
## EXERCISE 10: Monte Carlo integration and importance sampling.
