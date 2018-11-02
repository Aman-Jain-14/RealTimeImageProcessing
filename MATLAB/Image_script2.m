Img=zeros(576,720);
count=0;
for q=201:1:225
    for w=201:1:225
        Img(q,w)=1;
        count=count+1;
    end
end

count;

top1=0;
a=0;
stack(1000,2)=0;

for i=10:1:576
    for j=10:1:720
        if Img(i,j)==1
            a=a+1;
            Img(i,j)=0;
               [Img,a]= flood_fill(i,j,Img,a);
        end
    end
end     
                    
                