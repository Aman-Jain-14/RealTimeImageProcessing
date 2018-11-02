/*
 * imageProcessing.c
 *
 *  Created on: 31 janv. 2013
 *      Author: pierre
 */

#include "imageProcessing.h"
int32 i,j,temp=0,temp1=0;
int32 ta[65536][2];
uint8 *YBufferForLabeling;
uint32 pixel[65536][2];
uint32 top=0;
int32 connect[2][8],length=0;
int16 id=-1;
uint16 yval,cbval,crval;
int32 isEven=0,isOdd=0,isCorner=0;

uint32 ycbcr[10][3];

typedef struct
{
	int32 RCList[65536][2];
	int32 boundaryList[5000][2];
	int32 freemanChainCode[5000];
	int32 boundarySize;
	int32 boundingbox;
	int32 count;

}sObject;

sObject s,*object;

typedef struct
{
	uint32 x,y;
}sPoint;

sPoint startingPoint,startPoint1;
sPoint p,startPoint,p_prev,p_next;


/* --------------------------------------------------------------------------------
 _____  _____   ____   _____ ______  _____ _____   ____  ______ _____ _____ _   _
|  __ \|  __ \ / __ \ / ____|  ____|/ ____/ ____| |  _ \|  ____/ ____|_   _| \ | |
| |__) | |__) | |  | | |    | |__  | (___| (___   | |_) | |__ | |  __  | | |  \| |
|  ___/|  _  /| |  | | |    |  __|  \___ \\___ \  |  _ <|  __|| | |_ | | | | . ` |
| |    | | \ \| |__| | |____| |____ ____) |___) | | |_) | |___| |__| |_| |_| |\  |
|_|    |_|  \_\\____/ \_____|______|_____/_____/  |____/|______\_____|_____|_| \_|

   -------------------------------------------------------------------------------- */
void Threshold(uint8 *YInputBuffer, uint8 *YOutputBuffer, uint32 imgHeight, uint32 imgWidth, uint8 *CbOutputBuffer, uint8 *CrOutputBuffer)
{
	for(i=0 ; i<imgHeight; i++)
		{
			for(j=0 ; j<imgWidth ; j++)
			{
				if(YInputBuffer[i*imgWidth + j]>88)
				{
					YOutputBuffer[i*imgWidth + j]=255;
				}
				else
					YOutputBuffer[i*imgWidth + j]=0;
			}
		}
	YBufferForLabeling = YOutputBuffer;
}

sPoint moore_domain (sPoint p, sPoint p_prev, uint8 *ybuffer, uint8 *CbOutputBuffer, uint8 *CrOutputBuffer, uint32 imgHeight, uint32 imgWidth)
{
	int32 t=0;
	int32 m,x,f=0;

	for (m=0 ; m<8 ; m++)
	{
		if((p.x+connect[0][m]==p_prev.x) && (p.y+connect[1][m]==p_prev.y))
		{
			t=m;
			break;
		}
	}

	t++;
	if(t==8)
		t=0;

	for( m=t ; m<(t+8) ; m++)
	{
		x=m%8;

		if((ybuffer[(p.x+connect[0][x])*imgWidth + (p.y+connect[1][x])]==104))
		 {
			f=x;
			f--;
			if(f==-1)
				f=7;
			s.count++;
						p_next.x=p.x+connect[0][x];
						p_next.y=p.y+connect[1][x];

						s.boundaryList[s.count][0]=i;
						s.boundaryList[s.count][1]=j;

						ybuffer[(p.x+connect[0][x])*imgWidth + (p.y+connect[1][x])]=60;
						CbOutputBuffer[((p.x+connect[0][x])*imgWidth/2) + ((p.y+connect[1][x])/2)]=216;
						CrOutputBuffer[((p.x+connect[0][x])*imgWidth/2) + ((p.y+connect[1][x])/2)]=216;

						s.freemanChainCode[s.count]=f;

						if(s.freemanChainCode[s.count]%2==0)
							isEven++;

						if(s.freemanChainCode[s.count]%2 != 0)
							isOdd++;

						if(s.count>2)
						{
							if(s.freemanChainCode[s.count] - s.freemanChainCode[s.count-1] !=0 )
								isCorner++;

						}
						break;

		 }
	}

	return p_next;
}


