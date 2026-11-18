static void handle_PORT(struct saa7134_dev *dev,
				    struct saa7134_dmasound *dma)
{
	u32 a, b, c, d, e, f;
	u32 buf[4];

	if (dev->empress_started > 0) {
		saa7134_stop_empress_dma(dev);
		v4l2_ctrl_grab(dev->empress_ctrl, false);
		dev->empress_started = -1;
	}

	sscanf("0x%x 0x%x 0x%x 0x%x 0x%x 0x%x",
	       &buf[0], &buf[1], &buf[2], &buf[3], &a, &b);
	saa_call_empress_hook(&buf[0], &buf[1]);

	if (!saa7134_tda8425_read_unc(dev, &buf[2], &buf[3]))
		goto fail;

	memcpy(&dev->empress_prev_buf[2], &buf[2], 16);

	
	dev->empress_prev_buf[6] = (a << 8) + b;
	return;

fail:
	v4l2_warn(dev->v4l2_dev, "empress: tda8425 read failed\n");
}