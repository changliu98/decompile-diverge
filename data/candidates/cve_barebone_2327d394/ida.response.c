UINT __cdecl ainput_send_input_event(AInputClientContext *context, UINT64 flags, INT32 x, INT32 y)
{
  const char *v4; // rax
  BYTE *v5; // rdx
  IWTSVirtualChannel *channel; // [rsp+0h] [rbp-140h]
  ULONG v8; // [rsp+Ch] [rbp-134h]
  UINT (*Write)(IWTSVirtualChannel *, ULONG, const BYTE *, void *); // [rsp+10h] [rbp-130h]
  UINT64 v10; // [rsp+18h] [rbp-128h]
  char ebuffer[128]; // [rsp+20h] [rbp-120h] BYREF
  wStream *s; // [rsp+A8h] [rbp-98h]
  wStream sbuffer; // [rsp+B0h] [rbp-90h] BYREF
  UINT64 time; // [rsp+E8h] [rbp-58h]
  BYTE buffer[32]; // [rsp+F0h] [rbp-50h] BYREF
  GENERIC_CHANNEL_CALLBACK *callback; // [rsp+110h] [rbp-30h]
  AINPUT_PLUGIN *ainput; // [rsp+118h] [rbp-28h]
  INT32 ya; // [rsp+120h] [rbp-20h]
  INT32 xa; // [rsp+124h] [rbp-1Ch]
  UINT64 flagsa; // [rsp+128h] [rbp-18h]
  AInputClientContext *contexta; // [rsp+130h] [rbp-10h]

  contexta = context;
  flagsa = flags;
  xa = x;
  ya = y;
  ainput = 0LL;
  callback = 0LL;
  memset(buffer, 0, sizeof(buffer));
  time = 0LL;
  memset(&sbuffer, 0, sizeof(sbuffer));
  s = Stream_StaticInit(&sbuffer, buffer, 0x20uLL);
  if ( !s )
    __assert_fail(
      "s",
      "/work/harness.c",
      0x208u,
      "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)");
  if ( !contexta )
    __assert_fail(
      "context",
      "/work/harness.c",
      0x209u,
      "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)");
  time = winpr_GetTickCount64();
  ainput = (AINPUT_PLUGIN *)contexta->handle;
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
    v10 = time;
    v4 = ainput_flags_to_string(flagsa, ebuffer, 0x80uLL);
    vb_wlog_stub(
      "channels.ainput.client",
      "sending timestamp=0x%08lx, flags=%s, %dx%d",
      v10,
      v4,
      (unsigned int)xa,
      (unsigned int)ya);
    Stream_Write_UINT16_unchecked(s, 2u);
    Stream_Write_UINT64(s, time);
    Stream_Write_UINT64(s, flagsa);
    Stream_Write_INT32_unchecked(s, xa);
    Stream_Write_INT32_unchecked(s, ya);
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
    Write = callback->channel->Write;
    channel = callback->channel;
    v8 = Stream_Length(s);
    v5 = Stream_Buffer(s);
    return Write(channel, v8, v5, 0LL);
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