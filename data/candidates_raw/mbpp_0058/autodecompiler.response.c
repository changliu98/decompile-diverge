int BTLZA_BitStream_SameBits(int v1,int v2)
{
 return(((v1^v2)<0)?1:0);
}