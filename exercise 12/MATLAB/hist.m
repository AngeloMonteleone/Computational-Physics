[a]=readvars("gaussAR.dat");
figure;
hold on;
h=histogram(a,100,'Normalization','pdf');
set(0,'defaultTextInterpreter','latex');
xlabel("$x$")
ylabel("Conteggi")
func = @(x) (exp(-x*x))/(sqrt(pi))
plot_func('x','',true,func,[-4 4 0 .7]);
legend("Dati A&R","g(x)");
hold off;