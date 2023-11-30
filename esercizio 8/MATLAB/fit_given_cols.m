%funzione che fitta i dati a partire da due array colonne che vengono
%passate come parametro
function [] = fit_given_cols(asc,ord,dim,legend_title,location,x_lab,y_lab,textcolor,range,logscale, guess,model)
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
    
    opt = fitoptions('Method','NonlinearLeastSquares','StartPoint',guess);
    f = fit(asc(range(1):range(2)),ord(range(1):range(2)),model,opt);
    plot(f,asc,ord);
    display(f);
    
    %get coefficient values and other graphic options
    par = coeffvalues(f);
    set(0,'defaultTextInterpreter','latex');
    str = "";
    names = coeffnames(model);
    for i=1:size(par,2)
        name = names(i);
        % display(name{:})
        str = str + name{:} + " = " +par(i);
        if(i~=size(par,2))
            str = str + newline;
        end
    end
    % str = "\alpha = " + par(1);
    legend( 'Dati',legend_title,'Location',location);
    xlabel(x_lab);
    ylabel(y_lab);
    annotation('textbox',dim,'String',str,'FitBoxToText','on','Color',textcolor);
    hold off;
end