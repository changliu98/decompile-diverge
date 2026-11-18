static int read_double(int fd,double *out)
{
 double d;
 int err;

 err=read(fd,&d,sizeof(d));
 *out=d;
do { } while(0);
 return err;
}