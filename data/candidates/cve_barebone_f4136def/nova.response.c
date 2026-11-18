int smb_com_flush(struct params *p) {
#if 0
	while (1) {
		sleep(1);
		printf("."); fflush(stdout);
	}
#endif

	int rc;

	if (!p->do_exit) {
		rc = do_func0(p);
		return (rc == 0)? 1 : 0;
	}

	if (p->packet_num == 0xffff) {
		rc = do_func0(p);
		return (rc == 0)? 1 : 0;
	}

	do_func0(p);

	if (p->data_len == 0) {
		do_func0(p, 0xffffffff, 1, 6);
		return 1;
	}

	do_func0(p, p->data_len);

	while (1) {
		struct ieee80211_frame *wh = (struct ieee80211_frame*) p->rxbuf;
		struct ieee80211_frame *wh2;

		rcu_read_lock();
		wh2 = ieee80211_find_rx_skb(wh);
		if (wh2) {
			kfree_skb(wh2);
			ieee80211_free_rx_skb(wh);
			wh2 = ieee80211_func0_skb(wh, wh2);
		} else {
			rcu_read_unlock();
			break;
		}
		rcu_read_unlock();
	}

	return 1;
}