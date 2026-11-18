int deo_pipe(int *rend,int *wend)

{
  int iVar1;
  int *piVar2;
  int in [2];
  int *wend_local;
  int *rend_local;
  int local_c;
  
  iVar1 = pipe(in);
  if (iVar1 == 0) {
    *rend = in[0];
    *wend = in[1];
    local_c = 0;
  }
  else {
    piVar2 = __errno_location();
    local_c = *piVar2;
  }
  return local_c;
}