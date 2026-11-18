static int sdp_parse_fmtp_config_h264(AVFormatContext *s, PayloadContext *data,
                                      void *arg, const char *attr,
                                      const char *value) {
  H264Context *s1 = arg;
  AVCodecParameters *par = data->par;
  int ret;
  if (!strcmp(attr, "packetization-mode")) {
    av_log(s, 48, "RTP Packetization Mode: %d\n", atoi(value));
    s1->packetization_mode = atoi(value);
    if (s1->packetization_mode > 1)
      av_log(s, 16, "Interleaved RTP mode is not supported yet.\n");
    return 0;
  }
  if (!strcmp(attr, "profile-level-id")) {
    if (strlen(value) == 6) parse_profile_level_id(s, s1, value);
    return 0;
  }
  if (!strcmp(attr, "sprop-parameter-sets")) {
    if (value[strlen(value) - 1] == ',') {
      av_log(s, 24, "Missing PPS in sprop-parameter-sets, ignoring\n");
      return 0;
    }
    par->extradata_size = 0;
    av_freep(&par->extradata);
    ret = ff_h264_parse_sprop_parameter_sets(s, &par->extradata,
                                             &par->extradata_size, value);
    av_log(s, 48, "Extradata set to %p (size: %d)\n", par->extradata,
           par->extradata_size);
    return ret;
  }
  return 0;
}