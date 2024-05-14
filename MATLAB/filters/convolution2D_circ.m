function output_image = convolution2D_circ(input_array,kernel)
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
% Rep = zeros(r + top + bottom, c + left + right);
% for x = 1 + top : r + top
%     for y = 1 + left : c + left
%         Rep(x,y) = A(x - top, y - left);
%     end
% end
Rep = border_replication_circular(input_array,kernel_size);
B = zeros(r, c);
for x = 1:r
    for y = 1:c 
        for i = 1 : m
            for j = 1 : n
                q = x - 1;
                w = y -1;
                B(x, y) = B(x, y) + (Rep(i + q, j + w) * h(i, j)); 
            end
        end
    end
end

maxb  = max(max(abs(B)));
B = B./maxb;
output_image = uint8(abs(B).*255);
output_image = im2uint8(B);
% C = conv2(input_array,kernel,'full');
end