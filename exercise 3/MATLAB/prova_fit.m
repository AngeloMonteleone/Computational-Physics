%myfit('trapezio.dat', [0.2,.7,.2,.2], 'Modello', 'Southeast','$log(\frac{1}{N})$','$log(\Delta)$','red',[3 50],true,[2,6])
%myfit('simpson.dat', [0.2,.7,.2,.2], 'Modello', 'Southeast','$log(\frac{1}{N})$','$log(\Delta)$','red',[5 50],true,[4,6])
arr = [];
for k = 1:13
    arr(k)=(2^k-1)^-1;
end
arr = arr';
%display(arr);
[a,b,c] = readvars('romberg.dat');

%display(romberg_col)

fit_given_cols(arr,c,[0.2,.7,.2,.2], 'Modello', 'Southeast','$log(\frac{1}{N})$','$log(\Delta)$','red',[3 13],true,[6 6])
fit_given_cols(arr,b,[0.2,.7,.2,.2], 'Modello', 'Southeast','$log(\frac{1}{N})$','$log(\Delta)$','red',[2 13],true,[4 6])
fit_given_cols(arr,a,[0.2,.7,.2,.2], 'Modello', 'Southeast','$log(\frac{1}{N})$','$log(\Delta)$','red',[1 13],true,[2 6])