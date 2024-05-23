clear all
close all
clc

image_in = imread('artificial.bmp');
image_gray = rgb2gray(image_in);

image_in_1 = imread('DeltaE_8bit_gamma2.2.bmp');
image_gray_1 = rgb2gray(image_in_1);

figure(1)
subplot(221)
imshow(image_in_1)
xlabel('X')
ylabel('Y')
title('normal image')
subplot(222)
imshow(image_in)
xlabel('X')
ylabel('Y')
title('bad image')
subplot(223)
histogram(image_gray_1)
title('Histogramm of a normal image')
xlabel('X')
ylabel('Y')
subplot(224)
histogram(image_gray)
title('Histogramm of a bad image')
xlabel('X')
ylabel('Y')