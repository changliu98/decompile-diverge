void rdpsnd_virtual_channel_event_terminated(rdpsndPlugin* rdpsnd)
{
	if (rdpsnd)
	{
		if (rdpsnd->queue)
			MessageQueue_PostQuit(rdpsnd->queue, 0);

		if (rdpsnd->thread)
		{
			(void)WaitForSingleObject(rdpsnd->thread, INFINITE);
			(void)CloseHandle(rdpsnd->thread);
		}
		MessageQueue_Free(rdpsnd->queue);

		free_internals(rdpsnd);
		audio_formats_free(rdpsnd->fixed_format, 1);
		free(rdpsnd->subsystem);
		free(rdpsnd->device_name);
		rdpsnd->InitHandle = 0;
	}

	free(rdpsnd);
}