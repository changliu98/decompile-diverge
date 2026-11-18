static void h(struct sk_buff *skb, int len)
{
	if (skb->len > len)
		__skb_pull(skb, skb->len - len);
	else
		skb->len = 0;
}