function out_image = autolevels_my(input_image)
R = input_image(:,:,1);
G = input_image(:,:,2);
B = input_image(:,:,3);

[m n k]= size(input_image);
out_image  = zeros(m, n, k);
Rmin = min(min(R));
Rmax = max(max(R));

Gmin = min(min(G));
Gmax = max(max(G));

Bmin = min(min(B));
Bmax = max(max(B));

%intencity transformations
Max_pixel_default = 1;
Min_pixel_default = 0;
input_image = double(input_image);
    for i = 1:1:m

        for j = 1:1:n
            
             out_image(i,j,1) = (input_image(i,j,1) - Rmin) * ((Max_pixel_default - Min_pixel_default)/(Rmax - Rmin));
             out_image(i,j,2) = (input_image(i,j,2) - Gmin) * ((Max_pixel_default - Min_pixel_default)/(Gmax - Gmin));
             out_image(i,j,3) = (input_image(i,j,3) - Bmin) * ((Max_pixel_default - Min_pixel_default)/(Bmax - Bmin));
          
        end
    
    end
    
end