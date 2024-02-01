# Computational-Physics
Repository for the projects of the 2023-24 course of Computational Physics. (<b>LAST UPDATE: 1/02/2024</b>)<br> 
A general directory with some graphs and other visual results will soon be added to the page. <br><br>
<b>DISCLAIMER</b>: Here a brief description of each exercise follows, along with <b>some</b> of the problems and anlyses which were done during the course. The code is mostly filled with English names for the variables and functions, however sometimes the comments and debug lines are written in Italian, as it was the main language of the course. This repository serves as a general presentation of the content of the course.
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
$\int_{x_1}^{x_N} f(x)dx = h[\frac{1}{2}f(x_1)+f(x_2)+...+f(x_{N-1})+\frac{1}{2}f(x_N)] + \mathcal{O}(\frac{1}{N^2})$<br><br>
$\int_{x_1}^{x_N} f(x)dx = \frac{h}{3}[f(x_1)+4f(x_2)+2f(x_3)+...+2f(x_{N-2})+4f(x_{N-1})+f(x_N)] + \mathcal{O}(\frac{1}{N^4})$<br><br>
where $h$ represents the width of each interval into which the original integration interval is divided<br>
### Romberg method
$R(J,K)=\frac{4^KR(J,K-1)-R(J-1,K-1)}{4^K-1}$<br><br>
where $J$ is a parameter linked to the number of points used for the integration and $K$ is a parameter linked to the precision of the method. Increasing the former corresponds to an increase in the number of points, while the latter increases the order in $h$ with which the formula differs from the analytical result.
### Gaussian quadratures
$I=\int_a^bf(x)W(x)dx\simeq\displaystyle\sum_{i=1}^nf(x_i)w_i$<br><br>
where $W(x)$ is the weight function of a particular set of orthogonal polynomials which needs to appear explicitly in the integral for the formula to work.
In the exercises different sets of polynomials are used:
#### Legendre Polynomials
Weight $W(x)=1$, Integration range: $(-1,1)$.<br>
The only challenge is to shift the original interval $(a,b)$ to $(-1,1)$ but this can be easily done with the transformation: <br><br>
$x \mapsto \frac{b-a}{2}x+\frac{b+a}{2}$<br><br>
#### Laguerre Polynomials
Weight $W(x)=e^{-x}$, Integration range: $(0,\infty)$.<br>
Here one may transform the integral through:<br><br>
$I=\int_a^bf(x)dx=\int_a^{\infty}f(x)dx-\int_b^{\infty}f(x)dx=\int_0^{\infty}[f(x+a)-f(x+b)]e^xe^{-x}dx$<br><br>
But the first step may not be well-posed as the integrals may diverge and the method may not be stable numerically. This is the case of the function $f(x)=cosh(x)$ for which one has to resort to its definition as sum of real exponentials to transform the integral in a form which is acceptable for the use of these polynomials.
#### Hermite Polynomials
Weight $W(x)=e^{-x^2}$, Integration range: $(-\infty,\infty)$.<br>
## EXERCISE 8: calculation of the volume of an M-sphere with the midpoint rule in M dimensions and with Monte Carlo integration.
In this exercise two different integration techinques are used to calculate the volume of an M-sphere: the midpoint rule and Monte Carlo integration. The function which defines the M-sphere is the following <br><br>
$f(x_1,x_2,...,x_{M-1})=\sqrt{1 - x_1^2 - x_2^2 - ... - x_{M-1}^2}$  if  $x_1^2 + x_2^2 + ... + x_{M-1}^2 \leq 1$
<br><br>
and takes the value $0$ elsewhere. This is just a trick to avoid evaluating nested integrals which are complicated to treat, especially in high number of dimensions.
### Midpoint rule
The midpoint rule consists in the approximation of an integral by constructing an evenly spaced grid in M-dimensions and by evaluating the function in the points which are "in the middle" of a space of the grid and then by summing up all those values. As an example, in one dimension this corresponds to divide an interval $\[x_0,x_n\]$ in different subintervals $[x_0,x_1)$ $U$ $[x_1,x_2)$ $U ... U$ $[x_{n.1},x_n]$ and to evaluate the function in the midpoint $\tilde{x_i} = \frac{x_{i-1} + x_{i}}{2}$ of each interval. The integral is then:<br><br>
   $I=\int_a^b f(x)dx=h\displaystyle\sum_{i=1} ^{N} f(\tilde{x_i})$
