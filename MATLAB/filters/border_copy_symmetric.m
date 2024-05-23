function output_image = border_copy_symmetric(input_array,kernel_size)

output_image = padarray(input_array,[kernel_size kernel_size],'symmetric');

% [m n] = size(input_array);
% N = kernel_size - ceil(kernel_size/2);
% output_array = zeros(m + (2*N),n + (2*N));
% [H G] = size(output_array);
% k = 1;
% l = 1;
% for i = N+1:1:m+N
%     
%     for j = N+1:1:n+N
%        
%         output_array(i,j) = input_array(k,l);
%         l = l + 1;
%     end
%     k = k + 1;
%     l = 1;
% end
% 
% 
% %up side
% k = 1;
% l = 1;
% for i = N:-1:1
%     
%     for j = N+1:1:(n+N)
%         output_array(i,j) = input_array(k,l);
%         l = l + 1;
%     end
%     k = k + 1;
%     l = 1;
% end
% %down side
% k = G - ;
% l = 1;
% for i = H-N+1:1:H
%     
%     for j = N+1:1:(n+N)
%         output_array(i,j) = input_array(k,l);
%         l = l + 1;
%     end
%     k = k - 1;
%     l = 1;
% end
% 
% 
% %and left and right
% k = 1;
% l = 1;
% for i = N+1:1:m + N
%     
%     for j = N:-1:1
%         output_array(i,j) = input_array(k,l);
%         l = l + 1;
%     end
%     k = k + 1;
%     l = 1;
% end

%and left and right

end