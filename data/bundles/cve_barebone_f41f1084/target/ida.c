int __cdecl sdp_parse_fmtp_config_h264(
        AVFormatContext *s,
        AVStream *stream,
        PayloadContext *h264_data,
        const char *attr,
        const char *value)
{
  unsigned int v5; // eax
  int ret; // [rsp+14h] [rbp-3Ch]
  AVCodecParameters *par; // [rsp+18h] [rbp-38h]

  par = stream->codecpar;
  if ( !strcmp(attr, "packetization-mode") )
  {
    v5 = atoi(value);
    av_log(s, 48, "RTP Packetization Mode: %d\n", v5);
    h264_data->packetization_mode = atoi(value);
    if ( h264_data->packetization_mode > 1 )
      av_log(s, 16, "Interleaved RTP mode is not supported yet.\n");
    return 0;
  }
  if ( !strcmp(attr, "profile-level-id") )
  {
    if ( strlen(value) == 6 )
      parse_profile_level_id(s, h264_data, value);
    return 0;
  }
  if ( strcmp(attr, "sprop-parameter-sets") )
    return 0;
  if ( value[strlen(value) - 1] == 44 )
  {
    av_log(s, 24, "Missing PPS in sprop-parameter-sets, ignoring\n");
    return 0;
  }
  else
  {
    par->extradata_size = 0;
    av_freep(par);
    ret = ff_h264_parse_sprop_parameter_sets(s, &par->extradata, &par->extradata_size, value);
    av_log(s, 48, "Extradata set to %p (size: %d)\n", par->extradata, (unsigned int)par->extradata_size);
    return ret;
  }
}