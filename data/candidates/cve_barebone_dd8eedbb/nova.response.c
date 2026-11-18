int mwifiex_cmd_append_vsie_tlv(struct nlattr *nla[], unsigned short family,
		      struct nlattr **tb)
{
	int i, totlen = 0;

	if (!tb)
		return 0;

	if (!tb[0])
		goto out;

	for (i = 0; i < 9; i++) {
		if (nla[i] & family) {
			struct nlattr *est = tb[0];

			est->nla_len = sizeof(*est);
			est->nla_len += nla[i]->nla_len;
			memcpy(est+1, nla[i]+1, est->nla_len);
			tb[0] = (struct nlattr *)((char *)est + est->nla_len);
			totlen += est->nla_len;
		}
	}
out:
	return totlen;
}