function h = gauss_kernel_create(sigma1)
sigma = [sigma1 sigma1];
hsize = 2*ceil(2*sigma)+1;

% hsize = vector [x y]
% sigma - value
filterRadius = (hsize-1)/2;
filterDims = numel(hsize);

% 2-D Gaussian kernel
[X,Y] = meshgrid(-filterRadius(2):filterRadius(2), -filterRadius(1):filterRadius(1));
arg = (X.*X)/(sigma(2)*sigma(2)) + (Y.*Y)/(sigma(1)*sigma(1));

h = exp( -arg/2 );

% Suppress near-zero components	
h(h < eps*max(h(:)) ) = 0;

% Normalize
sumH = sum(h(:));
if sumH ~=0
    h = h./sumH;
end

end