void computeBoundaryList (uint8 *ybuffer, sPoint startPoint1, sObject *object, uint32 imgHeight, uint32 imgWidth,uint8 *CbOutputBuffer, uint8 *CrOutputBuffer )
{
	p_next.x=0;
	p_next.y=0;

	s.count=0;
	length=0;
	uint8 flag=0;

	for(i=120 ; i<imgHeight-10 ; i++)
	{
		for(j=10 ; j<imgWidth-10 ; j++)
		{
			if(ybuffer[i*imgWidth + j]==104)
			{
				s.count++;
				p.x=i;
				p.y=j;
				startPoint.x=i;
				startPoint.y=j;
				s.boundaryList[s.count][0]=i;
				s.boundaryList[s.count][1]=j;

				while (p_next.x!= startPoint.x || p_next.y!=startPoint.y)
				{
					if (s.count==1)
					{
						p_prev.x=p.x;
						p_prev.y=p.y-1;

						p_next=moore_domain(p, p_prev, ybuffer, CbOutputBuffer,CrOutputBuffer,imgHeight, imgWidth);
					}
					else
						p_next=moore_domain(p,p_prev,ybuffer, CbOutputBuffer,CrOutputBuffer, imgHeight, imgWidth);

					s.boundaryList[s.count][0]=p.x;
					s.boundaryList[s.count][1]=p.y;

					p_prev=p;
					p=p_next;
				}

				flag++;
			}

			if(flag!=0)
				break;
		}
		if(flag!=0)
			break;
	}

	length= (isEven*98/100) + (isOdd*1406/1000) - (isCorner*91/1000);

}

void computeBoundingBox (uint8 *ybuffer,uint8 *CbOutputBuffer, uint8 *CrOutputBuffer, sObject *object, uint32 imgHeight, uint32 imgWidth)
{
	uint32 temp_min=imgWidth;
	temp=temp1=0;

	for(i=1; i<s.count ; i++)
	{
		if(temp1<s.boundaryList[i][1])
		{
			temp1=s.boundaryList[i][1];
		}
	}

	for(i=1 ; i<s.count ; i++)
	{
		if(temp_min>s.boundaryList[i][1])
		{
			temp_min=s.boundaryList[i][1];
		}
	}

	for(i=1; i<5000 ; i++)
	{
		if(temp<s.boundaryList[i][0])
		{
			temp=s.boundaryList[i][0];
		}
	}

	j=temp_min;
	for(i=startPoint.x ; i<temp ; i++)
	{
        ybuffer[i*imgWidth + j]=16;
        CbOutputBuffer[((i*imgWidth)/2) + (j/2)]=248;
        CrOutputBuffer[((i*imgWidth)/2) + (j/2)]=8;
	}

	i=startPoint.x;
	for(j=temp_min ; j<temp1 ; j++)
	{
		ybuffer[i*imgWidth + j] = 16;
		CbOutputBuffer[((i*imgWidth)/2) + (j/2)]=248;
	    CrOutputBuffer[((i*imgWidth)/2) + (j/2)]=8;
	}

	i=temp;
	for(j=temp_min ; j<temp1 ; j++)
	{
		ybuffer[i*imgWidth + j] = 16;
		CbOutputBuffer[((i*imgWidth)/2) + (j/2)]=248;
		CrOutputBuffer[((i*imgWidth)/2) + (j/2)]=8;
	}

	 j=temp1;
	 for(i=startPoint.x ; i<temp ; i++)
	 {
		 ybuffer[i*imgWidth + j] = 16;
		 CbOutputBuffer[((i*imgWidth)/2) + (j/2)]=248;
		 CrOutputBuffer[((i*imgWidth)/2) + (j/2)]=8;
	 }
}

void fastflooding(int32 i,int32 j, uint8 *YOutputBuffer, uint32 imgHeight, uint32 imgWidth, uint8 *CbOutputBuffer, uint8 *CrOutputBuffer, uint32 yval,uint32 cbval,uint32 crval)
{
	uint8 m;
	for(m=0 ; m<8 ; m++)
	{
		if(YOutputBuffer[((i+connect[0][m])*imgWidth) + (j+connect[1][m])]==255)
		{
			s.count++;
			s.RCList[s.count][0]=connect[0][m]+i;
			s.RCList[s.count][1]=j+connect[1][m];

			top++;
			pixel[top][0]=i+connect[0][m];
			pixel[top][1]=j+connect[1][m];

			YOutputBuffer[((i+connect[0][m])*imgWidth) + (j+connect[1][m])]=yval;
			CbOutputBuffer[(((i+connect[0][m])*imgWidth)/2) + ((j+connect[1][m])/2)]=cbval;
			CrOutputBuffer[(((i+connect[0][m])*imgWidth)/2) + ((j+connect[1][m])/2)]=crval;

		}
		else;
	}
}

