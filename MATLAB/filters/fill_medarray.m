function array = fill_medarray(array_in,i,j,kernel_size)
%i,j - current indexes of array_in
%kernel_size - size of median filter kernel
array = zeros(1,kernel_size * kernel_size);
k = 1;
start_step_y = (i - floor(kernel_size/2));
start_step_x = (j - floor(kernel_size/2));
end_row = start_step_y + (kernel_size - 1);
end_col = start_step_x + (kernel_size - 1);
for i_ind = start_step_y:1:end_row
   for j_ind = start_step_x:1:end_col
       array(k) = array_in(i_ind,j_ind);
       k = k + 1;
   end
end

end