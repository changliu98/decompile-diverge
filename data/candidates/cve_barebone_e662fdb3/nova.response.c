static void do_iccprofile_item(struct cx231xx *dev,
			     struct cx231xx_dmaqueue *dma_q,
			     struct cx231xx_buffer *buf, u32 bytesused)
{
	u32 cur_field = 0;
	u32 cur_line = 0;

	if (bytesused < 5)
		return;

	cur_field = cx231xx_get_field(dev->norm, buf, bytesused);

	dev_dbg(&dev->udev->dev,
		"do_iccprofile_item() cur_field=0x%02x, cur_line=0x%02x\n",
		cur_field, cur_line);

	if (cur_field == 1) {
		kfree(dma_q->left_field);
		dma_q->left_field = NULL;
	}

	if (cur_field == 0) {
		dma_q->left_field = vb2_dma_sg_plane_desc(&dma_q->vb.vb2_buf,
			0, &cur_line, 1);
	}

	if ((cur_field == 0) || (cur_field == 1)) {
		vb2_set_plane_payload(&dma_q->vb.vb2_buf,
			4, cur_line);
	}
}