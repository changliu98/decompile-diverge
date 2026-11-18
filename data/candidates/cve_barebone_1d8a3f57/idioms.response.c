int stszin(int size)
{
  int i; int len; int offset;
  read_int();
  read_int();
  len = read_int();
  if ( (qword_40A8 = (unsigned int *)read_data(len * sizeof(int))) == ((void *)0))
    return -1;
  offset = 0;
  qword_40A8[0] = 0;
  for (i = 0; i < len; i++)
  {
    int l = read_int();
    offset += l;
    if (dword_40B8 < l)
      dword_40B8 = l;
    qword_40A8[i + 1] = offset;
    if (offset < qword_40A8[i])
      return -1;
  }
  return size;
}