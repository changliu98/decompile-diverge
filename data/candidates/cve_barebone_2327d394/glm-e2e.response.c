int ainput_send_input_event(void* context, uint64_t flags, int32_t x, int32_t y) {
    int ret = 0;
    struct ainput_ctx* ainput = NULL;
    struct channel_data* channel = NULL;
    uint64_t timestamp = 0;
    uint8_t stream_buf[0x38];
    uint8_t buffer[0x20];
    wStream s;
    char str_buf[0x80];

    memset(&s, 0, sizeof(s));
    memset(stream_buf, 0, sizeof(stream_buf));
    wStream* s_ptr = Stream_StaticInit(&s, stream_buf, 0x20);
    assert(s_ptr != NULL);
    assert(context != NULL);

    timestamp = winpr_GetTickCount64();
    ainput = *(struct ainput_ctx**)context;
    assert(ainput != NULL);

    if (ainput->state != 1) {
        vb_wlog_stub("WLOG_WARN", "state %d version %d", ainput->state, ainput->version);
        return 0x13;
    }

    channel = ainput->channel_data->send_func_ptr;
    assert(channel != NULL);

    memset(str_buf, 0, sizeof(str_buf));
    ainput_flags_to_string(flags, str_buf, 0x80);
    vb_wlog_stub("WLOG_DEBUG", "flags %s x %d y %d", str_buf, x, y);

    Stream_Write_UINT16_unchecked(&s, 2);
    Stream_Write_UINT64(&s, timestamp);
    Stream_Write_UINT64(&s, flags);

    assert(x <= 0x7fffffff);
    assert(x >= -0x80000000);
    Stream_Write_INT32_unchecked(&s, x);

    assert(y <= 0x7fffffff);
    assert(y >= -0x80000000);
    Stream_Write_INT32_unchecked(&s, y);

    Stream_SealLength(&s);

    assert(channel->hooks != NULL);
    assert(channel->hooks->send_func_ptr != NULL);

    int (*send_func)(void*, uint32_t, uint8_t*, void*) = channel->hooks->send_func_ptr;
    void* send_ctx = channel->hooks;
    uint32_t len = Stream_Length(&s);
    uint8_t* buf = Stream_Buffer(&s);

    ret = send_func(send_ctx, len, buf, NULL);

    return ret;
}