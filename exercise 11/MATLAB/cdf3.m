[a]=readvars("cdf3.dat");
figure;
hold on;
h=histogram(a,100,'Normalization','pdf');
set(0,'defaultTextInterpreter','latex');
xlabel("$x$")
ylabel("Conteggi")
func = @(x) 2*x*exp(-x*x)
plot_func('x','',true,func,[0 4 0 .7]);
legend("Dati funzione inversa","g(x)");
hold off;