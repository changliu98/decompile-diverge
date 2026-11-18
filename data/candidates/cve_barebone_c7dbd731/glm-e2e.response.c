void mt76_add_fragment(struct mt76_dev *dev, struct sk_buff *skb, 
                       void *va, int len, bool more)
{
    struct page *page = virt_to_head_page(va);
    int offset = (unsigned long)va - (unsigned long)page_address(page);
    struct sk_buff *iter = skb_shinfo(skb)->frag_list;
    
    offset += skb->len;

    skb_add_rx_frag(iter, skb_end_pointer(iter)->nr_frags, page, offset, len, skb->dataref);

    if (!more) {
        skb_shinfo(skb)->frag_list = NULL;
        dev->drv->rx_skb(dev, (skb - (void *)dev) >> 4, iter);
    }
}