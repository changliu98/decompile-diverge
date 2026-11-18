static int parse_video_info(struct airo_info *ai, struct net_device *dev)
{
	unsigned short len, rxlen;
	int status;

	dev->stats.rx_missed_errors = read_long(ai,RXMISS);
	dev->stats.collisions = read_long(ai,TXCOLL);
	write_mif_long(ai, 1, 0);
	rxlen = read_mif_byte(ai);
	dev->stats.rx_length_errors = rxlen;
	dev->stats.rx_crc_errors = do_crc_test(&crc_table, dev, rxlen);
	if (rxlen > sizeof(struct sk_buff))
		len = rxlen;
	else
		len = sizeof(struct sk_buff);
	dev->stats.rx_frame_errors = len;
	dev->stats.rx_fifo_errors = read_mif_byte(ai);
	if (dev->stats.rx_fifo_errors == 0) {
		dev->stats.rx_fifo_errors = 0;
		status = -EOVERFLOW;
	} else {
		memset(dev->stats.rx_fifo_errors, 0, 64);
		status = read_fifo(ai, dev->stats.rx_fifo_errors,
				   dev->stats.rx_fifo_errors_len);
		if (status < 0)
			status = -EOVERFLOW;
	}
	return status;
}