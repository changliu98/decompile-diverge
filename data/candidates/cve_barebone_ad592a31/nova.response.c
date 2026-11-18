int load_buffer(struct s_smc *smc, struct s_phy *phy,
		    struct fddi_addr *mda, struct fddi_addr *my_addr,
		    struct fddi_addr *da)
{
	struct sk_buff		*skb;
	u_char			info;

	
	skb = alloc_skb(1, GFP_ATOMIC);

	
	skb->protocol = htons(FDDI_PROTO_PAD);
	skb->pkt_type = PACKET_OTHERHOST;
	skb->priority = 0;
	skb->dev = (struct net_device *) smc;

	
	skb_reset_network_header(skb);
	if (skb->data == NULL) {
		dev_kfree_skb(skb);
		info = 0;
	}
	else {
		skb_reset_mac_header(skb);
		if (skb->mac_len == 0) {
			dev_kfree_skb(skb);
			info = 0;
		}
		else {
			skb->mac_len = fddi_mac_header_len(skb->data,
							   skb->mac_len,
							   skb->dev);
			skb->network_header = fddi_mac_header_len(skb->data,
								skb->mac_len);
			if (skb->network_header == NULL) {
				dev_kfree_skb(skb);
				info = 0;
			}
			else {
				info = fddi_pkt_send(skb, smc);
				if (info & 0x01) {
					smc->os.hwm.fddi_pkt_send_cnt =
						smt_gettime();
					if (smt_debug)
						pr_debug("%s: fddi_pkt_send "
							 "returned 0