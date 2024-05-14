function output_array = border_replication_circular(input_array,kernel_size)
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
[m n] = size(output_array);
k = 1;
l = 1;
%copy up border of image 'same'
k = k + (N - 1);
for i = N-1:1:2*(N - 1)

    for j = N+1:1:(n - N)
       
        output_array(i,j) = input_array(k,l);
        l = l + 1;
    end
    k = k - 1;
    l = 1;
end

%copy down border of image 'circular'
[M L] = size(input_array);
k = M - (N-2);
for i = m-N+1:1:m

    for j = N+1:1:(n - N)
       
        output_array(i,j) = input_array(k,l);
        l = l + 1;
    end
    k = k - 1;
    l = 1;
end
%computing left side and right side  of image
k = N+1;
indx_i = m - N;
indx_j = n - (N-1);
indx_j_tale = n - (N-1);
d = N;
for i = 1:1:m

    for j = 1:1:N
        
        output_array(i,indx_j) = output_array(i,indx_j_tale-j);
        output_array(i,d) = output_array(i,k);
        indx_j = indx_j + 1;
        k = k + 1;
        d = d - 1;
    end
    d = N;
    indx_j = n - (N-1);
    k = N+1;
    l = 1;
end

end