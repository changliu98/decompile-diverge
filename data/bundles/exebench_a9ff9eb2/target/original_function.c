void ltox(unsigned int value,char* str){
 int i = 0;
 char tab[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
 for(i = 0;i < 8;i++){
  str[9-i] = tab[value & 0xf];
  value >>= 4;
 }
 str[0] = '0';
 str[1] = 'x';
 str[10] = '\n';
 str[11] = '\0';
}