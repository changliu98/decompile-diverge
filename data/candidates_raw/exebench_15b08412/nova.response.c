static int func0(struct st_fdma_chan *fchan,
		unsigned long pwidth)
{
	int ret;

	if (!pwidth || pwidth > fchan->fdev->datawidth) {
		ret = 1;
		goto err_out;
	}

	fchan->fdesc_size = fchan->fdev->desc_num / pwidth;
	fchan->fdesc_num = fchan->fdev->desc_num % pwidth;

	ret = 0;
err_out:
	return ret;
}