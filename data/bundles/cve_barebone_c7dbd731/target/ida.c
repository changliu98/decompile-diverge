void __cdecl mt76_add_fragment(mt76_dev *dev, mt76_queue *q, void *data, int len, bool more)
{
  unsigned int v5; // eax
  int v6; // esi
  sk_buff *skb; // [rsp+18h] [rbp-38h]
  int offset; // [rsp+24h] [rbp-2Ch]
  page *page; // [rsp+28h] [rbp-28h]
  bool morea; // [rsp+33h] [rbp-1Dh]
  int dataa; // [rsp+38h] [rbp-18h]

  dataa = (int)data;
  morea = more;
  page = virt_to_head_page(data);
  v5 = (unsigned int)page_address(page);
  skb = q->rx_head;
  offset = dataa - v5 + q->buf_offset;
  v6 = skb_end_pointer(skb)[2];
  skb_add_rx_frag(skb, v6, page, offset, len, q->buf_size);
  if ( !morea )
  {
    q->rx_head = 0LL;
    dev->drv->rx_skb(dev, (unsigned int)(q - dev->q_rx), skb);
  }
}