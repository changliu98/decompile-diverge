static int gdi_Bitmap_Decompress(struct drm_connector *connector,
				    struct drm_display_mode *mode,
				    struct drm_display_mode *adjusted_mode,
				    int maxX, int maxY,
				    uint32_t max_pclk,
				    uint32_t max_pclk_freq)
{
	struct drm_device *dev = connector->dev;
	struct drm_display_mode *fixed_mode = &dev->mode_config.fixed_mode;
	unsigned long pclk;
	unsigned long pclk_freq;
	unsigned long pclk_div;
	unsigned long pclk_div_max;
	unsigned long pclk_div_min;
	unsigned long pclk_div_step;
	int ret;

	mode->hdisplay = fixed_mode->hdisplay;
	mode->vdisplay = fixed_mode->vdisplay;

	mode->clock = max_pclk * mode->hdisplay * mode->vdisplay;
	mode->clock = DIV_ROUND_UP(mode->clock, 16);

	
	ret = 0;
	while (ret == 0) {
		pclk_div_max = max_pclk;
		pclk_div_min = max_pclk_freq;
		pclk_div_step = 1;

		if (maxX) {
			pclk_div_max = maxX;
			pclk_div_min = maxX * max_pclk_freq;
		} else if (maxY) {
			pclk_div_max = maxY;
			pclk_div_min = maxY * max_pclk_freq;
		}

		pclk_div = DIV_ROUND_UP(pclk_div_max, pclk_div_min);
		pclk_div = DIV_ROUND_UP(pclk_div, pclk_div_step);

		if (pclk_div == 0