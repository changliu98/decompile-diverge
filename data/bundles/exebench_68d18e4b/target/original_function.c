void SwitchToChar(char* str,unsigned char data)
{
 if(data/16>=10){
 *str = 'A'+data/16-10;
 }else{
 *str = '0'+data/16;
 }

  if(data%16>=10){
    *(str+1) = 'A'+data%16-10;
  }else{
   *(str+1) = '0'+data%16;
  }
}