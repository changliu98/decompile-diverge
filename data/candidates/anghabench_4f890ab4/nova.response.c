static inline u8 ff_norm_qscale(u8 agc, u8 sq)
{
	u8 idx;

	switch (sq) {
	case 0:
		idx = 0;
		break;
	case IEEE80211_CCK_SQ_MAX:
		idx = 15;
		break;
	case IEEE80211_OFDM_SQ_MAX:
		idx = 63;
		break;
	default:
		idx = (u8)((sq - 3) / 2);
		break;
	}

	return idx >= agc? idx - agc : 0;
}