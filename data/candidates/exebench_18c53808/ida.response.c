void __cdecl gui_combine_scissor(int *dst, int *src)
{
  int v2; // [rsp+0h] [rbp-48h]
  int v3; // [rsp+4h] [rbp-44h]
  int v4; // [rsp+8h] [rbp-40h]
  int v5; // [rsp+Ch] [rbp-3Ch]

  if ( src )
  {
    if ( *dst <= *src )
      v5 = *src;
    else
      v5 = *dst;
    if ( dst[1] <= src[1] )
      v4 = src[1];
    else
      v4 = dst[1];
    if ( dst[2] + *dst >= src[2] + *src )
      v3 = src[2] + *src;
    else
      v3 = dst[2] + *dst;
    if ( dst[3] + dst[1] >= src[3] + src[1] )
      v2 = src[3] + src[1];
    else
      v2 = dst[3] + dst[1];
    *dst = v5;
    dst[1] = v4;
    dst[2] = v3 - v5;
    dst[3] = v2 - v4;
  }
}