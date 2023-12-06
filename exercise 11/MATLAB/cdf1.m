[a]=readvars("cdf1.dat");
figure;
hold on;
h=histogram(a,100,'Normalization','pdf');
set(0,'defaultTextInterpreter','latex');
xlabel("$x$")
ylabel("Conteggi")
func = @(x) exp(-x+2)/(exp(2)-1)
plot_func('x','',true,func,[0 2 0 .7]);
legend("Dati funzione inversa","g(x)");
hold off;