function [ Img,a ] = flood_fill( i,j,Img,a )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

connectivity = [-1 -1 -1 0 +1 +1 +1 0; -1 0 +1 +1 +1 0 -1 -1];

for m=1:1:8
    if Img(i+connectivity(1,m),j+connectivity(2,m))== 1
        Img(i+connectivity(1,m),j+connectivity(2,m))= 0;
        a=a+1;
        [Img,a] = flood_fill((i+connectivity(1,m)),(j+connectivity(2,m)),Img,a);
    end
end

