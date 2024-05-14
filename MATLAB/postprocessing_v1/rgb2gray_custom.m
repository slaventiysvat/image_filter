function gray_image = rgb2gray_custom(image_in)
%Rec.ITU-R BT.709 Formula, becouse rgb2gray works in other grayscale
%representation
% image_in should be as uint8 format
% gray_image will return as single format
[m n k] = size(image_in);
gray_image = zeros(m,n,k);
image_in = image_in./255;
for i = 1:1:m
    
   for j = 1:1:n
    
       gray_image(i,j) = ((0.21 * image_in(i,j,1)) + (0.72 * image_in(i,j,2)) + (0.07 * image_in(i,j,3)));
       
   end
   
end

end