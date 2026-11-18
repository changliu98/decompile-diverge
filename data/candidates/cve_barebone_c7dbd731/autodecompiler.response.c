__attribute__((used)) static void mt76_add_fragment(struct net_device *ndev,
			       struct hnae_ring *ring, void *va, int size,
			       unsigned char last_offset)
{
	unsigned int last_offset_index;
	struct hnae_desc_cb *desc_cb;
	struct hnae_desc *desc;
	struct page *page;
	struct sk_buff *skb;
	int offset;

	/* reuse buffer space */
	last_offset_index = last_offset & 1;
	page = virt_to_head_page(va);
	desc_cb = (struct hnae_desc_cb *)va;
	offset = (unsigned long)va - page_address(page);

	skb = ring->skb_cache;
	offset += ring->last_offset;

	skb_add_rx_frag(skb, skb_tailroom(skb), page, offset, size,
			ring->buf_size);

	if (last_offset_index)
		return;

	/* last packet, close skb */
	ring->skb_cache = NULL;
	ndev->netdev_ops->ndo_netpoll_receive_skb(ndev,
						  skb - (void *)&ring->skb_cache,
						  ndev);
}