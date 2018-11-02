surface=0;
sumh=0;
sumw=0;

for m=1:1:576
    for n=1:1:720
        if Img(m,n)==1
            surface=surface+1;
            sumh = sumh + m;
            sumw = sumw + n;
        end
    end
end

 centre(1)=sumh/surface;
 centre(2)=sumw/surface;

n=round (centre(2));
for m=(round(centre(1)-5)):1:round((centre(1)+5))
    Img(m,n)=0;
end

m=round(centre(1));
for n=round((centre(2)-5)):1:round((centre(2)+5))
    Img(m,n)=0;
end

imshow(Img);


