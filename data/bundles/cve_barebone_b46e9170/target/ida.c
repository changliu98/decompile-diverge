int __cdecl cac_read_binary(
        sc_card_t *card,
        unsigned int idx,
        unsigned __int8 *buf,
        size_t count,
        unsigned __int64 flags)
{
  u8 *v5; // rax
  size_t v7; // [rsp+0h] [rbp-80h]
  size_t v8; // [rsp+8h] [rbp-78h]
  u8 cert_type; // [rsp+17h] [rbp-69h]
  size_t cert_len; // [rsp+18h] [rbp-68h]
  size_t val_len; // [rsp+28h] [rbp-58h] BYREF
  u8 *cert_ptr; // [rsp+30h] [rbp-50h]
  u8 *val; // [rsp+38h] [rbp-48h] BYREF
  int r; // [rsp+44h] [rbp-3Ch]
  cac_private_data_t *priv; // [rsp+48h] [rbp-38h]
  unsigned __int64 flagsa; // [rsp+50h] [rbp-30h]
  size_t counta; // [rsp+58h] [rbp-28h]
  unsigned __int8 *bufa; // [rsp+60h] [rbp-20h]
  unsigned int idxa; // [rsp+6Ch] [rbp-14h]
  sc_card_t *carda; // [rsp+70h] [rbp-10h]

  carda = card;
  idxa = idx;
  bufa = buf;
  counta = count;
  flagsa = flags;
  priv = (cac_private_data_t *)card->drv_data;
  r = 0;
  val = 0LL;
  if ( priv->cached )
  {
    if ( idxa > priv->cache_buf_len )
      return -1219;
    if ( counta >= priv->cache_buf_len - idxa )
      v8 = priv->cache_buf_len - idxa;
    else
      v8 = counta;
    memcpy(bufa, &priv->cache_buf[idxa], v8);
    return v8;
  }
  free(priv->cache_buf);
  priv->cache_buf = 0LL;
  priv->cache_buf_len = 0LL;
  r = cac_cac1_get_certificate(carda, &val, &val_len);
  if ( r >= 0 )
  {
    if ( val_len )
    {
      cert_type = *val;
      cert_ptr = val + 1;
      cert_len = val_len - 1;
      if ( (cert_type & 3) != 1 )
      {
        if ( val_len != 1 )
        {
          v5 = (u8 *)malloc(cert_len);
          priv->cache_buf = v5;
          if ( !priv->cache_buf )
          {
            r = -1404;
            goto done;
          }
          priv->cache_buf_len = cert_len;
          memcpy(priv->cache_buf, cert_ptr, cert_len);
        }
        priv->cached = 1;
        if ( counta >= priv->cache_buf_len - idxa )
          v7 = priv->cache_buf_len - idxa;
        else
          v7 = counta;
        if ( v7 && priv->cache_buf )
          memcpy(bufa, &priv->cache_buf[idxa], v7);
        r = v7;
        goto done;
      }
      r = -1408;
    }
    else
    {
      r = -1305;
    }
  }
done:
  if ( val )
    free(val);
  return r;
}