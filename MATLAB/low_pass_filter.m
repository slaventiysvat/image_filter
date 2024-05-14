function filtred_image = low_pass_filter(input_image,kernel)
%filter works for only square kernels
%filters kernel size should be bigger than 1;
[m n] = size(input_image);
filtred_image = zeros(m,n);
%computing borders of place where will be input image
D = length(kernel);
a1 = floor(D/2) + round(mod(D,2));
filter_place = zeros(m + a1,n + a1);
%prepearing image to filtration
%border pixel replication process
%EXAMPLE (Here we have test image matrix), 
%    __ __ __ __ ___
%   |_1_|_2_|_2_|_4_|
%   |_5_|_6_|_7_|_9_|  
%   |_9_|_10|_11|_12|   
%   |_13|_14|_15|_16|
%
% Kernel of filter will be 3x3, the extra size for image replication pixels
% will be a1 = (floor(3/2) + round(mod(3,2))) - 1; a1 = 1;
% after pixel replication we should have such rezult
%  _______________________
% |_1_|_1_|_2_|_2_|_4_|_4_|
% |_1_|_1_|_2_|_2_|_4_|_4_|
% |_5_|_5_|_6_|_7_|_9_|_9_|  
% |_9_|_9_|_10|_11|_12|_12|   
% |13_|_13|_14|_15|_16|_16|
% |13_|_13|_14|_15|_16|_16|
%
% Border pixel replication process

for k = 2:1:m + a1
    filter_place(1,1) = input_image(1,1);
    for n = 2:1:n + a1
        
        filter_place(k,n) = input_image(k-1,n-1);
        
    end
    filter_place(k,n) = input_image(k,n);
end
%Convolution process
     for i = a1:1:m
         
          for j = a1:1:n
              value = 0;
              for K = 1:1:k-1
                  
                  for L = 1:1:l-1
                      
                       value = value + filter_place(i+K-1,j+L-1) * kernel(K,L);
                      
                  end
         
              end
              filter_place(i,j) = value;    
          end
          
     end
     
%copy image to rezult matrix array
for i = a1:1:m
    
    for j = a1:1:n
        
        filtred_image(i,j) = filter_place(i-a1+1,j-a1+1);
        
    end
    
end
     
end