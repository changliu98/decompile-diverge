__attribute__((used)) static char *cmd_to_str(int cmd)
{
	char *str;

	switch (cmd) {
	case VENUS_CMD_PING_FW:
		str = "PING_FW";
		break;
	case VENUS_CMD_START_CAPTURE:
		str = "START_CAPTURE";
		break;
	case VENUS_CMD_STOP_CAPTURE:
		str = "STOP_CAPTURE";
		break;
	case VENUS_CMD_SET_AUDIO_ID:
		str = "SET_AUDIO_ID";
		break;
	case VENUS_CMD_SET_VIDEO_ID:
		str = "SET_VIDEO_ID";
		break;
	case VENUS_CMD_SET_PCR_ID:
		str = "SET_PCR_ID";
		break;
	case VENUS_CMD_SET_FRAME_RATE:
		str = "SET_FRAME_RATE";
		break;
	case VENUS_CMD_SET_FRAME_SIZE:
		str = "SET_FRAME_SIZE";
		break;
	case VENUS_CMD_SET_BIT_RATE:
		str = "SET_BIT_RATE";
		break;
	case VENUS_CMD_SET_GOP_PROPERTIES:
		str = "SET_GOP_PROPERTIES";
		break;
	case VENUS_CMD_SET_ASPECT_RATIO:
		str = "SET_ASPECT_RATIO";
		break;
	case VENUS_CMD_SET_DNR_FILTER_MODE:
		str = "SET_DNR_FILTER_MODE";
		break;
	case VENUS_CMD_SET_DNR_FILTER_PROPS:
		str = "SET_DNR_FILTER_PROPS";
		break;
	case VENUS_CMD_SET_CORING_LEVELS:
		str = "SET_CORING_LEVELS";
		break;
	case VENUS_CMD_SET_SPATIAL_FILTER_TYPE:
		str = "SET_SPATIAL_FILTER_TYPE";
		break;
	case VENUS_CMD_SET_VBI_LINE:
		str = "SET_VBI_LINE";
		break;
	case VENUS_CMD_SET_STREAM_TYPE:
		str = "SET_STREAM_TYPE";
		break;
	case VENUS_CMD_SET_OUTPUT_PORT:
		str = "SET_OUTPUT_PORT";
		break;
	case VENUS_CMD_SET_AUDIO_PROPERTIES:
		str = "SET_AUDIO_PROPERTIES";
		break;
	case VENUS_CMD_HALT_FW:
		str = "HALT_FW";
		break;
	case VENUS_CMD_GET_VERSION:
		str = "GET_VERSION";
		break;
	case VENUS_CMD_SET_GOP_CLOSURE:
		str = "SET_GOP_CLOSURE";
		break;
	case VENUS_CMD_GET_SEQ_END:
		str = "GET_SEQ_END";
		break;
	case VENUS_CMD_SET_PGM_INDEX_INFO:
		str = "SET_PGM_INDEX_INFO";
		break;
	case VENUS_CMD_SET_VBI_CONFIG:
		str = "SET_VBI_CONFIG";
		break;
	case VENUS_CMD_SET_DMA_BLOCK_SIZE:
		str = "SET_DMA_BLOCK_SIZE";
		break;
	case VENUS_CMD_GET_PREV_DMA_INFO_MB_10:
		str = "GET_PREV_DMA_INFO_MB_10";
		break;
	case VENUS_CMD_GET_PREV_DMA_INFO_MB_9:
		str = "GET_PREV_DMA_INFO_MB_9";
		break;
	case VENUS_CMD_SCHED_DMA_TO_HOST:
		str = "SCHED_DMA_TO_HOST";
		break;
	case VENUS_CMD_INITIALIZE_INPUT:
		str = "INITIALIZE_INPUT";
		break;
	case VENUS_CMD_SET_FRAME_DROP_RATE:
		str = "SET_FRAME_DROP_RATE";
		break;
	case VENUS_CMD_PAUSE_ENCODER:
		str = "PAUSE_ENCODER";
		break;
	case VENUS_CMD_REFRESH_INPUT:
		str = "REFRESH_INPUT";
		break;
	case VENUS_CMD_SET_COPYRIGHT:
		str = "SET_COPYRIGHT";
		break;
	case VENUS_CMD_SET_EVENT_NOTIFICATION:
		str = "SET_EVENT_NOTIFICATION";
		break;
	case VENUS_CMD_SET_NUM_VSYNC_LINES:
		str = "SET_NUM_VSYNC_LINES";
		break;
	case VENUS_CMD_SET_PLACEHOLDER:
		str = "SET_PLACEHOLDER";
		break;
	case VENUS_CMD_MUTE_VIDEO:
		str = "MUTE_VIDEO";
		break;
	case VENUS_CMD_MUTE_AUDIO:
		str = "MUTE_AUDIO";
		break;
	case VENUS_CMD_MISC:
		str = "MISC";
		break;
	default:
		str = "UNKNOWN";
	}

	return str;
}