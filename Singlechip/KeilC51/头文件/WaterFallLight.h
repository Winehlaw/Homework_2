#include<reg51.h>
#include<intrins.h>
#define uint unsigned int
#define uchar unsigned char 
void delay(){   
uint i,j;
for(i=0;i<1000;i++)
for(j=0;j<50;j++)
;
}
void leftrl()
{
uint i,j;
P2=0xff;
for(i=0;i<8;i++){
P2=P2<<1;
delay();
}
P2=0xff;
for(j=0;j<8;j++)
{
P2=P2>>1;
delay();
}
}
void leftlr1(){
uint i,j;
P2=0xfe;
for(i=0;i<7;i++){
P2=_crol_(P2,1);
delay();
}
for(j=0;j<7;j++){
P2=_cror_(P2,1);
delay();
}
}
void array1(){
uchar arr[]={0x00,0x80,0xc0,0xe0,0xf0,0xf8,0xfc,0xfe,0xff};
uint i,j;
for(i=0;i<9;i++){
P2=arr[i];
delay();
}
for(j=9;j>0;j--){
P2=arr[j];
delay();
}
}
 