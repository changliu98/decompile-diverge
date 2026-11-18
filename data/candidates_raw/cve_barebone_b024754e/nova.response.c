static void func0(struct ieee80211_device *ieee,
				   struct sk_buff *skb)
{
	u16 *tag;
	u8 *pos;

	tag = (u16 *)skb->data;
	pos = (u8 *)skb->data;
	if (tag[0] == 0)
		return;

	tag = (u16 *)(skb->data + be16_to_cpu(tag[0]) - 2);
	pos = (u8 *)tag;

	if (be16_to_cpu(tag[0]) == 0x600 &&
	    pos[1] == 0x07 &&
	    pos[2] == 0xff &&
	    pos[3] == 0x00) {
		ieee80211_beacon_detect(ieee, skb);
		return;
	}

	if (tag[0] == 0x00e9 &&
	    pos[1] == 0x00 &&
	    pos[2] == 0xdd &&
	    pos[3] == 0x00) {
		ieee80211_probe_response_detect(ieee, skb);
		return;
	}
}