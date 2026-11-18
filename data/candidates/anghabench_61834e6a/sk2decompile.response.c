static const char *cmd_to_str(int cmd) {
  const char *str;
  switch (cmd) {
    case INITIALIZE_INPUT:
      str = "INITIALIZE_INPUT";
      break;
    case REFRESH_INPUT:
      str = "REFRESH_INPUT";
      break;
    case SET_FRAME_SIZE:
      str = "SET_FRAME_SIZE";
      break;
    case SET_FRAME_RATE:
      str = "SET_FRAME_RATE";
      break;
    case SET_FRAME_DROP_RATE:
      str = "SET_FRAME_DROP_RATE";
      break;
    case SET_ASPECT_RATIO:
      str = "SET_ASPECT_RATIO";
      break;
    case SET_STREAM_TYPE:
      str = "SET_STREAM_TYPE";
      break;
    case SET_OUTPUT_PORT:
      str = "SET_OUTPUT_PORT";
      break;
    case SET_VIDEO_ID:
      str = "SET_VIDEO_ID";
      break;
    case SET_AUDIO_ID:
      str = "SET_AUDIO_ID";
      break;
    case SET_PCR_ID:
      str = "SET_PCR_ID";
      break;
    case SET_GOP_CLOSURE:
      str = "SET_GOP_CLOSURE";
      break;
    case SET_GOP_PROPERTIES:
      str = "SET_GOP_PROPERTIES";
      break;
    case SET_NUM_VSYNC_LINES:
      str = "SET_NUM_VSYNC_LINES";
      break;
    case SET_VBI_LINE:
      str = "SET_VBI_LINE";
      break;
    case SET_VBI_CONFIG:
      str = "SET_VBI_CONFIG";
      break;
    case SET_PLACEHOLDER:
      str = "SET_PLACEHOLDER";
      break;
    case SET_PGM_INDEX_INFO:
      str = "SET_PGM_INDEX_INFO";
      break;
    case SET_DMA_BLOCK_SIZE:
      str = "SET_DMA_BLOCK_SIZE";
      break;
    case SCHED_DMA_TO_HOST:
      str = "SCHED_DMA_TO_HOST";
      break;
    case SET_AUDIO_PROPERTIES:
      str = "SET_AUDIO_PROPERTIES";
      break;
    case SET_CORING_LEVELS:
      str = "SET_CORING_LEVELS";
      break;
    case SET_COPYRIGHT:
      str = "SET_COPYRIGHT";
      break;
    case SET_BIT_RATE:
      str = "SET_BIT_RATE";
      break;
    case SET_SPATIAL_FILTER_TYPE:
      str = "SET_SPATIAL_FILTER_TYPE";
      break;
    case SET_DNR_FILTER_MODE:
      str = "SET_DNR_FILTER_MODE";
      break;
    case SET_DNR_FILTER_PROPS:
      str = "SET_DNR_FILTER_PROPS";
      break;
    case SET_EVENT_NOTIFICATION:
      str = "SET_EVENT_NOTIFICATION";
      break;
    case START_CAPTURE:
      str = "START_CAPTURE";
      break;
    case STOP_CAPTURE:
      str = "STOP_CAPTURE";
      break;
    case PAUSE_ENCODER:
      str = "PAUSE_ENCODER";
      break;
    case MUTE_VIDEO:
      str = "MUTE_VIDEO";
      break;
    case MUTE_AUDIO:
      str = "MUTE_AUDIO";
      break;
    case MISC:
      str = "MISC";
      break;
    case GET_VERSION:
      str = "GET_VERSION";
      break;
    case GET_SEQ_END:
      str = "GET_SEQ_END";
      break;
    case GET_PREV_DMA_INFO_MB_9:
      str = "GET_PREV_DMA_INFO_MB_9";
      break;
    case GET_PREV_DMA_INFO_MB_10:
      str = "GET_PREV_DMA_INFO_MB_10";
      break;
    case PING_FW:
      str = "PING_FW";
      break;
    case HALT_FW:
      str = "HALT_FW";
      break;
    default:
      str = "UNKNOWN";
      break;
  }
  return str;
}