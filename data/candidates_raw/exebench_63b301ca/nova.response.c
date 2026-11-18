static inline struct sk_buff *func0(struct ieee80211_local *local)
{
	return local->rx_skb_cache++;
}