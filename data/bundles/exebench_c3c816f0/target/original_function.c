int char2num(char c, char *pNum)
{
 int ret = 0;

 if(('0' <= c) && (c <= '9')){
  *pNum = c - '0';
 }else if(('A' <= c) && (c <= 'F')){
  *pNum = c - 'A' + 10;
 }else if(('a' <= c) && (c <= 'f')){
  *pNum = c - 'a' + 10;
 }else{
  ret = -1;
 }

 return ret;
}