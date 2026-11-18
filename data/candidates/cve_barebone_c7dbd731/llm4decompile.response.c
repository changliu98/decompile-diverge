void
mt76_add_fragment(struct mt76_dev *dev, struct mt76_queue *q, void *data,
		  int len, bool more)
{
	struct page *page = virt_to_head_page(data);
	struct sk_buff *skb = q->rx_head;
	int offset = (void *)data - page_address(page) + q->buf_offset;

	skb_add_rx_frag(skb, skb_end_pointer(skb)[2], page, offset, len,
			q->buf_size);

	if (!more) {
		q->rx_head = NULL;
		dev->drv->rx_skb(dev, (void *)q - (void *)dev->q_rx, skb);
	}
}