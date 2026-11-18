void __cdecl mt76_add_fragment(mt76_dev *dev, mt76_queue *q, void *data, int len, bool more)
{
  sk_buff *skb = q->rx_head;
  page *page = virt_to_head_page(data);
  
  // Calculate the offset of the data within the page
  int offset = (int)((unsigned long)data - (unsigned long)page_address(page)) + q->buf_offset;
  
  // skb_end_pointer(skb) returns a pointer to the shinfo structure at the end of the skb.
  // The nr_frags field is located at offset 8 (i.e., the 3rd 32-bit integer) in skb_shared_info.
  skb_shared_info *shinfo = skb_end_pointer(skb);
  int nr_frags = shinfo->nr_frags; // Equivalent to skb_end_pointer(skb)[2]
  
  skb_add_rx_frag(skb, nr_frags, page, offset, len, q->buf_size);
  
  if ( !more )
  {
    q->rx_head = NULL;
    dev->drv->rx_skb(dev, q - dev->q_rx, skb);
  }
}