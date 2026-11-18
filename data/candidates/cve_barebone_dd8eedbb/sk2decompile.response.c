int mwifiex_cmd_append_vsie_tlv(struct mwifiex_private *priv, u8 vsie_type,
                                u8 **tlv) {
  struct mwifiex_ie_types_header *tlv_hdr;
  int i, len = 0;
  if (!tlv || !(*tlv)) return 0;
  for (i = 0; i < 8; i++) {
    if (priv->vsie[i].type & vsie_type) {
      tlv_hdr = (struct mwifiex_ie_types_header *)*tlv;
      tlv_hdr->element_id = 0x010a;
      tlv_hdr->length = priv->vsie[i].len + 2;
      memcpy(((u8 *)tlv_hdr) + 4, priv->vsie[i].data, tlv_hdr->length);
      *tlv += tlv_hdr->length + 4;
      len += tlv_hdr->length + 4;
    }
  }
  return len;
}