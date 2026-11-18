int force_write(int fd,unsigned char *buf,int sz) {
 int got=0,rd;

 while (sz > 0) {
  rd = write(fd,buf,sz);
  if (rd <= 0) break;
  got += rd;
  buf += rd;
  sz -= rd;
 }

 return got;
}