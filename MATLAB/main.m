clear all
close all
clc

image_in = imread('artificial.bmp');
% image_in = double(image_in);
% image_in = image_in./255;

J = image_in;
J = imnoise(image_in,'gaussian',0.02,0.01);
figure(1)
imshow(J)
title('Image with Noise')
image_gray = rgb2gray(J);
B = imgaussfilt(J,2.5);
figure(2)
imshow(B)
title('Image after Gauss Filter')
[m n k] = size(image_in);
image_out = zeros(m,n,k);
image_out1 = zeros(m,n,k);
sigma = 0.1;
alpha = 0.5;
image_out = locallapfilt(single(B), sigma, alpha);%returning contrasts!!!
image_out(:,:,1) = medfilt2(B(:,:,1),[4 4]);
image_out(:,:,2) = medfilt2(B(:,:,2),[4 4]);
image_out(:,:,3) = medfilt2(B(:,:,3),[4 4]);
noisyLAB = rgb2lab(B);
roi = [210,24,52,41];
patch = imcrop(noisyLAB,roi);

patchSq = patch.^2;
edist = sqrt(sum(patchSq,3));
patchSigma = sqrt(var(edist(:)));

DoS = 0.25*patchSigma;
image_out = imnlmfilt(B,'DegreeOfSmoothing',DoS);
figure(3)
imshow(image_out)
title('Image after NLM filter')

t = 5 %  t: radio of search window
f = 2 %  f: radio of similarity window
h = 2; %  h: degree of filtering
B = im2double(B);
image_out1(:,:,1) = NLmeansfilter(B(:,:,1),t,f,h);
image_out1(:,:,2) = NLmeansfilter(B(:,:,2),t,f,h);
image_out1(:,:,3) = NLmeansfilter(B(:,:,3),t,f,h);
figure(4)
imshow(image_out1)
title('Image after NLM filter custom')


% imwrite(image_out,'artificial_changed.bmp','BMP');
% h = fspecial('laplacian',[3 3]);
% B = imfilter(image_in,h,'same');


















