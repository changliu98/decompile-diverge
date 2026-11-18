void
rdpsnd_virtual_channel_event_terminated(void *data)
{
    rdpsndPlugin *rdpsnd = (rdpsndPlugin *)data;

    if (rdpsnd != NULL)
    {
        if (rdpsnd->queue != NULL)
        {
            MessageQueue_PostQuit(rdpsnd->queue, 0);
        }

        if (rdpsnd->thread != NULL)
        {
            WaitForSingleObject(rdpsnd->thread, 0xFFFFFFFF);
            CloseHandle(rdpsnd->thread);
        }

        MessageQueue_Free(rdpsnd->queue);

        free_internals(rdpsnd);

        audio_formats_free(rdpsnd->fixed_format, 1);

        free(rdpsnd->subsystem);
        free(rdpsnd->device_name);

        rdpsnd->InitHandle = NULL;
    }

    free(rdpsnd);
}