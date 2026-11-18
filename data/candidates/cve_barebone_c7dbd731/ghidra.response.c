void mt76_add_fragment(mt76_dev *dev,mt76_queue *q,void *data,int len,_Bool more)

{
  byte bVar1;
  sk_buff *skb_00;
  page *page_00;
  void *pvVar2;
  uchar *puVar3;
  sk_buff *skb;
  int offset;
  page *page;
  _Bool more_local;
  int len_local;
  void *data_local;
  mt76_queue *q_local;
  mt76_dev *dev_local;
  
  page_00 = virt_to_head_page(data);
  pvVar2 = page_address(page_00);
  skb_00 = q->rx_head;
  bVar1 = q->buf_offset;
  puVar3 = skb_end_pointer(skb_00);
  skb_add_rx_frag(skb_00,(uint)puVar3[2],page_00,(uint)bVar1 + ((int)data - (int)pvVar2),len,
                  q->buf_size);
  if (!more) {
    q->rx_head = (sk_buff *)0x0;
    (*dev->drv->rx_skb)(dev,(mt76_rxq_id)((long)q - (long)dev->q_rx >> 4),skb_00);
  }
  return;
}