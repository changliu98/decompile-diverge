/* WARNING: Removing unreachable block (ram,0x00101600) */

int cac_read_binary(sc_card_t *card,uint idx,uchar *buf,size_t count,unsigned_long flags)

{
  size_t __size;
  u8 *puVar1;
  size_t local_88;
  size_t local_80;
  u8 cert_type;
  size_t cert_len;
  size_t len;
  size_t val_len;
  u8 *cert_ptr;
  u8 *val;
  int r;
  cac_private_data_t *priv;
  unsigned_long flags_local;
  size_t count_local;
  uchar *buf_local;
  uint idx_local;
  sc_card_t *card_local;
  
  priv = card->drv_data;
  r = 0;
  val = (u8 *)0x0;
  flags_local = flags;
  count_local = count;
  buf_local = buf;
  idx_local = idx;
  card_local = card;
  if (priv->cached != 0) {
    if (priv->cache_buf_len < (ulong)idx) {
      return -0x4c3;
    }
    local_80 = count;
    if (priv->cache_buf_len - (ulong)idx <= count) {
      local_80 = priv->cache_buf_len - (ulong)idx;
    }
    memcpy(buf,priv->cache_buf + idx,local_80);
    return (int)local_80;
  }
  free(priv->cache_buf);
  priv->cache_buf = (u8 *)0x0;
  priv->cache_buf_len = 0;
  r = cac_cac1_get_certificate(card_local,&val,&val_len);
  if (-1 < r) {
    if (val_len == 0) {
      r = -0x519;
    }
    else {
      cert_ptr = val + 1;
      __size = val_len - 1;
      if ((*val & 3) == 1) {
        r = -0x580;
      }
      else {
        if (__size != 0) {
          puVar1 = malloc(__size);
          priv->cache_buf = puVar1;
          if (priv->cache_buf == (u8 *)0x0) {
            r = -0x57c;
            goto LAB_001016e9;
          }
          priv->cache_buf_len = __size;
          memcpy(priv->cache_buf,cert_ptr,__size);
        }
        priv->cached = 1;
        if (count_local < priv->cache_buf_len - (ulong)idx_local) {
          local_88 = count_local;
        }
        else {
          local_88 = priv->cache_buf_len - (ulong)idx_local;
        }
        if ((local_88 != 0) && (priv->cache_buf != (u8 *)0x0)) {
          memcpy(buf_local,priv->cache_buf + idx_local,local_88);
        }
        r = (int)local_88;
      }
    }
  }
LAB_001016e9:
  if (val != (u8 *)0x0) {
    free(val);
  }
  return r;
}