struct pyc_object *get_complex_object(struct RzBinPycObj *pyc, struct RzBuffer *buffer)
{
  struct pyc_object *ret = ((void *)0);
  unsigned int len1;
  unsigned int len2;
  char *str1 = ((void *)0);
  char *str2 = ((void *)0);
  unsigned char *data1 = ((void *)0);
  unsigned char *data2 = ((void *)0);
  int error = 0;
  ret = (struct pyc_object *)calloc(1, sizeof(pyc_object));
  if (ret == ((void *)0))
    return ((void *)0);
  if (pyc->magic_int < 0xf26e)
    len1 = get_ut8(buffer, &error);
  else
    len1 = get_st32(buffer, &error);
  if (error)
  {
    free(ret);
    return ((void *)0);
  }
  str1 = (char *)malloc(len1 + 1);
  if (str1 == ((void *)0))
    return ((void *)0);
  if (rz_buf_read(buffer, str1, len1) != len1)
  {
    free(str1);
    free(ret);
    ret = ((void *)0);
    return ((void *)0);
  }
  str1[len1] = '\0';
  if (pyc->magic_int < 0xf26e)
    len2 = get_ut8(buffer, &error);
  else
    len2 = get_st32(buffer, &error);
  if (error)
    return ((void *)0);
  str2 = (char *)malloc(len2 + 1);
  if (str2 == ((void *)0))
    return ((void *)0);
  if (rz_buf_read(buffer, str2, len2) != len2)
  {
    free(str1);
    free(str2);
    free(ret);
    ret = ((void *)0);
    return ((void *)0);
  }
  str2[len2] = '\0';
  ret->type = TYPE_COMPLEX;
  ret->data = rz_str_newf("%s+%sj", str1, str2);
  free(str1);
  free(str2);
  if (ret->data == ((void *)0))
  {
    free(ret);
    ret = ((void *)0);
    return ((void *)0);
  }
  return ret;
}