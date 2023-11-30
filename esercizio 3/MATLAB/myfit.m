%funzione che fitta i dati estraendo le prime due colonne da un file
%il cui nome viene passato come parametro
function [] = myfit(file,dim,legend_title,location,x_lab,y_lab,textcolor,range,logscale, guess)
    %estract data from file
    [asc,ord]=readvars(file);
    if(range(2)>size(asc,1))
        range(2)=size(asc,1);
    end
    figure;
    hold on;
    
    %set log scale
    if(logscale)
        asc = log(asc);
        ord = log(ord);
    end
    
    %fit the data within the positions defined in "range"
    ft = fittype('c+a*x',...
    'dependent',{'y'},'independent',{'x'},...
    'coefficients',{'a','c'});
    
    opt = fitoptions('Method','NonlinearLeastSquares','StartPoint',guess);
    f = fit(asc(range(1):range(2)),ord(range(1):range(2)),ft,opt);
    plot(f,asc,ord);
    display(f);
    
    %get coefficient values and other graphic options
    par = coeffvalues(f);
    set(0,'defaultTextInterpreter','latex');
    str = "\alpha = " + par(1);
    legend( 'Dati',legend_title,'Location',location);
    xlabel(x_lab);
    ylabel(y_lab);
    annotation('textbox',dim,'String',str,'FitBoxToText','on','Color',textcolor);
    hold off;
end