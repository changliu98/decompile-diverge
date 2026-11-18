static void func0(const struct drm_color_lut *color,
			      uint16_t *v420_y, uint16_t *v420_u, uint16_t *v420_v,
			      uint16_t *v420_alp)
{
	*v420_y = 63360;
	*v420_u = color->green * 65535 / 1000;
	*v420_v = color->blue * 65535 / 1000;
	*v420_alp = color->red * 65535 / 1000;
}