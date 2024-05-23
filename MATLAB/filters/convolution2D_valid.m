function output_image = convolution2D_valid(input_array,kernel)
% A = border_replication_circular(input_array,kernel);
kernel_size = length(kernel);
N = floor(kernel_size/2) + 1; 
% A = border_replication_zerros(input_array,kernel_size);
A = input_array;
k = kernel;
[r c] = size(A);
[m n] = size(k);
h = rot90(k, 2);
center = floor((size(h)+1)/2);
left = center(2) - 1;
right = n - center(2);
top = center(1) - 1;
bottom = m - center(1);
Rep = zeros(r + top + bottom, c + left + right);
for x = 1 + top : r + top
    for y = 1 + left : c + left
        Rep(x,y) = A(x - top, y - left);
    end
end
% Rep = border_copy_symmetric(input_array,kernel_size);
o_i = 1;
o_j = 1;
k1 = r - (N + 1);
k2 = c - (N + 1);
output_image = zeros(k1,k2);
output_tmp_image = zeros(r,c);
for x = 1 : r
    for y = 1 : c
        B = 0;
        for i = 1 : m
            for j = 1 : n
                q = x - 1;
                w = y - 1;
                B = B + (Rep(i + q, j + w) * h(i, j)); 
            end
        end
        output_tmp_image(o_i,o_j) = B;
        o_j = o_j + 1;
    end
    o_i = o_i + 1;
    o_j = 1;
end

o_i = 1;
o_j = 1;
for x = N : k1+2
    
    for y = N : k2+2
        
        output_image(o_i,o_j) =  output_tmp_image(x,y);
        
        o_j = o_j + 1;
    end
    o_i = o_i + 1;
    o_j = 1;
end
% C = conv2(input_array,kernel,'full');
end