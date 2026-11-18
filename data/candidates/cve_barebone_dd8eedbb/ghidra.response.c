int mwifiex_cmd_append_vsie_tlv(mwifiex_private *priv,u16 vsie_mask,u8 **buffer)

{
  u8 *puVar1;
  mwifiex_ie_types_vendor_param_set *vs_param_set;
  int ret_len;
  int id;
  u8 **buffer_local;
  u16 vsie_mask_local;
  mwifiex_private *priv_local;
  int local_c;
  
  ret_len = 0;
  if (buffer == (u8 **)0x0) {
    local_c = 0;
  }
  else if (*buffer == (u8 *)0x0) {
    local_c = 0;
  }
  else {
    for (id = 0; id < 8; id = id + 1) {
      if ((priv->vs_ie[id].mask & vsie_mask) != 0) {
        puVar1 = *buffer;
        puVar1[0] = '\n';
        puVar1[1] = '\x01';
        *(ushort *)(puVar1 + 2) = priv->vs_ie[id].ie[1] + 2;
        memcpy(puVar1 + 4,priv->vs_ie[id].ie,(ulong)*(ushort *)(puVar1 + 2));
        *buffer = *buffer + (ulong)*(ushort *)(puVar1 + 2) + 4;
        ret_len = ret_len + *(ushort *)(puVar1 + 2) + 4;
      }
    }
    local_c = ret_len;
  }
  return local_c;
}