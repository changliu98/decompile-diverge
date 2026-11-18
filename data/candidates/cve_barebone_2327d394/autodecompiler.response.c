static UINT ainput_send_input_event(AInputClientContext * context, UINT64 flags, INT32 x, INT32 y)
{
 AINPUT_CHANNEL *ainput = NULL;
 AINPUT_CALLBACK *callback = NULL;
 wStream s;
 wStream * _s = NULL; { (s).ptr = NULL; (s).capacity = 0; (s).size = 0; }; { (s).ptr = (BYTE*)calloc(1, (32)); (s).capacity = (32); (s).size = 0; };
 { if (!(_s = Stream_StaticInit(&(s), (BYTE*)calloc(1, (32)), (32)))) { return (19); } };
 { if (!(context)) { ___assert_fail("context", "harness.c", 521, "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)"); } };
 UINT64 timestamp = winpr_GetTickCount64();
 { if (!((ainput = (AINPUT_CHANNEL *) context->handle))) { ___assert_fail("ainput", "harness.c", 525, "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)"); } };
 if (ainput->header.version != 1)
 {
  { vb_wlog_stub("channels." "ainput" ".client", "Unsupported channel version %u.%u, aborting.", ainput->header.major, ainput->header.minor); };
  return (19);
 }
 { if (!((callback = (AINPUT_CALLBACK *) ainput->channel->handle))) { ___assert_fail("callback", "harness.c", 534, "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)"); } };
 { memset(&(s), 0, sizeof(s)); s.timestamp = timestamp; vb_wlog_stub("channels." "ainput" ".client", "sending timestamp=0x%08lx, flags=%s, %dx%d", s.timestamp, ainput_flags_to_string(flags, (char*)((void*)(&((s).ptr[0])))), x, y); };
 { Stream_Write_UINT16_unchecked(_s, 2); };
 { Stream_Write_UINT64(_s, timestamp); };
 { Stream_Write_UINT64(_s, flags); };
 { { if (!((x) <= (2147483647))) { ___assert_fail("(x) <= (2147483647)", "harness.c", 548, "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)"); } }; { if (!((x) >= (-2147483647-1))) { ___assert_fail("(x) >= (-2147483647-1)", "harness.c", 548, "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)"); } }; Stream_Write_INT32_unchecked(_s, x); };
 { { if (!((y) <= (2147483647))) { ___assert_fail("(y) <= (2147483647)", "harness.c", 549, "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)"); } }; { if (!((y) >= (-2147483647-1))) { ___assert_fail("(y) >= (-2147483647-1)", "harness.c", 549, "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)"); } }; Stream_Write_INT32_unchecked(_s, y); };
 { Stream_SealLength(_s); };
 { if (!((callback->channel))) { ___assert_fail("callback->channel", "harness.c", 553, "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)"); } };
 { if (!((callback->channel->Write))) { ___assert_fail("callback->channel->Write", "harness.c", 554, "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)"); } };
 return callback->channel->Write(callback->channel, Stream_Length(_s), Stream_Buffer(_s), NULL);
}