void zigzag (uint8 *YInputBuffer, uint8 *YOutputBuffer, uint32 imgHeight, uint32 imgWidth, uint8 *CbOutputBuffer, uint8 *CrOutputBuffer, uint32 yval,uint32 cbval,uint32 crval)
{
	s.count=0;
	id=-1;
	for(i=140 ; i<imgHeight-10 ; i++)
	  {
		  for(j=10 ; j<imgWidth-10; j++)
		  {
			  if(YOutputBuffer[i*imgWidth + j]==255)
			  {
	              id++;

	              yval=ycbcr[id%9][0];
	              cbval=ycbcr[id%9][1];
	              crval=ycbcr[id%9][2];

				  s.count++;
				  s.RCList[s.count][0]=i;
				  s.RCList[s.count][1]=j;

				  top++;
				  pixel[top][0]=i;
				  pixel[top][1]=j;

				  YOutputBuffer[i*imgWidth + j]=yval;
				  CbOutputBuffer[((i*imgWidth)/2) + j/2]=cbval;
				  CrOutputBuffer[((i*imgWidth)/2) + j/2]=crval;

				   while(top!=0)
				   {
					   fastflooding(i,j ,YOutputBuffer , imgHeight, imgWidth, CbOutputBuffer, CrOutputBuffer, yval, cbval, crval);

					   i=pixel[top][0];
					   j=pixel[top][1];
					   top--;
				   }

			  }
		  }
	  }

}

void dataProcessing(uint8 *YInputBuffer, uint8 *YOutputBuffer, uint8 *CbOutputBuffer, uint8 *CrOutputBuffer, uint32 imgHeight, uint32 imgWidth) {
	// put your code here...
	// for the template, we make a copy of the inputBuffer to the outputImage
	uint32 temp1=0;
	memset(CbOutputBuffer,128,(sizeof(uint8)*imgHeight*imgWidth)/2);
	memset(CrOutputBuffer,128,(sizeof(uint8)*imgHeight*imgWidth)/2);

	connect[0][0]=-1;
	connect[0][1]=-1;
	connect[0][2]=-1;
	connect[0][3]=0;
	connect[0][4]=1;
	connect[0][5]=1;
	connect[0][6]=1;
	connect[0][7]=0;

	connect[1][0]=-1;
	connect[1][1]=0;
	connect[1][2]=1;
	connect[1][3]=1;
	connect[1][4]=1;
	connect[1][5]=0;
	connect[1][6]=-1;
	connect[1][7]=-1;

	isEven=isOdd=isCorner=0;

	ycbcr[0][0]=104; ycbcr[0][1]=40; ycbcr[0][2]=8;

	ycbcr[1][0]=235; ycbcr[1][1]=184; ycbcr[1][2]=72;
	ycbcr[2][0]=191; ycbcr[2][1]=104; ycbcr[2][2]=152;
	ycbcr[3][0]=191; ycbcr[3][1]=24; ycbcr[3][2]=200;
	ycbcr[4][0]=16; ycbcr[4][1]=200; ycbcr[4][2]=232;
	ycbcr[5][0]=60; ycbcr[5][1]=40; ycbcr[5][2]=24;
	ycbcr[6][0]=147; ycbcr[6][1]=88; ycbcr[6][2]=232;
	ycbcr[7][0]=60; ycbcr[7][1]=200; ycbcr[7][2]=248;
	ycbcr[8][0]=104; ycbcr[8][1]=8; ycbcr[8][2]=8;
	ycbcr[9][0]=235; ycbcr[9][1]=72; ycbcr[9][2]=56;

	for(i=0 ; i<5000 ; i++)
	{
		s.boundaryList[i][0]=s.boundaryList[i][1]=0;
	}

	Threshold(YInputBuffer, YOutputBuffer, imgHeight,imgWidth, CbOutputBuffer, CrOutputBuffer);

    zigzag(YInputBuffer, YOutputBuffer, imgHeight,imgWidth, CbOutputBuffer,CrOutputBuffer, yval, cbval, crval);

    computeBoundaryList (YOutputBuffer,startPoint1,object, imgHeight,imgWidth ,CbOutputBuffer, CrOutputBuffer);

    computeBoundingBox (YOutputBuffer, CbOutputBuffer, CrOutputBuffer, object, imgHeight, imgWidth);

    temp1=length;

	//memcpy(YOutputBuffer,YInputBuffer,sizeof(uint8)*imgHeight*imgWidth);
	return;
}
/* --------------------------------------------------------------------------------
 _____  _____   ____   _____ ______  _____ _____   ______ _   _ _____
|  __ \|  __ \ / __ \ / ____|  ____|/ ____/ ____| |  ____| \ | |  __ \
| |__) | |__) | |  | | |    | |__  | (___| (___   | |__  |  \| | |  | |
|  ___/|  _  /| |  | | |    |  __|  \___ \\___ \  |  __| | . ` | |  | |
| |    | | \ \| |__| | |____| |____ ____) |___) | | |____| |\  | |__| |
|_|    |_|  \_\\____/ \_____|______|_____/_____/  |______|_| \_|_____/

   -------------------------------------------------------------------------------- */

