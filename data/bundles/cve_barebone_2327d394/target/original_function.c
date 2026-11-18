static UINT ainput_send_input_event(AInputClientContext* context, UINT64 flags, INT32 x, INT32 y)
{
	AINPUT_PLUGIN* ainput = NULL;
	GENERIC_CHANNEL_CALLBACK* callback = NULL;
	BYTE buffer[32] = { 0 };
	UINT64 time = 0;
	wStream sbuffer = { 0 };
	wStream* s = Stream_StaticInit(&sbuffer, buffer, sizeof(buffer));

	WINPR_ASSERT(s);
	WINPR_ASSERT(context);

	time = GetTickCount64();
	ainput = (AINPUT_PLUGIN*)context->handle;
	WINPR_ASSERT(ainput);

	if (ainput->MajorVersion != AINPUT_VERSION_MAJOR)
	{
		WLog_WARN(TAG, "Unsupported channel version %" PRIu32 ".%" PRIu32 ", aborting.",
		          ainput->MajorVersion, ainput->MinorVersion);
		return CHANNEL_RC_UNSUPPORTED_VERSION;
	}
	callback = ainput->base.listener_callback->channel_callback;
	WINPR_ASSERT(callback);

	{
		char ebuffer[128] = { 0 };
		WLog_VRB(TAG, "sending timestamp=0x%08" PRIx64 ", flags=%s, %" PRId32 "x%" PRId32, time,
		         ainput_flags_to_string(flags, ebuffer, sizeof(ebuffer)), x, y);
	}

	/* Message type */
	Stream_Write_UINT16(s, MSG_AINPUT_MOUSE);

	/* Event data */
	Stream_Write_UINT64(s, time);
	Stream_Write_UINT64(s, flags);
	Stream_Write_INT32(s, x);
	Stream_Write_INT32(s, y);
	Stream_SealLength(s);

	/* ainput back what we have received. AINPUT does not have any message IDs. */
	WINPR_ASSERT(callback->channel);
	WINPR_ASSERT(callback->channel->Write);
	return callback->channel->Write(callback->channel, (ULONG)Stream_Length(s), Stream_Buffer(s),
	                                NULL);
}