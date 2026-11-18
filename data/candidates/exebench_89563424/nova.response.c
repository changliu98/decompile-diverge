static void f(struct drm_display_mode *mode)
{
	mode->hdisplay = mode->htotal;
	mode->vdisplay = mode->vtotal;
}