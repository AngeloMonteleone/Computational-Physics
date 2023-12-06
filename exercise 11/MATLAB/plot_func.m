function [] = plot_func(xlab,ylab,grid_on,func,lims)
    fplot(func);
    axis(lims)
    xlabel(xlab);
    ylabel(ylab);
    if(grid_on)
       grid on;
    end
end