clear all
close all
clc

%Load compressed image, normilize it
image_in = imread('artificial.bmp');
image_in = double(image_in);
image_in = image_in./255;

%Load original image, normilize it
image_in_org = imread('DeltaE_8bit_gamma2.2.bmp');
image_in_org = double(image_in_org);
image_in_org = image_in_org./255;

%add Gaussian Noise to image
J = image_in;
J = imnoise(image_in,'gaussian',0.02);
figure(1)
imshow(J)
title('Image with Noise')

%make Grayscale image and add gaus noise
image_gray = rgb2gray(J);
B = imgaussfilt(J,2.5);
%B = J;
% figure(2)
% imshow(B)
% title('Image after Gauss Filter')

[m n k] = size(image_in);
image_out = zeros(m,n,k);
sigma = 0.1;
alpha = 0.5;

%use median filter to improving image
% image_out = locallapfilt(single(B), sigma, alpha);%returning contrasts!!!
image_out(:,:,1) = medfilt2(B(:,:,1),[5 5]);
image_out(:,:,2) = medfilt2(B(:,:,2),[5 5]);
image_out(:,:,3) = medfilt2(B(:,:,3),[5 5]);

%measure sigma from cropped part of image
noisyLAB = rgb2lab(B);
roi = [210,24,52,41];
patch = imcrop(noisyLAB,roi);

patchSq = patch.^2;
edist = sqrt(sum(patchSq,3));
patchSigma = sqrt(var(edist(:)));

%use nlm filter to filtering image
DoS = 0.25*patchSigma;
image_out = imnlmfilt(B,'DegreeOfSmoothing',DoS);
figure(3)
imshow(image_out)
title('Image after NLM filter')

lapMatrix=[1 1 1;
            1 -8 1;
            1 1 1];        
 Matrix2=[1 0 1;
    0 -4 0;
    1 0 1];

%use median filter with circular filter 
rgb_sharped = im_filter_circular(image_out,lapMatrix);
r = rgb_sharped(:,:,1)./max((max(rgb_sharped(:,:,1))));
g = rgb_sharped(:,:,1)./max((max(rgb_sharped(:,:,1))));
b = rgb_sharped(:,:,1)./max((max(rgb_sharped(:,:,1))));

r1 = uint8((r.*255));
J = im2uint8(r);

%use circular filter for filtering image
rgb_sharped1 = im_filter_circular(image_out,Matrix2);

figure(1);
subplot(221);
imshow(image_in);
title('Input Image');
subplot(222);
imshow(image_out);
title('Image Out "Blurred"');
subplot(223)
imshow(rgb_sharped);
title('Image Out "Sharped1"');
subplot(224)
imshow(rgb_sharped1);
title('Image Out "Sharped2"');

%estimating PSNR and SSIM
fprintf('===============SSIM Estimating================= \n');
ssimval1 = ssim(image_in,image_in_org);
fprintf('SSIM Original and Resized Image = %f5 \n',ssimval1);
ssimval2 = ssim(rgb_sharped,image_in_org);
fprintf('SSIM Original Image and Output Image = %f5 \n',ssimval2);
ssimval3 = ssim(rgb_sharped,image_in);
fprintf('SSIM Resized Image and Output Image = %f5 \n',ssimval3);

fprintf('===============PSNR Estimating================= \n');
psnrval1 = psnr(image_in,image_in_org);
fprintf('PSNR Original and Resized Image = %f5 \n',psnrval1);
psnrval2 = psnr(rgb_sharped,image_in_org);
fprintf('PSNR Original Image and Output Image = %f5 \n',psnrval2);
psnrval3 = psnr(rgb_sharped,image_in);
fprintf('PSNR Resized Image and Output Image = %f5 \n',psnrval3);

