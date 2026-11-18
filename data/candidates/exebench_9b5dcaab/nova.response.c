static void modify_calculated_address_new_syntax(struct drm_display_mode *mode)
{
	mode->hdisplay += 5;
	mode->htotal -= 5;
}