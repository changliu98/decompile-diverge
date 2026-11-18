int par_msquares_multi_code(int sw, int se, int ne, int nw)
{
  int code = 0;
  int code_se = 0; int code_ne = 0; int code_nw = 0;
  int ncols = 1;
  if (se != sw) {
    ncols++;
    code_se = 1;
  }
  if (ne != se) {
    if (ne != sw) {
      code_ne = ncols++;
    }
    else {
      code_ne = code_se;
    }
  }
  else {
    code_ne = code_se;
  }
  if (nw == ne) {
    code_nw = code_ne;
  }
  else if (nw == se) {
    code_nw = code_se;
  }
  else if (nw == sw) {
    code_nw = 0;
  }
  else {
    code_nw = ncols;
  }
  return (code_nw << 6 | code_ne << 4 | code_se << 2);
}