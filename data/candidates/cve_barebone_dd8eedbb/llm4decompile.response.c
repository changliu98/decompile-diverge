int
mwifiex_cmd_append_vsie_tlv(struct mwifiex_private *priv, u16 vsie_mask,
			     u8 **buffer)
{
	int ret_len = 0;
	u8 *tlv;
	u16 tlv_len;
	int i;

	if (!buffer || !*buffer)
		return 0;

	for (i = 0; i < 8; i++) {
		if (priv->vs_ie[i].mask & vsie_mask) {
			tlv = *buffer;
			tlv[0] = 0x0a;
			tlv[1] = 0x01;
			tlv_len = priv->vs_ie[i].ie[1] + 2;
			tlv[2] = (u8)(tlv_len & 0xff);
			tlv[3] = (u8)((tlv_len & 0xff00) >> 8);
			memcpy(&tlv[4], priv->vs_ie[i].ie, tlv_len);
			*buffer += tlv_len + 4;
			ret_len += tlv_len + 4;
		}
	}

	return ret_len;
}