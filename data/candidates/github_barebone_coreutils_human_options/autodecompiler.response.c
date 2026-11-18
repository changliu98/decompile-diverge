int human_options(char *buf, char *val, long *b_size)
{
 int ret;

 ret = humblock(buf, b_size, val);
 if (*b_size == 0) {
  *b_size = default_block_size();
  ret = 4;
 }
 return ret;
}