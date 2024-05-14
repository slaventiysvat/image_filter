clear all
close all
clc

f=imread('artificial.tiff'); imshow(f); % фото слева
z=rgb2hsv(f); % преобразование в формат hsi
z1=z(:,:,1);z2=z(:,:,2);z3=z(:,:,3);
g3=imadjust(z3,[],[],0.5); % корректировка интенсивности I
g=cat(3,z1,z2,g3); % создание нового HSI изображения
e= hsv2rgb(g); % преобразование в формат RGB
figure,imshow(e); % изображение справа