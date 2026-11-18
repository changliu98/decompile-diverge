static inline short popPriorityQueue(struct ks_wlan_private *priv,
					    unsigned char *p)
{
	short ret;

	ret = (short)*(__le16 *)p;
	priv->count_rpt_event--;

	return ret;
}