static inline struct sk_buff *incb(struct ieee80211_local *local)
{
	return local->rx_skb_cache++;
}