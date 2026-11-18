int __cdecl xpm_decode_frame(AVCodecContext *avctx, void *data, int *got_frame, AVPacket *avpkt)
{
  int v4; // eax
  uint32_t *v5; // rax
  bool v7; // [rsp+3h] [rbp-7Dh]
  int len; // [rsp+4h] [rbp-7Ch]
  const uint8_t *index; // [rsp+8h] [rbp-78h]
  uint32_t *dst; // [rsp+10h] [rbp-70h]
  int64_t size; // [rsp+18h] [rbp-68h]
  int j; // [rsp+24h] [rbp-5Ch]
  int i; // [rsp+28h] [rbp-58h]
  int ia; // [rsp+28h] [rbp-58h]
  int ib; // [rsp+28h] [rbp-58h]
  int ret; // [rsp+2Ch] [rbp-54h]
  int reta; // [rsp+2Ch] [rbp-54h]
  int retb; // [rsp+2Ch] [rbp-54h]
  int cpp; // [rsp+30h] [rbp-50h]
  int ncolors; // [rsp+34h] [rbp-4Ch]
  uint8_t *ptr; // [rsp+38h] [rbp-48h]
  const char *ptra; // [rsp+38h] [rbp-48h]
  const char *ptrb; // [rsp+38h] [rbp-48h]
  const uint8_t *ptrc; // [rsp+38h] [rbp-48h]
  char *ptrd; // [rsp+38h] [rbp-48h]
  const char *ptre; // [rsp+38h] [rbp-48h]
  const uint8_t *ptrf; // [rsp+38h] [rbp-48h]
  const uint8_t *end; // [rsp+40h] [rbp-40h]
  XPMDecContext *x; // [rsp+50h] [rbp-30h]

  x = (XPMDecContext *)avctx->priv_data;
  ptr = avpkt->data;
  avctx->pix_fmt = 1;
  end = &avpkt->data[avpkt->size];
  while ( 1 )
  {
    v7 = 0;
    if ( memcmp(ptr, "/* XPM */", 9uLL) )
      v7 = ptr < end - 9;
    if ( !v7 )
      break;
    ++ptr;
  }
  if ( ptr < end )
  {
    ptra = (const char *)&ptr[mod_strcspn((const char *)ptr, "\"")];
    if ( (unsigned int)__isoc99_sscanf() == 4 )
    {
      ret = ff_set_dimensions(avctx, avctx->width, avctx->height);
      if ( ret >= 0 )
      {
        reta = ff_get_buffer(avctx, (AVFrame *)data, 0);
        if ( reta >= 0 )
        {
          if ( cpp > 0 && cpp < 5 )
          {
            size = 1LL;
            for ( i = 0; i < cpp; ++i )
              size *= 94LL;
            if ( ncolors > 0 && ncolors <= size )
            {
              av_fast_padded_malloc(x, &x->pixels_size, 4 * size);
              if ( x->pixels )
              {
                ptrb = &ptra[mod_strcspn(ptra, ",") + 1];
                for ( ia = 0; ia < ncolors; ++ia )
                {
                  ptrc = (const uint8_t *)&ptrb[mod_strcspn(ptrb, "\"") + 1];
                  if ( &ptrc[cpp] > end )
                    return -1094995529;
                  index = ptrc;
                  ptrd = strstr((const char *)&ptrc[cpp], "c ");
                  if ( !ptrd )
                    return -1094995529;
                  ptre = ptrd + 2;
                  len = strcspn(ptre, "\" ");
                  v4 = ascii2index(index, cpp);
                  if ( v4 < 0 )
                    return v4;
                  x->pixels[v4] = color_string_to_rgba(ptre, len);
                  ptrb = &ptre[mod_strcspn(ptre, ",") + 1];
                }
                for ( ib = 0; ib < avctx->height; ++ib )
                {
                  dst = (uint32_t *)(*((_DWORD *)data + 16) * ib + *(_QWORD *)data);
                  ptrf = (const uint8_t *)&ptrb[mod_strcspn(ptrb, "\"") + 1];
                  for ( j = 0; j < avctx->width; ++j )
                  {
                    if ( &ptrf[cpp] > end )
                      return -1094995529;
                    retb = ascii2index(ptrf, cpp);
                    if ( retb < 0 )
                      return retb;
                    v5 = dst++;
                    *v5 = x->pixels[retb];
                    ptrf += cpp;
                  }
                  ptrb = (const char *)&ptrf[mod_strcspn((const char *)ptrf, ",") + 1];
                }
                *((_DWORD *)data + 24) = 1;
                *((_DWORD *)data + 25) = 1;
                *got_frame = 1;
                return avpkt->size;
              }
              else
              {
                return -12;
              }
            }
            else
            {
              av_log(avctx, 16, "invalid number of colors: %d\n", (unsigned int)ncolors);
              return -1094995529;
            }
          }
          else
          {
            av_log(avctx, 16, "unsupported/invalid number of chars per pixel: %d\n", (unsigned int)cpp);
            return -1094995529;
          }
        }
        else
        {
          return reta;
        }
      }
      else
      {
        return ret;
      }
    }
    else
    {
      av_log(avctx, 16, "missing image parameters\n");
      return -1094995529;
    }
  }
  else
  {
    av_log(avctx, 16, "missing signature\n");
    return -1094995529;
  }
}