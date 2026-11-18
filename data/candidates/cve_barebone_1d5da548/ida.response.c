pyc_object *__cdecl get_complex_object(RzBinPycObj *pyc, RzBuffer *buffer)
{
  char *v2; // rax
  unsigned __int8 *s2; // [rsp+0h] [rbp-40h]
  unsigned __int8 *s1; // [rsp+8h] [rbp-38h]
  unsigned int n2; // [rsp+10h] [rbp-30h]
  unsigned int n1; // [rsp+14h] [rbp-2Ch]
  bool error; // [rsp+1Fh] [rbp-21h] BYREF
  pyc_object *ret; // [rsp+20h] [rbp-20h]
  RzBuffer *buffera; // [rsp+28h] [rbp-18h]
  RzBinPycObj *pyca; // [rsp+30h] [rbp-10h]

  pyca = pyc;
  buffera = buffer;
  error = 0;
  ret = (pyc_object *)calloc(1uLL, 0x10uLL);
  if ( !ret )
    return 0LL;
  if ( (unsigned __int16)pyca->magic_int > 0xF26Du )
    n1 = get_st32(buffera, &error);
  else
    n1 = get_ut8(buffera, &error);
  if ( error )
  {
    free(ret);
    return 0LL;
  }
  else
  {
    s1 = (unsigned __int8 *)malloc(n1 + 1);
    if ( s1 )
    {
      if ( (unsigned int)rz_buf_read(buffera, s1, n1) == n1 )
      {
        s1[n1] = 0;
        if ( (unsigned __int16)pyca->magic_int > 0xF26Du )
          n2 = get_st32(buffera, &error);
        else
          n2 = get_ut8(buffera, &error);
        if ( error )
        {
          return 0LL;
        }
        else
        {
          s2 = (unsigned __int8 *)malloc(n2 + 1);
          if ( s2 )
          {
            if ( (unsigned int)rz_buf_read(buffera, s2, n2) == n2 )
            {
              s2[n2] = 0;
              ret->type = TYPE_COMPLEX;
              v2 = rz_str_newf("%s+%sj", (const char *)s1, (const char *)s2);
              ret->data = v2;
              free(s1);
              free(s2);
              if ( ret->data )
              {
                return ret;
              }
              else
              {
                free(ret);
                ret = 0LL;
                return 0LL;
              }
            }
            else
            {
              free(s1);
              free(s2);
              free(ret);
              ret = 0LL;
              return 0LL;
            }
          }
          else
          {
            return 0LL;
          }
        }
      }
      else
      {
        free(s1);
        free(ret);
        ret = 0LL;
        return 0LL;
      }
    }
    else
    {
      return 0LL;
    }
  }
}