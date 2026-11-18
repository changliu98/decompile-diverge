static int OS_file_open(file_t *file, char *filename)
{
 int ret;

 file->fd = open(filename, 0);
 if (file->fd == ((int)-1))
 {
  ret = 0x1004;
 }
 else
 {
  ret = 0x0000;
 }

 return ret;
}