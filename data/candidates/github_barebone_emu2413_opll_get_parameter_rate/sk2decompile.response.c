static int get_parameter_rate(MPEG_audio_frame_t *frame) {
  int rate;
  if (!(frame->flags & 1) && !frame->bitrate) return 0;
  switch (frame->sampling_frequency) {
    case 0:
      rate = frame->mpeg_header->sampling_frequency_1000;
      break;
    case 1:
      rate = frame->mpeg_header->sampling_frequency_12000;
      break;
    case 2:
      rate = (frame->mpeg_header->mpeg25) ? 0 : frame->mpeg_header->sampling_frequency_5000;
      break;
    case 3:
      if (frame->mpeg25_ext)
        rate = 5;
      else if (frame->mpeg_header->mpeg25)
        rate = frame->mpeg_header->sampling_frequency_5000;
      else
        rate = 7;
      break;
    case 4:
      rate = 12;
      break;
    default:
      rate = 0;
      break;
  }
  return rate;
}