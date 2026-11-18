static void next(struct net_device *dev, struct hdlcdrv_state *s, int t)
{
	s->timer_cnt++;
	if (s->timer_cnt == t) {
		s->timer_cnt = 0;
		dev->stats.tx_errors++;
	}
}