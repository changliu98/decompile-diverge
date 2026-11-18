char * ft_strcpy(char *dst,char *src)

{
  char cVar1;
  char *pcVar2;
  char *return_value;
  char *src_local;
  char *dst_local;
  
  src_local = src;
  dst_local = dst;
  do {
    cVar1 = *src_local;
    pcVar2 = dst_local + 1;
    *dst_local = cVar1;
    src_local = src_local + 1;
    dst_local = pcVar2;
  } while (cVar1 != '\0');
  *pcVar2 = '\0';
  return dst;
}