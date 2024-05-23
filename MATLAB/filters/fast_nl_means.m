function  [output]=fast_nl_means(x,f,t,h)
% fast nonlocal means filter,a fast implementation of nonlocal means filter for image
% denoising.
% x :         a 2D image and
% f:          % radius of square patch
% t:          % searching range in each direction
% kernel      
% sigma           noise variance 
% last modified 24/04 2010 
% Size of the image
[m n]=size(x);
% Memory for the output
output=[];
% Replicate the boundaries of the x image
x2 = padarray(x,[f+t f+t],'symmetric');
kernel = make_kernel(f); 
 squ_sum=x2.*x2;gsqu_sum=imfilter(squ_sum,kernel);
wd=2*f+1; % width of widow;
ff = floor(length(kernel)/2);
h=h^2;
rw = [];
for i=1:m
    for j=1:n
        i1 = i+ t+f;
        j1 = j+ t+f;
        dm = 1;
        dn = 1;
         for gm = i1+f:-1:i1-f
             
             for gn = j1+f:-1:j1-f
                 
                 rw(dm,dn) = x2(gm,gn) * kernel(dm,dn);
                 dn = dn + 1;
             end
             dm = dm + 1;
             dn = 1;
         end       
        bw=x2(i1-t-f:i1+t+f,j1-t-f:j1+t+f);   % big window for similarity searching
        % convolution computation
        cv_bw = convolution2D_valid(bw,rw);%cv_bw=conv2(bw,rw,'same');%cv_bw = filter2(rw,bw,'valid');        
        %-----------------------------------
        gsq_dis=gsqu_sum(i1,j1)+gsqu_sum(i1-t:i1+t,j1-t:j1+t)-2*cv_bw;
        weight=exp(-gsq_dis/h);
        weight(t+1,t+1)=0;
        weight(t+1,t+1)=max(weight(:));
        est=x2(i1-t:i1+t,j1-t:j1+t).*weight;
        output(i,j)=sum(est(:))/(sum(weight(:)));
    end
    
end

end





