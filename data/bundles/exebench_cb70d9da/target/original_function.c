void BTIC2D_TransDCT_Vert(int *iblk, int *oblk)
{
 int ib0, ib1, ib2, ib3, ib4, ib5, ib6, ib7;
 int ob0, ob1, ob2, ob3, ob4, ob5, ob6, ob7;
 int ib0p7, ib1p6, ib2p5, ib3p4;
 int ib0n7, ib1n6, ib2n5, ib3n4;
 int ib0p7n3n4, ib1p6n2n5;

 ib0=iblk[ 0]; ib1=iblk[ 8];
 ib2=iblk[16]; ib3=iblk[24];
 ib4=iblk[32]; ib5=iblk[40];
 ib6=iblk[48]; ib7=iblk[56];

 ib0p7=ib0+ib7; ib1p6=ib1+ib6;
 ib2p5=ib2+ib5; ib3p4=ib3+ib4;
 ib0n7=ib0-ib7; ib1n6=ib1-ib6;
 ib2n5=ib2-ib5; ib3n4=ib3-ib4;

 ob0=(ib0p7+ib1p6+ib2p5+ib3p4)*91;
 ob4=(ib0p7-ib1p6-ib2p5+ib3p4)*91;

 ib0p7n3n4=ib0p7-ib3p4;
 ib1p6n2n5=ib1p6-ib2p5;
 ob2=ib0p7n3n4*118 +ib1p6n2n5* 49;
 ob6=ib0p7n3n4* 49 -ib1p6n2n5*118;

 ob1=ib0n7*126 +ib1n6*106 +ib2n5* 71 +ib3n4* 25;
 ob3=ib0n7*106 -ib1n6* 25 -ib2n5*126 -ib3n4* 71;
 ob5=ib0n7* 71 -ib1n6*126 +ib2n5* 25 +ib3n4*106;
 ob7=ib0n7* 25 -ib1n6* 71 +ib2n5*106 -ib3n4*126;

 oblk[ 0]=(ob0+32768)>>16; oblk[ 8]=(ob1+32768)>>16;
 oblk[16]=(ob2+32768)>>16; oblk[24]=(ob3+32768)>>16;
 oblk[32]=(ob4+32768)>>16; oblk[40]=(ob5+32768)>>16;
 oblk[48]=(ob6+32768)>>16; oblk[56]=(ob7+32768)>>16;
}