static void func0(struct drm_display_mode *mode)
{
	mode->hdisplay = mode->htotal;
	mode->vdisplay = mode->vtotal;
}