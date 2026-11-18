void set_page_data(int val, char *buf)
{
  int *p = (int *)buf;
  *p = val;
}