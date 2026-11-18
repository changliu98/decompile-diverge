int cac_read_binary(sc_card_t *card, unsigned idx, unsigned char *buf,
      size_t count, unsigned long flags)
{
 int r;
 size_t cert_len, len;
 uchar *cert;
 cac_private_data_t *priv = card->drv_data;

 if (priv->cached) {
  if (idx > priv->cache_buf_len)
   return -1219;
  len = ((count) < (priv->cache_buf_len - idx) ? (count) : (priv->cache_buf_len - idx));
  memcpy(buf, priv->cache_buf + idx, len);
  return len;
 }

 free(priv->cache_buf);
 priv->cache_buf = NULL;
 priv->cache_buf_len = 0;

 r = cac_cac1_get_certificate(card, &cert, &cert_len);
 if (r < 0)
  goto out;

 if (cert_len == 0) {
  r = -1305;
  goto out;
 }

 cert_len--;
 cert++;

 if ((cert[-1] & 0x03) == 0x01) {
  r = -1408;
  goto out;
 }

 if (cert_len > 0) {
  priv->cache_buf = malloc(cert_len);
  if (priv->cache_buf == NULL) {
   r = -1404;
   goto out;
  }
  priv->cache_buf_len = cert_len;
  memcpy(priv->cache_buf, cert, cert_len);
 }

 priv->cached = 1;

 len = ((count) < (priv->cache_buf_len - idx) ? (count) : (priv->cache_buf_len - idx));
 if (len > 0 && priv->cache_buf != NULL)
  memcpy(buf, priv->cache_buf + idx, len);

 r = len;

out:
 if (cert != NULL)
  free(cert);

 return r;
}