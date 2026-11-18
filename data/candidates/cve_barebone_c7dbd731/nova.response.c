static void mt76_add_fragment(struct sk_buff *skb, struct ieee80211_hdr *hdr,
			     struct ieee80211_rx_stats *rx_stats,
			     unsigned int keyidx, unsigned char flags)
{
	struct ieee80211_rx_data *rx = (void *) rx_stats;
	struct ieee80211_hdr *hdr_tmp;
	unsigned int hdrlen;
	unsigned int iv_len;
	unsigned char *iv;
	unsigned char *data;

	
	hdrlen = ieee80211_hdrlen(hdr->frame_control);
	iv_len = ieee80211_get_hdrlen_from_rx(rx);

	iv = hdr->addr1;
	iv += hdrlen;
	iv_len -= hdrlen;

	data = hdr->addr2;

	
	hdr_tmp = (void *)hdr;
	memcpy(hdr_tmp, hdr, ieee80211_hdr_minlen(hdr->frame_control));

	if (flags & 1)
		hdr_tmp->frame_control = hdr->frame_control;
	else
		hdr_tmp->frame_control = 0;

	skb_copy_from_linear_data_offset(skb, -(int)sizeof(*hdr_tmp),
					 (u8 *)hdr_tmp, hdr_tmp->len);
}