UINT ainput_send_input_event(AInputClientContext *context, UINT64 flags, INT32 x, INT32 y)
{
    BYTE buffer[32];
    wStream sbuffer;
    wStream *s;
    UINT64 time;
    AINPUT_PLUGIN *ainput;
    GENERIC_CHANNEL_CALLBACK *callback;
    UINT error;
    char ebuffer[128];

    memset(buffer, 0, sizeof(buffer));
    memset(&sbuffer, 0, sizeof(sbuffer));
    do { if (!(s = Stream_StaticInit(&sbuffer, buffer, sizeof(buffer)))) { __assert_fail("s", "/work/harness.c", 520, "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)"); } } while (0);
    do { if (!(context)) { __assert_fail("context", "/work/harness.c", 521, "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)"); } } while (0);

    time = winpr_GetTickCount64();

    ainput = (AINPUT_PLUGIN *)context->handle;
    do { if (!(ainput)) { __assert_fail("ainput", "/work/harness.c", 525, "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)"); } } while (0);

    if (ainput->version.major != 1)
    {
        vb_wlog_stub("channels.ainput.client", "Unsupported channel version %u.%u, aborting.", ainput->version.major, ainput->version.minor);
        return 19;
    }

    callback = (GENERIC_CHANNEL_CALLBACK *)ainput->callback;
    do { if (!(callback)) { __assert_fail("callback", "/work/harness.c", 534, "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)"); } } while (0);

    memset(ebuffer, 0, sizeof(ebuffer));
    vb_wlog_stub("channels.ainput.client", "sending timestamp=0x%08lx, flags=%s, %dx%d", time, ainput_flags_to_string(flags, ebuffer, sizeof(ebuffer)), x, y);

    Stream_Write_UINT16_unchecked(s, 2);
    Stream_Write_UINT64(s, time);
    Stream_Write_UINT64(s, flags);
    do { if (!((x) >= (-2147483647-1))) { __assert_fail("(x) >= (-2147483647-1)", "/work/harness.c", 548, "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)"); } } while (0);
    Stream_Write_INT32_unchecked(s, x);
    do { if (!((y) >= (-2147483647-1))) { __assert_fail("(y) >= (-2147483647-1)", "/work/harness.c", 549, "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)"); } } while (0);
    Stream_Write_INT32_unchecked(s, y);
    Stream_SealLength(s);

    do { if (!(callback->channel)) { __assert_fail("callback->channel", "/work/harness.c", 553, "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)"); } } while (0);
    do { if (!(callback->channel->Write)) { __assert_fail("callback->channel->Write", "/work/harness.c", 554, "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)"); } } while (0);
    error = callback->channel->Write(callback->channel, Stream_Length(s), Stream_Buffer(s), NULL);

    return error;
}