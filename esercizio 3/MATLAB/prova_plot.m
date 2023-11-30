[asc,ord] = readvars('trapezio.dat');
figure;
hold on;
scatter(asc,ord,'*');
[asc,ord] = readvars('simpson.dat');
scatter(asc,ord,'*');
set(0,'defaultTextInterpreter','latex');
xlabel('$\frac{1}{N}$');
ylabel('$\Delta$');
legend('Trapezio','Simpson','Location','Northwest');
hold off;

figure;
hold on;
[asc,ord,times] = readvars('trapezio.dat');
scatter(arrayfun(@(x) 1/x,asc),times,'*');
[asc,ord,times] = readvars('simpson.dat');
scatter(arrayfun(@(x) 1/x,asc),times,'*');
set(0,'defaultTextInterpreter','latex');
xlabel('$\frac{1}{N}$');
ylabel('Tempo di calcolo');
legend('Trapezio','Simpson','Location','Northwest');
hold off;