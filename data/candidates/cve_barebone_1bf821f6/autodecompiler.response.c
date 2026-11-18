void
rdpsnd_virtual_channel_event_terminated(rdpsnd *r)
{
    if (r != NULL)
    {
        if (r->queue != NULL)
        {
            MessageQueue_PostQuit(r->queue, 0);
        }
        if (r->thread != NULL)
        {
            WaitForSingleObject(r->thread, -1);
            CloseHandle(r->thread);
        }
        __ZN24QScopedPointerPodDeleter7cleanupEPv(r->queue);
        free_internals(r);
        audio_formats_free(r->formats, 1);
        free(r->device_name);
        free(r->driver_name);
        r->is_open = 0;
    }
    free(r);
}