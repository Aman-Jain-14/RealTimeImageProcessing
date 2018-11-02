Img=zeros(1,576*720);

for q=270:1:290
    for w=300:1:320
        Img(q*720+w)=1;
    end
end

p0(1)=270;
p0(2)=297;

imshow(Img);