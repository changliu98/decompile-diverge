int ainput_send_input_event(void *context, unsigned long flags, int x, int y)
{
  struct AInputClientContext *ainput_context = (AInputClientContext *)context;
  struct AINPUT_PLUGIN *ainput = ((void *)0);
  struct GENERIC_CHANNEL_CALLBACK *channel_callback = ((void *)0);
  struct wStream stream;
  struct wStream *s = ((void *)0);
  struct wStream ebuf;
  unsigned long timestamp = 0;
  char buf[-1];
  char ebuf_str[-1];
  ainput_stream_init(&stream, buf, sizeof(buf));
  ainput_stream_init(&ebuf, ((void *)0), 0);
  s = ainput_stream_get_write_stream(&ebuf, &stream, sizeof(struct wStream));
  if (s == ((void *)0))
    ainput_stream_log_error("s", "/work/harness.c", 520, ainput_send_input_event);
  if (ainput_context == ((void *)0))
    ainput_stream_log_error("context", "/work/harness.c", 521, ainput_send_input_event);
  timestamp = ainput_get_timestamp();
  ainput = ainput_context->handle;
  if (ainput == ((void *)0))
    ainput_stream_log_error("ainput", "/work/harness.c", 525, ainput_send_input_event);
  if (ainput->MajorVersion == 1) {
    channel_callback = ainput->base.listener_callback->channel_callback;
    if (channel_callback == ((void *)0))
      ainput_stream_log_error("callback", "/work/harness.c", 526, ainput_send_input_event);
    ainput_stream_init(ebuf_str, ((void *)0), sizeof(ebuf_str));
    ainput_stream_log_info("channels.ainput.client", "sending timestamp=0x%08lx, flags=%s, %dx%d",
      timestamp, ainput_get_flags_str(flags, ebuf_str, sizeof(ebuf_str)), x, y);
    ainput_stream_write_uint16(s, 2);
    ainput_stream_write_uint64(s, timestamp);
    ainput_stream_write_uint64(s, flags);
    ainput_stream_write_int32(s, x);
    ainput_stream_write_int32(s, y);
    ainput_stream_write_end(s);
    if (channel_callback->channel == ((void *)0))
      ainput_stream_log_error("callback->channel", "/work/harness.c", 545, ainput_send_input_event);
    if (channel_callback->channel->Write == ((void *)0))
      ainput_stream_log_error("callback->channel->Write", "/work/harness.c", 546, ainput_send_input_event);
    int (*Write)(struct IWTSVirtualChannel *channel, unsigned long size, unsigned char *data, void *user) = channel_callback->channel->Write;
    struct IWTSVirtualChannel *channel = channel_callback->channel;
    int ret = ainput_stream_get_stream_size(s);
    unsigned char *data = ainput_stream_get_stream_data(s);
    return Write(channel, ret, data, ((void *)0));
  }
  ainput_stream_log_info("channels.ainput.client", "Unsupported channel version %u.%u, aborting.",
    ainput->MajorVersion, ainput->MinorVersion);
  return 19;
}