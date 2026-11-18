/*
 * Converts a command integer code to its corresponding string representation.
 *
 * @param cmd The command code (e.g., 0x80 for STOP_CAPTURE).
 * @return A pointer to a static string describing the command, or "UNKNOWN" if the command is not recognized.
 */
char * cmd_to_str(int command_code)
{
  switch(command_code) {
  case 0x80: return "STOP_CAPTURE";
  case 0x81: return "START_CAPTURE";
  case 0x82: return "SET_VIDEO_ID";
  case 0x83: return "SET_VBI_LINE";
  case 0x84: return "SET_VBI_CONFIG";
  case 0x85: return "SET_STREAM_TYPE";
  case 0x86: return "SET_SPATIAL_FILTER_TYPE";
  case 0x87: return "SET_PLACEHOLDER";
  case 0x88: return "SET_PGM_INDEX_INFO";
  case 0x89: return "SET_PCR_ID";
  case 0x8a: return "SET_OUTPUT_PORT";
  case 0x8b: return "SET_NUM_VSYNC_LINES";
  case 0x8c: return "SET_GOP_PROPERTIES";
  case 0x8d: return "SET_GOP_CLOSURE";
  case 0x8e: return "SET_FRAME_SIZE";
  case 0x8f: return "SET_FRAME_RATE";
  case 0x90: return "SET_FRAME_DROP_RATE";
  case 0x91: return "SET_EVENT_NOTIFICATION";
  case 0x92: return "SET_DNR_FILTER_PROPS";
  case 0x93: return "SET_DNR_FILTER_MODE";
  case 0x94: return "SET_DMA_BLOCK_SIZE";
  case 0x95: return "SET_CORING_LEVELS";
  case 0x96: return "SET_COPYRIGHT";
  case 0x97: return "SET_BIT_RATE";
  case 0x98: return "SET_AUDIO_PROPERTIES";
  case 0x99: return "SET_AUDIO_ID";
  case 0x9a: return "SET_ASPECT_RATIO";
  case 0x9b: return "SCHED_DMA_TO_HOST";
  case 0x9c: return "REFRESH_INPUT";
  case 0x9d: return "PING_FW";
  case 0x9e: return "PAUSE_ENCODER";
  case 0x9f: return "MUTE_VIDEO";
  case 0xa0: return "MUTE_AUDIO";
  case 0xa1: return "MISC";
  case 0xa2: return "INITIALIZE_INPUT";
  case 0xa3: return "HALT_FW";
  case 0xa4: return "GET_VERSION";
  case 0xa5: return "GET_SEQ_END";
  case 0xa6: return "GET_PREV_DMA_INFO_MB_9";
  case 0xa7: return "GET_PREV_DMA_INFO_MB_10";
  default: return "UNKNOWN";
  }
}