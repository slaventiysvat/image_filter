function output_image = medfilter2D(input_image,kernel_size)
%kernel of median filter must be odd
%kernel size must be bigger than 3
[m n] = size(input_image);
output_image = zeros(m,n);
N = kernel_size - ceil(kernel_size/2);
output_array = zeros(m + (2*N),n + (2*N));
k = 1;
l = 1;
%prepearing image before filtrations
for i = N+1:1:m+N
    
    for j = N+1:1:n+N
       
        output_array(i,j) = input_image(k,l);
        l = l + 1;
    end
    k = k + 1;
    l = 1;
end

kernel_array = zeros(1,kernel_size*kernel_size);
%median filter process
k = 1;
l = 1;
output_mat = [];
% array = fill_medarray(output_array,3,3074,kernel_size);
for i = N+1:1:m+N
    
    for j = N+1:1:n+N
%         output_mat(k,l) = output_array(i,j);
        array = fill_medarray(output_array,i,j,kernel_size);
        %copy pixel after filtrations to rezult array
        output_image(k,l) = get_median1D(array);
%         output_image(k,l) = median(array);
        l = l + 1;
    end
    k = k + 1;
    l = 1;
end

end