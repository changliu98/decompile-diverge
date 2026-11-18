void ee_readn(unsigned int command_ee,unsigned int result_ee[]){
 if(command_ee>((0x0003FFFF +1-0x00038000)/0x100)){
  result_ee[0]=502;}
 else{
  result_ee[0]=0;
  result_ee[1]=(unsigned int)(0x00038000 +0x100*command_ee);
 }
 return;
}