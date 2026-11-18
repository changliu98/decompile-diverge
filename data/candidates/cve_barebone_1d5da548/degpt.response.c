pyc_object * get_complex_object(RzBinPycObj *pyc,RzBuffer *buffer)

{
  byte bVar1;
  uchar *out;
  longlong lVar2;
  uchar *out_00;
  char *pcVar3;
  uchar *s2;
  uchar *s1;
  uint n2;
  uint n1;
  uint size;
  _Bool error;
  pyc_object *ret;
  RzBuffer *buffer_local;
  RzBinPycObj *pyc_local;
  pyc_object *local_10;
  
  ret = (pyc_object *)0x0;
  error = false;
  buffer_local = buffer;
  pyc_local = pyc;
  ret = calloc(1,0x10);
  if (ret == (pyc_object *)0x0) {
    local_10 = (pyc_object *)0x0;
  }
  else {
    if ((pyc_local->magic_int & 0xffff) < 0xf26e) {
      bVar1 = get_ut8(buffer_local,&error);
      n1 = (uint)bVar1;
    }
    else {
      n1 = get_st32(buffer_local,&error);
    }
    if ((error & 1U) == 0) {
      out = malloc((ulong)(n1 + 1));
      if (out == (uchar *)0x0) {
        local_10 = (pyc_object *)0x0;
      }
      else {
        lVar2 = rz_buf_read(buffer_local,out,(ulong)n1);
        if ((uint)lVar2 == n1) {
          out[n1] = '\0';
          if ((pyc_local->magic_int & 0xffff) < 0xf26e) {
            bVar1 = get_ut8(buffer_local,&error);
            n2 = (uint)bVar1;
          }
          else {
            n2 = get_st32(buffer_local,&error);
          }
          if ((error & 1U) == 0) {
            out_00 = malloc((ulong)(n2 + 1));
            if (out_00 == (uchar *)0x0) {
              local_10 = (pyc_object *)0x0;
            }
            else {
              lVar2 = rz_buf_read(buffer_local,out_00,(ulong)n2);
              if ((uint)lVar2 == n2) {
                out_00[n2] = '\0';
                ret->type = TYPE_COMPLEX;
                pcVar3 = rz_str_newf("%s+%sj",out,out_00);
                ret->data = pcVar3;
                free(out);
                free(out_00);
                if (ret->data == (void *)0x0) {
                  free(ret);
                  local_10 = (pyc_object *)0x0;
                }
                else {
                  local_10 = ret;
                }
              }
              else {
                free(out);
                free(out_00);
                free(ret);
                local_10 = (pyc_object *)0x0;
              }
            }
          }
          else {
            local_10 = (pyc_object *)0x0;
          }
        }
        else {
          free(out);
          free(ret);
          local_10 = (pyc_object *)0x0;
        }
      }
    }
    else {
      free(ret);
      local_10 = (pyc_object *)0x0;
    }
  }
  return local_10;
}