<br><br>
In an arbitrary number $M$ of dimensions the process is repeated for every coordinate.
### Monte Carlo integration
The idea beind this method is rather simple. A certain number of points $N$ is generated in the domain of the function, and the integral is approximated as: <br><br>
$\int f dV \simeq V(\langle f \rangle \pm \Delta f)$
<br><br>
where $\langle f\rangle$ denotes the mean value of the function f.
<br>
### Computing time
In general, it is expected that the computing time of the midpoint method will increase exponentially as the number $M$ of dimensions grows. This is due to the fact that if we choose to use 10 points per dimension to contruct the grid, this will result in having to evaluate the function in $10^M$ different points. Moreover additional computing time is required to cycle through all the possible permutations of the coordinates to use the whole grid.<br>

On the other hand the Monte Carlo method is highly more efficient in higher dimensions, but it needs to increase the number of points used to keep up with the precision, which would otherwise decrease if the number of points was fixed.
## EXERCISE 9: analysis of the central limit theorem with a discrete distribution and with a uniform distribution.
The focus of this exercise is the generation of random numbers. More precisely it is aimed at studying the behaviour of random variables constructed as: <br><br>
$x_i=\frac{1}{N}\displaystyle \sum_{n=1}^{N}r_n$
<br><br>
Where the $r_n$'s are random numbers generated with the same distribution. One distribution is the discrete distribution, which gives the same probability of extracting $-1$ or $+1$:<br><br>
$f_{\text{coin}}(x) = \frac{1}{2}\delta(x-1) + \frac{1}{2}\delta(x+1)$
<br><br>
While the other is the uniform distribution in the interval $(-1,+1)$:<br><br>
$f_{\text{unif}}(x)=\frac{1}{2}$
<br><br>
It is expected that the random variables constructed starting from these distributions will exhibit a behaviour that resembles the one of a Gaussian distribution, as predicted by the central limit theorem.
## EXERCISE 10: Monte Carlo integration and hit or miss method.
The hit or miss method consists in the approximation of the integral through the random generation of points $(x_i,y_i)$ in the rectangle $[a,b]\times[0,y_{\text{max}}]$ that encolses the graph of the function in the interval $[a,b]$, where $y_{\text{max}}$ is the maximum value of the function in that domain. The following formula describes the approximation<br><br>
$I\simeq I_{\text{HM}} = y_{\text{max}}(b-a)\frac{N_{\textit{hit}}}{N_{\textit{tot}}}$
<br><br>
Here the term $\frac{N_{\textit{hit}}}{N_{\textit{tot}}}$ represents the fraction of points for which the following condition is satisfied $y_i$ $<$ $f(x_i)$.<br>
On the other hand the Monte Carlo method is implemented as described in <b>exercise 8</b>, just for the one dimensional case.
## EXERCISE 11: Random number generation: inverse transfom sampling
The implementation of the inverse transform method is rather simple, as we want to use some function to generate a distribution of random numbers. Here we study the following functions:<br><br>
1. $f(x)=e^{-x}, x\in(0,2)$
2. $g(x)=e^{-x}, x\in(1,\infty)$
3. $h(x)=xe^{-x^2}, x\in(0,\infty)$
<br><br>

For each of these we will need to calculate their <b>cumulative distribution function (CDF)</b> y=F(x) and by inverting this function (which needs to be normalized) and using random numbers $y_i$ generated in $(0,1)$ we can extract the respective $x_i$ values.<br>
The only problem of this method arises when the analytical form of a CDF is not known. In those cases we have to resort to other methods, as described in <b>exercise 12</b>
## EXERCISE 12: Gaussian distributed random numbers: exact method VS rejection sampling
Gaussian numbers can be generated "exactly" by the following method:
1. Generate a random number $z\in(0,1)$, and $\alpha\in(0,1)$
2. Calculate $r=\sqrt{-ln(1-z)}$
3. Calculate $x=r cos(2\pi\alpha)$. $x$ will then have a gaussian distribution with mean equal to zero and a width of $\frac{1}{2}$.

Another way of generating gaussian distributed numbers is through **rejection sampling**. <br>
If we wish our numbers to follow $f(x)=\frac{1}{\sqrt{\pi}}e^{-x^2}$:
1. We need a test distribution $g(x)$ such that $g(x)\geq f(x)$, $\forall x$.
2. Then we need to sample this distribution at a point $\tilde{x}$ in its domain and thereafter we sample a number $\tilde{y}$ with a uniform distribution in $(0,g(\tilde{x}))$.
3. If $\tilde{y}\geq f(\tilde{x})$, then the sampled value $\tilde{x}$ is rejected, otherwise it is accepted.

The main challenge in this method is to find a proper test distribution, which in theory should be as similar as possible as the desired one, in order to reduce the number of rejections.
## EXERCISE 13: Stochastic integration: Monte Carlo sampling VS importance sampling
## EXERCISES 14-15-16-17-18: differential equations: Euler VS Runge-Kutta methods
