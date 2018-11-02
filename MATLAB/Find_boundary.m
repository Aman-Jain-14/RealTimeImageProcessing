function [ boundary_list, bsize ] = Find_boundary (Img, Thr, p0)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
bsize=0;
boundary_list=zeros(1000,2);

p_next(1)=0;
p_next(2)=0;

p_prev(1)=0;
p_prev(2)=0;

flag=0;

for i=p0(1):1:575
    for j=p0(2):1:719
       
        if Img(i*720 + j) > Thr
            bsize=bsize+1;
            p(1)=i;
            p(2)=j;
            startpoint(1)=i;
            startpoint(2)=j;
            boundary_list(1,1)=i;
            boundary_list(1,2)=j;
            
            while (p_next(1)~=startpoint(1) || p_next(2)~=startpoint(2))
                if bsize==1
                    p_prev(1)=p(1);
                    p_prev(2)=p(2)-1;
                    p_next=moore_domain(p,p_prev,Img,Thr);
                else
                    p_next=moore_domain(p,p_prev,Img,Thr);
                end
                
                bsize=bsize+1;
                boundary_list(bsize,1)=p(1);
                boundary_list(bsize,2)=p(2);
                p_prev=p;
                p=p_next;
                               
            end
            bsize=bsize-1;
            
        end
    end
    bsize
end

