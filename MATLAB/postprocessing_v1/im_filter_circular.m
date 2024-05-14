function  out_image = im_filter_circular(input_image,mask)
%works only for RGB image
rgb_R = input_image(:,:,1);
rgb_G = input_image(:,:,2);
rgb_B = input_image(:,:,3);

%of image will be replaced using circular approach
f_R=imfilter(rgb_R,mask,'circular');
f_G=imfilter(rgb_G,mask,'circular');
f_B=imfilter(rgb_B,mask,'circular');
        
%getting new image (filtred)
rgb_tmp = cat(3,f_R,f_G,f_B);        
out_image = imsubtract(input_image,rgb_tmp);

end