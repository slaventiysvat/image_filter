clear all
close all
clc

%  A = randn(9,9);
%  A = A ./max(max(A));
%  A = int32(A .* 255); 
%  A = single(A);
% rgbImage = imread('peppers.png');
% % rgbImage = rgb2gray(im2double(rgbImage));
% % rgbImage = im2uint8(rgbImage);
% rgbImagef = im2single(rgbImage);
% kernel = fspecial('gaussian', [11 11], 2.5);
% kernel = gauss_kernel_create(2.5);
% blurredImage = imfilter(rgbImage, kernel);
% figure(1)
% imshow(blurredImage);
% B = imgaussfilt(rgbImage,2.5);
% figure(2)
% imshow(B);
% output_image = convolution2D_circ(rgbImage,kernel);
% figure(3)
% imshow(output_image);
% downSample = imresize(blurredImage, 1); % downSample by factor of 3 
% imshow(downSample);


 A =   [52,-  97,  -45,  55,   40,  -144, -131, -39, -51;...
       -40,  -45,  -63, -58, -103,   156,   64, -33,-125;...
       -124,  192, -178, 47,    8,  -203,  -34, -25, -24;...
        238, -141, -182, 136,   -94, -126,  173,  67, -64;...
       156, -114,   81, -84,   -96,   22,   -9, -48,  -2;...
       -87, -174,  106, -49,   144, -113, -183, -19, -70;...
         6,   92,   15,  33,   -71,   10,   -7, -69,  97;...
       106,   55,  226,   5,  -255,  103,  148, -14,  44;...
       -91, -112,	-136, 115,     5,  174,   63,  255, 20];

A = abs(A);
output_image = border_copy_symmetric(A,18);
% array = fill_medarray(A,5,5,5);

kernel =[1 1 1;
         1 -8 1;
         1 1 1];
rgbImage = imread('artificial.bmp');
rgbImage(:,:,1) = medfilter2D(rgbImage(:,:,1),5);
rgbImage(:,:,2) = medfilter2D(rgbImage(:,:,2),5);
rgbImage(:,:,3) = medfilter2D(rgbImage(:,:,3),5);
%      rot90(kernel)
%output_array = convolution2D_circ(A,kernel);
% output_array = border_replication_circular(A,5);
% output_array1 = border_replication_zerros(A,5);
% for i = 2:1:9-1
% 
%    for j = 2:1:9-1
%        
%        array = fill_medarray(A,i,j,3);
%        disp(array);
%        
%    end
%    
% end
% array = fill_medarray(A,5,8,3);
%  
% med_val = get_median1D(array);
% med_val_orig = median(array);
% output_array = border_replication_zerros(A,9);
% image_out2 = medfilter2D(A,3);
% image_out1 = medfilt2(A,[3 3]);

 