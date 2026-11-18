void af_filter_bilinear(float yl[], float yr[], float c, float dyy[], float dyc[])
{
 float c1,c2;

 c1=yl[2]*(4.0)*c*c+yl[1]*(2.0)*c*c+yl[0];
 c2=yr[2]*(4.0)*c*c+yr[1]*(2.0)*c*c+yr[0];
 *dyc *= c1/c2;
 *(dyc++) = (2.0*yr[0]+(8.0*yr[2]*c*c)) / c2;
 *(dyc++) = ((4.0*yr[2]*c*c)+(2.0*yr[1]*c*c)+yr[0]) / c2;
 *(dyc++) = (2.0*yl[0]+(8.0*yl[2]*c*c)) / c1;
 *dyc = ((4.0*yl[2]*c*c)+(2.0*yl[1]*c*c)+yl[0]) / c1;
}