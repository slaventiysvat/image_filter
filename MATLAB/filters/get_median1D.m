function val = get_median1D(array)
%need to optimize using pivot median
val = nlogn_median(array);


end


function  med_val = nlogn_median(array)
    l = sort(array);
    N = length(l);
    if mod(N,2)== 1
       med_val = l(ceil(N/2));
    else
       med_val = 0.5 * (l(ceil(N/2) - 1) + l(ceil(N / 2)));
    end
end