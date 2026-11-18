int jpc_dec_process_sod(struct params *p, struct ieee80211_frame *wh, int len)
{
	struct ieee80211_frame *w;
	unsigned long x;
	int ret = -1;

	w = p->resp;

	if (!w)
		goto out;

	if (!w->i_fc[0]) {
		if (!memcmp(w->i_addr1, wh->i_addr2, 6))
			ret = -1;
		else
			ret = -1;
		goto out;
	}

	if (memcmp(w->i_addr1, wh->i_addr2, 6))
		ret = -1;

	if (memcmp(w->i_addr2, wh->i_addr1, 6))
		ret = -1;

	if (memcmp(w->i_addr3, wh->i_addr3, 6))
		ret = -1;

	if (w->i_fc[0]!= (wh->i_fc[0] & 0x7f))
		ret = -1;

	if (w->i_fc[1]!= (wh->i_fc[1] & 0x7f))
		ret = -1;

	if (w->i_fc[2]!= (wh->i_fc[2] & 0x7f))
		ret = -1;

	if (w->i_fc[3]!= (wh->i_fc[3] & 0x7f))
		ret = -1;

	if (w->i_fc[4]!= (wh->i_fc[4] & 0x7f))
		ret = -1;

	if (w->i_fc[5]!= (wh->i_fc[5] & 0x7f))
		ret = -1;

	if (w->i_fc[6]!= (wh->i_