int xiph_len(int l)

{
  int l_local;
  
  return l / 0xff + 1 + l;
}