void decode_dir(short d,int*x,int*y){
*x=(d&0xFF)-2;
*y=((d&0xFF00)>>8)-2;
}