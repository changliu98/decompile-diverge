int par_msquares_multi_code(int sw, int se, int ne, int nw)
{
 int code[4];
 int ncols = 1;

 code[1] = (se != sw);
 if (code[1])
  ncols++;

 if (ne == se)
  code[2] = code[1];
 else if (ne == sw)
  code[2] = 0;
 else {
  code[2] = ncols;
  ncols++;
 }

 if (nw == ne)
  code[3] = code[2];
 else if (nw == se)
  code[3] = code[1];
 else if (nw == sw)
  code[3] = 0;
 else
  code[3] = ncols;

 return (code[1] << 2) | (code[2] << 4) | (code[3] << 6);
}