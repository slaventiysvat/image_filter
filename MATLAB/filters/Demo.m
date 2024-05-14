%====================================================
% demo
%==================================================
%---------------------------------------------------
% This is a comparision of two implemantations of nonlocal means filter
% (NLM) for image denoising. Matlab funciton "fast_nl_means" is our
% fast implementation by using convolution, and "NLmeansfilter" is the
% classical implementation.
%---------------------------------------------------


% Any problems and advises are welcome .
% Email: love_truth@126.com,
% 2009-02-12

clear all;
iptsetpref('ImshowBorder','tight');
% load test image
timg=3;
switch timg
    case 1
        x0=double(imread('Cameraman256.png'));
    case 2
        x0 = double(imread('lena.png'));
     case 3
        x0 = double(imread('artificial.bmp')); 
        x0 = x0./255;
end

% add noise
randn('state',0)
sigma = 0.08; % variance of noise
x=x0+sigma*randn(size(x0));
figure(1), imshow(x,[])
disp(['psnr of noisy image=' num2str(psnr(x,x0)) 'dB'])
%--------parameters-------------
% delta for convergence control
f=5;   % radius of square patch 
t=15;   %searching range in each direction
%=======================================

%=======================================
% tic
% [output]=NLmeansfilter(x,t,f,sigma);
% toc
% figure(1), imshow(output,[])
% disp(['psnr of denoising output=' num2str(psnr(output,x0)) 'dB'])
%========================================							
tic
[m n k] = size(x);
x1 = zeros(floor(m/6), floor(n/6),k);
x1(:,:,1) = imresize(x(:,:,1),[floor(m/6) floor(n/6)]);
x1(:,:,2) = imresize(x(:,:,2),[floor(m/6) floor(n/6)]);
x1(:,:,3) = imresize(x(:,:,3),[floor(m/6) floor(n/6)]);
[m n k] = size(x1);
dx = zeros(m,n,k);
dx(:,:,1)=fast_nl_means(x1(:,:,1),f,t,sigma);
dx(:,:,2)=fast_nl_means(x1(:,:,2),f,t,sigma);
dx(:,:,3)=fast_nl_means(x1(:,:,3),f,t,sigma);
toc
figure(1), imshow(dx)
disp(['psnr of denoising output=' num2str(psnr(dx,x0)) 'dB'])
% x1 =im2uint8(x1);
% imwrite(x1,'artifical_341_512.bmp');
