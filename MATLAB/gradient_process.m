
ima = imread('artificial.bmp');
% image_in = double(image_in);
% image_in = image_in./255;

%  k=-1*ones(5);k(3,3)=23;
%  ima(:,:,1)=conv2(R,k,'same');
%  ima(:,:,2)=conv2(G,k,'same');
%  ima(:,:,3)=conv2(B,k,'same');
 figure, imshow(ima)
 
z = rgb2hsv(ima); % преобразование в формат hsi

[GmagH,GdirH] = imgradient(z(:,:,1));
[GmagS,GdirS] = imgradient(z(:,:,2));
[GmagV,GdirV] = imgradient(z(:,:,3));

figure(1)
imshow(GmagH)
title('GmagH');
figure(2)
imshow(GmagS)
title('GmagS');
figure(3)
imshow(GmagV)
title('GmagV');
R = ima(:,:,1);
G = ima(:,:,2);
B = ima(:,:,3);
[m n k] = size(ima);
[Y,U,V] = rgb2yuv(R,G,B,'YUV444_8','BT709_l');

% U = conv2(U,k,'same');
% V = conv2(V,k,'same');
 
[Gx,Gy] = imgradientxy(U);

[GmagU,GdirU] = imgradient(U);
[GmagV,GdirV] = imgradient(V);
[GmagY,GdirY] = imgradient(Y);