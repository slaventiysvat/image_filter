function output_array = border_replication_zerros(input_array,kernel_size)
%kernel of median filter must be odd
%kernel size must be bigger than 3
[m n] = size(input_array);
N = kernel_size - ceil(kernel_size/2);
output_array = zeros(m + (2*N),n + (2*N));
k = 1;
l = 1;
for i = N+1:1:m+N
    
    for j = N+1:1:n+N
       
        output_array(i,j) = input_array(k,l);
        l = l + 1;
    end
    k = k + 1;
    l = 1;
end

end