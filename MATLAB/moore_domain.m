function p_next = moore_domain ( p,p_prev,Img,Thr)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

connectivity = [-1 -1 -1 0 +1 +1 +1 0; -1 0 +1 +1 +1 0 -1 -1];
t=0;

for m=1:1:8
    if (p(1)+connectivity(1,m)==p_prev(1) && p(2)+connectivity(2,m)==p_prev(2))
        t=m;
        break;
    end
end

t=t+1;

        for m=t:1:(t+8)
            x=rem(m,9);
            if(x==0)
                x=1;
            end
            if Img(((p(1)+connectivity(1,x))*720)+p(2)+connectivity(2,x)) > Thr
                p_next(1)=p(1)+connectivity(1,x);
                p_next(2)=p(2)+connectivity(2,x);
                break;
            end
        end
  


