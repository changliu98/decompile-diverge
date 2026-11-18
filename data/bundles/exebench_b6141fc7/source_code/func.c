#include <stdio.h>

void R16SRFFT(float input[16],float output[16] ) {
  float temp, out0, out1, out2, out3, out4, out5, out6, out7, out8;
  float out9,out10,out11,out12,out13,out14,out15;

  out0=input[0]+input[8];
  out1=input[1]+input[9];
  out2=input[2]+input[10];
  out3=input[3]+input[11];
  out4=input[4]+input[12];
  out5=input[5]+input[13];
  out6=input[6]+input[14];
  out7=input[7]+input[15];



  out8=input[0]-input[8];
  out9=input[1]-input[9];
  out10=input[2]-input[10];
  out11=input[3]-input[11];
  out12=input[12]-input[4];
  out13=input[13]-input[5];
  out14=input[14]-input[6];
  out15=input[15]-input[7];
# 78 "fft.c"
  temp=(out13-out9)*(0.38268343236508978);
  out9=out9*(1.30656296487637660)+temp;
  out13=out13*(0.54119610014619690)+temp;

  out14*=(0.707106781186547460);
  out10*=(0.707106781186547460);
  out14=out14-out10;
  out10=out14+out10+out10;

  temp=(out15-out11)*(0.923879532511286740);
  out11=out11*(1.3065629648763766)+temp;
  out15=out15*(-0.54119610014619690)+temp;




  out8+=out10;
  out10=out8-out10-out10;

  out12+=out14;
  out14=out12-out14-out14;

  out9+=out11;
  out11=out9-out11-out11;

  out13+=out15;
  out15=out13-out15-out15;


  output[1]=out8+out9;
  output[7]=out8-out9;

  output[9]=out12+out13;
  output[15]=out13-out12;

  output[5]=out10+out15;
  output[13]=out14-out11;
  output[3]=out10-out15;
  output[11]=-out14-out11;
# 125 "fft.c"
  out0=out0+out4;
  out4=out0-out4-out4;
  out1=out1+out5;
  out5=out1-out5-out5;
  out2+=out6;
  out6=out2-out6-out6;
  out3+=out7;
  out7=out3-out7-out7;



  output[0]=out0+out2;
  output[4]=out0-out2;
  out1+=out3;
  output[12]=out3+out3-out1;

  output[0]+=out1;
  output[8]=output[0]-out1-out1;





  out5*=0.707106781186547460;
  out7*=0.707106781186547460;
  out5=out5-out7;
  out7=out5+out7+out7;

  output[14]=out6-out7;
  output[2]=out5+out4;
  output[6]=out4-out5;
  output[10]=-out7-out6;

}
