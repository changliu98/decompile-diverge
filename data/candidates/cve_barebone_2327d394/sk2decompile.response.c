DWORD ainput_send_input_event(vb_channel_t* channel, DWORD flags, INT32 x,
                              INT32 y) {
  ainput_channel_t* ainput_channel = NULL;
  vb_channel_client_t* client = NULL;
  unsigned char buffer[32];
  UINT64 timestamp = 0;
  Stream s;
  Stream* stream;
  memset(buffer, 0, sizeof(buffer));
  timestamp = 0;
  memset(&s, 0, sizeof(s));
  stream = Stream_StaticInit(&s, buffer, sizeof(buffer));
  assert(stream);
  assert(channel);
  timestamp = winpr_GetTickCount64();
  ainput_channel = (ainput_channel_t*)channel->data;
  assert(ainput_channel);
  if (ainput_channel->version_major != 1) {
    vb_wlog_stub("channels.ainput.client",
                 "Unsupported channel version %u.%u, aborting.",
                 ainput_channel->version_major, ainput_channel->version_minor);
    return 19;
  }
  client = ainput_channel->server->client;
  assert(client);
  {
    char flags_string[128];
    memset(flags_string, 0, sizeof(flags_string));
    vb_wlog_stub("channels.ainput.client",
                 "sending timestamp=0x%08lx, flags=%s, %dx%d", timestamp,
                 ainput_flags_to_string(flags, flags_string,
                                        sizeof(flags_string)),
                 x, y);
  }
  Stream_Write_UINT16_unchecked(stream, 2);
  Stream_Write_UINT64(stream, timestamp);
  Stream_Write_UINT64(stream, flags);
  Stream_Write_INT32_unchecked(stream, x);
  Stream_Write_INT32_unchecked(stream, y);
  Stream_SealLength(stream);
  assert(client->ops);
  assert(client->ops->send_data);
  client->ops->send_data(client->ops, Stream_Length(stream),
                         Stream_Buffer(stream), NULL);
}