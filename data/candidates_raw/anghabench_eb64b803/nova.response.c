static uint32_t func0(uint32_t format)
{
	uint32_t i = format;
	uint32_t ret;

	switch (i) {
	case SND_SOUND_FORMAT_U8:
		ret = SND_SOUND_FORMAT_U8;
		break;
	case SND_SOUND_FORMAT_S16_LE:
		ret = SND_SOUND_FORMAT_S16_LE;
		break;
	case SND_SOUND_FORMAT_S16_BE:
		ret = SND_SOUND_FORMAT_S16_BE;
		break;
	case SND_SOUND_FORMAT_S32_LE:
		ret = SND_SOUND_FORMAT_S32_LE;
		break;
	case SND_SOUND_FORMAT_S32_BE:
		ret = SND_SOUND_FORMAT_S32_BE;
		break;
	case SND_SOUND_FORMAT_S24_LE:
		ret = SND_SOUND_FORMAT_S24_LE;
		break;
	case SND_SOUND_FORMAT_S24_BE:
		ret = SND_SOUND_FORMAT_S24_BE;
		break;
	case SND_SOUND_FORMAT_S8:
		ret = SND_SOUND_FORMAT_S8;
		break;
	case SND_SOUND_FORMAT_U16_LE:
		ret = SND_SOUND_FORMAT_U16_LE;
		break;
	case SND_SOUND_FORMAT_U16_BE:
		ret = SND_SOUND_FORMAT_U16_BE;
		break;
	case SND_SOUND_FORMAT_U32_LE:
		ret = SND_SOUND_FORMAT_U32_LE;
		break;
	case SND_SOUND_FORMAT_U32_BE:
		ret = SND_SOUND_FORMAT_U32_BE;
		break;
	default:
		ret = S