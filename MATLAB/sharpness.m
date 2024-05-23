% Повышение резкости цветного изображения

clc;
clear all;
close all;

rgb1= imread('artificial_changed.bmp');
rgb=im2double(rgb1);
rgb_R=rgb(:,:,1);
rgb_G= rgb(:,:,2);
rgb_B= rgb(:,:,3);
lapMatrix=[1 1 1;
            1 -8 1;
            1 1 1];
        %формадоска1 1*8
Matrix2=[1 0 1;
    0 -4 0;
    1 0 1];
%формадоска21*4

%формадоска1*8 3Фильтр повышения резкости с другим третьим параметром
%replicate

f_R=imfilter(rgb_R,lapMatrix,'replicate');
f_G=imfilter(rgb_G,lapMatrix,'replicate');
f_B=imfilter(rgb_B,lapMatrix,'replicate');

%symmetric
f_R2=imfilter(rgb_R,lapMatrix,'symmetric');
f_G2=imfilter(rgb_G,lapMatrix,'symmetric');
f_B2=imfilter(rgb_B,lapMatrix,'symmetric');

%circular
f_R3=imfilter(rgb_R,lapMatrix,'circular');
f_G3=imfilter(rgb_G,lapMatrix,'circular');
f_B3=imfilter(rgb_B,lapMatrix,'circular');

%формадоска 1*4 3Фильтр повышения резкости с другим третьим параметром
%replicate
f2_R=imfilter(rgb_R,Matrix2,'replicate');
f2_G=imfilter(rgb_G,Matrix2,'replicate');
f2_B=imfilter(rgb_B,Matrix2,'replicate');

%symmetric
f2_R2=imfilter(rgb_R,Matrix2,'symmetric');
f2_G2=imfilter(rgb_G,Matrix2,'symmetric');
f2_B2=imfilter(rgb_B,Matrix2,'symmetric');

%circular
f2_R3=imfilter(rgb_R,Matrix2,'circular');
f2_G3=imfilter(rgb_G,Matrix2,'circular');
f2_B3=imfilter(rgb_B,Matrix2,'circular');

%формадоска1  Заостренный3Часть
rgb_tmp=cat(3,f_R,f_G,f_B);
rgb_tmp2=cat(3,f_R2,f_G2,f_B2);
rgb_tmp3=cat(3,f_R3,f_G3,f_B3);

%формадоска2  Заостренный3Часть
rgb2_tmp=cat(3,f2_R,f2_G,f2_B);
rgb2_tmp2=cat(3,f2_R2,f2_G2,f2_B2);
rgb2_tmp3=cat(3,f2_R3,f2_G3,f2_B3);

%формадоска1 3Результат обработки этого параметра вычитается из исходного изображения.
rgb_sharped =imsubtract(rgb,rgb_tmp);
rgb_sharped2=imsubtract(rgb,rgb_tmp2);
rgb_sharped3=imsubtract(rgb,rgb_tmp3);

%формадоска2 3Результат обработки этого параметра вычитается из исходного изображения.
rgb2_sharped =imsubtract(rgb,rgb2_tmp);
rgb2_sharped2=imsubtract(rgb,rgb2_tmp2);
rgb2_sharped3=imsubtract(rgb,rgb2_tmp3);

figure;
subplot(341);imshow(rgb);title('Исходное изображение');
subplot(342);imshow(rgb_R);title('R');
subplot(343);imshow(rgb_G);title('G');
subplot(344);imshow(rgb_B);title('B');

subplot(345);imshow(rgb_tmp);title('cat_r_g_b ');
subplot(346);imshow(rgb_tmp2);title('cat_r_g_b2');
subplot(347);imshow(rgb_tmp3);title('cat_r_g_b3');

subplot(348);imshow(rgb_sharped);title('1*8 replicate');
subplot(349);imshow(rgb_sharped2);title('1*8 symmetric');
subplot(3,4,10);imshow(rgb_sharped3);title('1*8 3 circular');

rgb_diff=imsubtract(rgb_sharped,rgb_sharped2);%replicate sub symmetric

subplot(3,4,11);imshow(rgb_diff);title('replicateSubSymmetric');

figure;
subplot(341);imshow(rgb);title('Исходное изображение');
subplot(342);imshow(rgb_R);title('R');
subplot(343);imshow(rgb_G);title('G');
subplot(344);imshow(rgb_B);title('B');

subplot(345);imshow(rgb2_tmp);title('cat_r_g_b ');
subplot(346);imshow(rgb2_tmp2);title('cat_r_g_b2');
subplot(347);imshow(rgb2_tmp3);title('cat_r_g_b3');

subplot(348);imshow(rgb2_sharped);title('1*4 replicate');
subplot(349);imshow(rgb2_sharped2);title('1*4 symmetric');
subplot(3,4,10);imshow(rgb2_sharped3);title('1*4 3 circular');

rgb2_diff=imsubtract(rgb2_sharped,rgb2_sharped2);%replicate sub symmetric

subplot(3,4,11);imshow(rgb2_diff);title('replicateSubSymmetric2');

rgb3_diff=imsubtract(rgb2_sharped2,rgb_sharped2);%1*8Sub1*4
figure;
imshow(rgb3_diff);title('1*8Sub1*4');
