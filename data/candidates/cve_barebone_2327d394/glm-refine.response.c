UINT __cdecl ainput_send_input_event(AInputClientContext *context, UINT64 flags, INT32 x, INT32 y)
{
  char ebuffer[128]; // [rsp+20h] [rbp-120h] BYREF
  wStream *s; // [rsp+A8h] [rbp-98h]
  wStream sbuffer; // [rsp+B0h] [rbp-90h] BYREF
  UINT64 time; // [rsp+E8h] [rbp-58h]
  BYTE buffer[32]; // [rsp+F0h] [rbp-50h] BYREF
  GENERIC_CHANNEL_CALLBACK *callback; // [rsp+110h] [rbp-30h]
  AINPUT_PLUGIN *ainput; // [rsp+118h] [rbp-28h]

  memset(buffer, 0, sizeof(buffer));
  memset(&sbuffer, 0, sizeof(sbuffer));
  s = Stream_StaticInit(&sbuffer, buffer, 0x20uLL);
  if ( !s )
    __assert_fail(
      "s",
      "/work/harness.c",
      0x208u,
      "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)");
  if ( !context )
    __assert_fail(
      "context",
      "/work/harness.c",
      0x209u,
      "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)");
      
  time = winpr_GetTickCount64();
  ainput = (AINPUT_PLUGIN *)context->handle;
  if ( !ainput )
    __assert_fail(
      "ainput",
      "/work/harness.c",
      0x20Du,
      "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)");

  if ( ainput->MajorVersion == 1 )
  {
    callback = ainput->base.listener_callback->channel_callback;
    if ( !callback )
      __assert_fail(
        "callback",
        "/work/harness.c",
        0x216u,
        "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)");
        
    memset(ebuffer, 0, sizeof(ebuffer));
    vb_wlog_stub(
      "channels.ainput.client",
      "sending timestamp=0x%08lx, flags=%s, %dx%d",
      time,
      ainput_flags_to_string(flags, ebuffer, 0x80uLL),
      (unsigned int)x,
      (unsigned int)y);
      
    Stream_Write_UINT16_unchecked(s, 2u);
    Stream_Write_UINT64(s, time);
    Stream_Write_UINT64(s, flags);
    Stream_Write_INT32_unchecked(s, x);
    Stream_Write_INT32_unchecked(s, y);
    Stream_SealLength(s);
    
    if ( !callback->channel )
      __assert_fail(
        "callback->channel",
        "/work/harness.c",
        0x229u,
        "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)");
    if ( !callback->channel->Write )
      __assert_fail(
        "callback->channel->Write",
        "/work/harness.c",
        0x22Au,
        "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)");
        
    return callback->channel->Write(callback->channel, Stream_Length(s), Stream_Buffer(s), 0LL);
  }
  else
  {
    vb_wlog_stub(
      "channels.ainput.client",
      "Unsupported channel version %u.%u, aborting.",
      ainput->MajorVersion,
      ainput->MinorVersion);
    return 19;
  }
}