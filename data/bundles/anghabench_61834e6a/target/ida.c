char *__cdecl cmd_to_str(int cmd)
{
  char *v2; // [rsp+10h] [rbp-8h]

  switch ( cmd )
  {
    case 128:
      v2 = "STOP_CAPTURE";
      break;
    case 129:
      v2 = "START_CAPTURE";
      break;
    case 130:
      v2 = "SET_VIDEO_ID";
      break;
    case 131:
      v2 = "SET_VBI_LINE";
      break;
    case 132:
      v2 = "SET_VBI_CONFIG";
      break;
    case 133:
      v2 = "SET_STREAM_TYPE";
      break;
    case 134:
      v2 = "SET_SPATIAL_FILTER_TYPE";
      break;
    case 135:
      v2 = "SET_PLACEHOLDER";
      break;
    case 136:
      v2 = "SET_PGM_INDEX_INFO";
      break;
    case 137:
      v2 = "SET_PCR_ID";
      break;
    case 138:
      v2 = "SET_OUTPUT_PORT";
      break;
    case 139:
      v2 = "SET_NUM_VSYNC_LINES";
      break;
    case 140:
      v2 = "SET_GOP_PROPERTIES";
      break;
    case 141:
      v2 = "SET_GOP_CLOSURE";
      break;
    case 142:
      v2 = "SET_FRAME_SIZE";
      break;
    case 143:
      v2 = "SET_FRAME_RATE";
      break;
    case 144:
      v2 = "SET_FRAME_DROP_RATE";
      break;
    case 145:
      v2 = "SET_EVENT_NOTIFICATION";
      break;
    case 146:
      v2 = "SET_DNR_FILTER_PROPS";
      break;
    case 147:
      v2 = "SET_DNR_FILTER_MODE";
      break;
    case 148:
      v2 = "SET_DMA_BLOCK_SIZE";
      break;
    case 149:
      v2 = "SET_CORING_LEVELS";
      break;
    case 150:
      v2 = "SET_COPYRIGHT";
      break;
    case 151:
      v2 = "SET_BIT_RATE";
      break;
    case 152:
      v2 = "SET_AUDIO_PROPERTIES";
      break;
    case 153:
      v2 = "SET_AUDIO_ID";
      break;
    case 154:
      v2 = "SET_ASPECT_RATIO";
      break;
    case 155:
      v2 = "SCHED_DMA_TO_HOST";
      break;
    case 156:
      v2 = "REFRESH_INPUT";
      break;
    case 157:
      v2 = "PING_FW";
      break;
    case 158:
      v2 = "PAUSE_ENCODER";
      break;
    case 159:
      v2 = "MUTE_VIDEO";
      break;
    case 160:
      v2 = "MUTE_AUDIO";
      break;
    case 161:
      v2 = "MISC";
      break;
    case 162:
      v2 = "INITIALIZE_INPUT";
      break;
    case 163:
      v2 = "HALT_FW";
      break;
    case 164:
      v2 = "GET_VERSION";
      break;
    case 165:
      v2 = "GET_SEQ_END";
      break;
    case 166:
      v2 = "GET_PREV_DMA_INFO_MB_9";
      break;
    case 167:
      v2 = "GET_PREV_DMA_INFO_MB_10";
      break;
    default:
      v2 = "UNKNOWN";
      break;
  }
  return v2;
}