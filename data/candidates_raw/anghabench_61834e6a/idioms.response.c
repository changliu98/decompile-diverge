char *get_command_name(int command)
{
  char *name;
  switch (command) {
  case 0x00010000 + 128:
    name = "STOP_CAPTURE";
    break;
  case 0x00010000 + 129:
    name = "START_CAPTURE";
    break;
  case 0x00010000 + 130:
    name = "SET_VIDEO_ID";
    break;
  case 0x00010000 + 131:
    name = "SET_VBI_LINE";
    break;
  case 0x00010000 + 132:
    name = "SET_VBI_CONFIG";
    break;
  case 0x00010000 + 133:
    name = "SET_STREAM_TYPE";
    break;
  case 0x00010000 + 134:
    name = "SET_SPATIAL_FILTER_TYPE";
    break;
  case 0x00010000 + 135:
    name = "SET_PLACEHOLDER";
    break;
  case 0x00010000 + 136:
    name = "SET_PGM_INDEX_INFO";
    break;
  case 0x00010000 + 137:
    name = "SET_PCR_ID";
    break;
  case 0x00010000 + 138:
    name = "SET_OUTPUT_PORT";
    break;
  case 0x00010000 + 139:
    name = "SET_NUM_VSYNC_LINES";
    break;
  case 0x00010000 + 140:
    name = "SET_GOP_PROPERTIES";
    break;
  case 0x00010000 + 141:
    name = "SET_GOP_CLOSURE";
    break;
  case 0x00010000 + 142:
    name = "SET_FRAME_SIZE";
    break;
  case 0x00010000 + 143:
    name = "SET_FRAME_RATE";
    break;
  case 0x00010000 + 144:
    name = "SET_FRAME_DROP_RATE";
    break;
  case 0x00010000 + 145:
    name = "SET_EVENT_NOTIFICATION";
    break;
  case 0x00010000 + 146:
    name = "SET_DNR_FILTER_PROPS";
    break;
  case 0x00010000 + 147:
    name = "SET_DNR_FILTER_MODE";
    break;
  case 0x00010000 + 148:
    name = "SET_DMA_BLOCK_SIZE";
    break;
  case 0x00010000 + 149:
    name = "SET_CORING_LEVELS";
    break;
  case 0x00010000 + 150:
    name = "SET_COPYRIGHT";
    break;
  case 0x00010000 + 151:
    name = "SET_BIT_RATE";
    break;
  case 0x00010000 + 152:
    name = "SET_AUDIO_PROPERTIES";
    break;
  case 0x00010000 + 153:
    name = "SET_AUDIO_ID";
    break;
  case 0x00010000 + 154:
    name = "SET_ASPECT_RATIO";
    break;
  case 0x00010000 + 155:
    name = "SCHED_DMA_TO_HOST";
    break;
  case 0x00010000 + 156:
    name = "REFRESH_INPUT";
    break;
  case 0x00010000 + 157:
    name = "PING_FW";
    break;
  case 0x00010000 + 158:
    name = "PAUSE_ENCODER";
    break;
  case 0x00010000 + 159:
    name = "MUTE_VIDEO";
    break;
  case 0x00010000 + 160:
    name = "MUTE_AUDIO";
    break;
  case 0x00010000 + 161:
    name = "MISC";
    break;
  case 0x00010000 + 162:
    name = "INITIALIZE_INPUT";
    break;
  case 0x00010000 + 163:
    name = "HALT_FW";
    break;
  case 0x00010000 + 164:
    name = "GET_VERSION";
    break;
  case 0x00010000 + 165:
    name = "GET_SEQ_END";
    break;
  case 0x00010000 + 166:
    name = "GET_PREV_DMA_INFO_MB_9";
    break;
  case 0x00010000 + 167:
    name = "GET_PREV_DMA_INFO_MB_10";
    break;
  default:
    name = "UNKNOWN";
  }
  return name;
}