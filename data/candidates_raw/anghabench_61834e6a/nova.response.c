static const char *func0(enum drm_color_encoding encoding)
{
	const char *name;

	switch (encoding) {
	case DRM_COLOR_YCBCR_BT601:
		name = "bt601";
		break;
	case DRM_COLOR_YCBCR_BT709:
		name = "bt709";
		break;
	case DRM_COLOR_YCBCR_BT2020:
		name = "bt2020";
		break;
	case DRM_COLOR_YCBCR_BT470BG:
		name = "bt470bg";
		break;
	case DRM_COLOR_YCBCR_BT470M:
		name = "bt470m";
		break;
	case DRM_COLOR_YCBCR_BT470BG_2:
		name = "bt470bg_2";
		break;
	case DRM_COLOR_YCBCR_BT470M_2:
		name = "bt470m_2";
		break;
	case DRM_COLOR_YCBCR_BT470BG_601:
		name = "bt470bg_601";
		break;
	case DRM_COLOR_YCBCR_BT470M_601:
		name = "bt470m_601";
		break;
	case DRM_COLOR_YCBCR_BT1361_ECG:
		name = "bt1361_ecg";
		break;
	case DRM_COLOR_YCBCR_BT1361_SMPTEC:
		name = "bt1361_smptec";
		break;
	case DRM_COLOR_YCBCR_BT2400_SP:
		name = "bt2400_sp";
		break;
	case DRM_COLOR_YCBCR_BT2400_HP:
		name = "bt24