[a]=readvars("cdf2.dat");
figure;
hold on;
h=histogram(a,100,'Normalization','pdf');
set(0,'defaultTextInterpreter','latex');
xlabel("$x$")
ylabel("Conteggi")
func = @(x) exp(1-x)
plot_func('x','',true,func,[1 10 0 .7]);
legend("Dati funzione inversa","g(x)");
hold off;