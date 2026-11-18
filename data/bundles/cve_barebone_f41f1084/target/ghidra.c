int sdp_parse_fmtp_config_h264
              (AVFormatContext *s,AVStream *stream,PayloadContext *h264_data,char *attr,char *value)

{
  AVCodecParameters *data_ptr;
  int iVar1;
  uint uVar2;
  size_t sVar3;
  int ret;
  AVCodecParameters *par;
  char *value_local;
  char *attr_local;
  PayloadContext *h264_data_local;
  AVStream *stream_local;
  AVFormatContext *s_local;
  
  data_ptr = stream->codecpar;
  iVar1 = strcmp(attr,"packetization-mode");
  if (iVar1 == 0) {
    uVar2 = atoi(value);
    av_log(s,0x30,"RTP Packetization Mode: %d\n",(ulong)uVar2);
    iVar1 = atoi(value);
    h264_data->packetization_mode = iVar1;
    if (1 < h264_data->packetization_mode) {
      av_log(s,0x10,"Interleaved RTP mode is not supported yet.\n");
    }
  }
  else {
    iVar1 = strcmp(attr,"profile-level-id");
    if (iVar1 == 0) {
      sVar3 = strlen(value);
      if (sVar3 == 6) {
        parse_profile_level_id(s,h264_data,value);
      }
    }
    else {
      iVar1 = strcmp(attr,"sprop-parameter-sets");
      if (iVar1 == 0) {
        sVar3 = strlen(value);
        if (value[sVar3 - 1] == ',') {
          av_log(s,0x18,"Missing PPS in sprop-parameter-sets, ignoring\n");
          return 0;
        }
        data_ptr->extradata_size = 0;
        av_freep(data_ptr);
        iVar1 = ff_h264_parse_sprop_parameter_sets
                          (s,&data_ptr->extradata,&data_ptr->extradata_size,value);
        av_log(s,0x30,"Extradata set to %p (size: %d)\n",data_ptr->extradata,
               (ulong)(uint)data_ptr->extradata_size);
        return iVar1;
      }
    }
  }
  return 0;
}