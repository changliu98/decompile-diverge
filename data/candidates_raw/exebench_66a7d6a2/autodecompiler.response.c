void swap64(void *v)
{
 unsigned int *i = (unsigned int *) v;
 unsigned int t = ((i[0] & 0xff) << 24) | ((i[0] & 0xff00) << 8) | ((i[0] & 0xff0000) >> 8) | ((i[0] & 0xff000000) >> 24);
 i[0] = ((i[1] & 0xff) << 24) | ((i[1] & 0xff00) << 8) | ((i[1] & 0xff0000) >> 8) | ((i[1] & 0xff000000) >> 24);
 i[1] = t;
}