clear all
close all
clc
% load flujet.mat
% colormap gray
% V = single(X(200:300,1:25));
% imagesc(V);
% axis off
% title('Original Image');
% Vq = interp2(V,4,'spline');
% Vq = interp2(Vq,1/4);
% imagesc(Vq);
% axis off
% title('Linear Interpolation')
% Vq = interp2(Vq,1/4);
% imagesc(Vq);
% axis off
% title('Linear Interpolation')
ima = imread('artificial.tiff');
ima = imgaussfilt(ima,2.5);
% A_sRGB = lin2rgb(ima,'OutputType','double','ColorSpace','adobe-rgb-1998');
% A_sRGB = lin2rgb(A_sRGB,'OutputType','double','ColorSpace','adobe-rgb-1998');
% A_sRGB = lin2rgb(A_sRGB,'OutputType','double','ColorSpace','adobe-rgb-1998');
% ima = single(ima)./255;
figure(1)
imshow(A_sRGB);

%ima = ima./255;

R = ima(:,:,1);
G = ima(:,:,2);
B = ima(:,:,3);
[m n k] = size(ima);
G1 = ones(m,n).*128;
imshow(G1);
colormap(gray(256));
G1 = im2double(G1);
B = imgaussfilt(ima,2.5);
B = im2double(B);
B(:,:,1) = B(:,:,1) + G1;
B(:,:,2) = B(:,:,2) + G1;
B(:,:,3) = B(:,:,3) + G1;
B = imnoise(B,'gaussian',0.02);
[Y,U,V] = rgb2yuv(R,G,B,'YUV444_8','BT709_l');

% Y = single(Y);
% U = single(U);
% V = single(V);
% U = interp2(U,0.5,'spline');
% Set bilateral filter parameters.
% w     = 5;       % bilateral filter half-width
% sigma = [3 0.1]; % bilateral filter standard deviations
% U = bfilter2(U,w,sigma);
% U = imresample([m n],U,[m n],'spline');
Y = single(Y)/255;
U = single(U)/255;
V = single(V)/255;

[m n] = size(U);

% U = imresample([m n],U,[m/4 n/4],'spline');
% U = imresample([m/4 n/4],U,[m n],'spline');
% 
% V = imresample([m n],V,[m/4 n/4],'spline');
% V = imresample([m/4 n/4],V,[m n],'spline');
% 
% 
% Y = imresample([m n],Y,[m/4 n/4],'spline');
% Y = imresample([m/4 n/4],Y,[m n],'spline');

% Y = butterworthbpf(Y,1000,1200,64);
% U  = antialias(U);
% V  = antialias(V);
% U = interp2(U,0.5,'spline');
% Y = medfilt2(Y,[16 16]);
% U = medfilt2(U,[32 32]);
% V = medfilt2(V,[32 32]);
% V = imgaussfilt(V,0.05);
% Y = imgaussfilt(Y,3);
% V = imadjust(V);
Y = uint8(Y*255);
U = uint8(U*255);
V = uint8(V*255);

rgb = yuv2rgb(Y,U,V,'YUV444_8','BT709_l');
rgb = imsharpen(rgb);
figure(2)
imshow(rgb)


function zaa = antialias(z)
kernel = 1 + [0,1,0; 1,0,1; 0,1,0]/4;
kernel = kernel / sum(kernel(:));
zaa = conv2(z, kernel, 'same');
end
