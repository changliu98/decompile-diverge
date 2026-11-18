int BGBDT_SndBTAC1C2_PredictSample_Pfn12(int p0, int p1, int p2,
 int c0, int c1, int c2, int w0, int w1)
{
 int p;
 p=(p0*4 +((p2+c0+c1+w1)*2)+p1+c0+w0);
 return((p+8)>>4);
}