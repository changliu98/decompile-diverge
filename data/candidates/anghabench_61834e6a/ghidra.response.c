char * cmd_to_str(int cmd)

{
  int cmd_local;
  char *local_10;
  
  switch(cmd) {
  case 0x80:
    local_10 = "STOP_CAPTURE";
    break;
  case 0x81:
    local_10 = "START_CAPTURE";
    break;
  case 0x82:
    local_10 = "SET_VIDEO_ID";
    break;
  case 0x83:
    local_10 = "SET_VBI_LINE";
    break;
  case 0x84:
    local_10 = "SET_VBI_CONFIG";
    break;
  case 0x85:
    local_10 = "SET_STREAM_TYPE";
    break;
  case 0x86:
    local_10 = "SET_SPATIAL_FILTER_TYPE";
    break;
  case 0x87:
    local_10 = "SET_PLACEHOLDER";
    break;
  case 0x88:
    local_10 = "SET_PGM_INDEX_INFO";
    break;
  case 0x89:
    local_10 = "SET_PCR_ID";
    break;
  case 0x8a:
    local_10 = "SET_OUTPUT_PORT";
    break;
  case 0x8b:
    local_10 = "SET_NUM_VSYNC_LINES";
    break;
  case 0x8c:
    local_10 = "SET_GOP_PROPERTIES";
    break;
  case 0x8d:
    local_10 = "SET_GOP_CLOSURE";
    break;
  case 0x8e:
    local_10 = "SET_FRAME_SIZE";
    break;
  case 0x8f:
    local_10 = "SET_FRAME_RATE";
    break;
  case 0x90:
    local_10 = "SET_FRAME_DROP_RATE";
    break;
  case 0x91:
    local_10 = "SET_EVENT_NOTIFICATION";
    break;
  case 0x92:
    local_10 = "SET_DNR_FILTER_PROPS";
    break;
  case 0x93:
    local_10 = "SET_DNR_FILTER_MODE";
    break;
  case 0x94:
    local_10 = "SET_DMA_BLOCK_SIZE";
    break;
  case 0x95:
    local_10 = "SET_CORING_LEVELS";
    break;
  case 0x96:
    local_10 = "SET_COPYRIGHT";
    break;
  case 0x97:
    local_10 = "SET_BIT_RATE";
    break;
  case 0x98:
    local_10 = "SET_AUDIO_PROPERTIES";
    break;
  case 0x99:
    local_10 = "SET_AUDIO_ID";
    break;
  case 0x9a:
    local_10 = "SET_ASPECT_RATIO";
    break;
  case 0x9b:
    local_10 = "SCHED_DMA_TO_HOST";
    break;
  case 0x9c:
    local_10 = "REFRESH_INPUT";
    break;
  case 0x9d:
    local_10 = "PING_FW";
    break;
  case 0x9e:
    local_10 = "PAUSE_ENCODER";
    break;
  case 0x9f:
    local_10 = "MUTE_VIDEO";
    break;
  case 0xa0:
    local_10 = "MUTE_AUDIO";
    break;
  case 0xa1:
    local_10 = "MISC";
    break;
  case 0xa2:
    local_10 = "INITIALIZE_INPUT";
    break;
  case 0xa3:
    local_10 = "HALT_FW";
    break;
  case 0xa4:
    local_10 = "GET_VERSION";
    break;
  case 0xa5:
    local_10 = "GET_SEQ_END";
    break;
  case 0xa6:
    local_10 = "GET_PREV_DMA_INFO_MB_9";
    break;
  case 0xa7:
    local_10 = "GET_PREV_DMA_INFO_MB_10";
    break;
  default:
    local_10 = "UNKNOWN";
  }
  return local_10;
}