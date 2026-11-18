int __cdecl mwifiex_cmd_append_vsie_tlv(mwifiex_private *priv, u16 vsie_mask, u8 **buffer)
{
  u8 *vs_param_set; // [rsp+0h] [rbp-30h]
  int ret_len; // [rsp+8h] [rbp-28h]
  int id; // [rsp+Ch] [rbp-24h]

  ret_len = 0;
  if ( !buffer )
    return 0;
  if ( !*buffer )
    return 0;
  for ( id = 0; id < 8; ++id )
  {
    if ( (vsie_mask & priv->vs_ie[id].mask) != 0 )
    {
      vs_param_set = *buffer;
      *(_WORD *)vs_param_set = 266;
      *((_WORD *)vs_param_set + 1) = priv->vs_ie[id].ie[1] + 2;
      memcpy(vs_param_set + 4, priv->vs_ie[id].ie, *((unsigned __int16 *)vs_param_set + 1));
      *buffer += *((unsigned __int16 *)vs_param_set + 1) + 4;
      ret_len += *((unsigned __int16 *)vs_param_set + 1) + 4;
    }
  }
  return ret_len;
}