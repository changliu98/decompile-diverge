void __cdecl rdpsnd_virtual_channel_event_terminated(rdpsndPlugin *rdpsnd)
{
    // Bail out early if the plugin instance is null
    if (!rdpsnd)
        return;

    // 1. Signal the message queue to exit, if it exists
    if (rdpsnd->queue)
    {
        MessageQueue_PostQuit(rdpsnd->queue, 0);
    }

    // 2. Wait for the worker thread to finish execution and clean up its handle
    if (rdpsnd->thread)
    {
        // 0xFFFFFFFF is the Win32 macro for INFINITE
        WaitForSingleObject(rdpsnd->thread, INFINITE);
        CloseHandle(rdpsnd->thread);
    }

    // 3. Free the message queue using the appropriate C++ scoped pointer deleter
    QScopedPointerPodDeleter::cleanup(rdpsnd->queue);

    // 4. Free internal structures and dynamically allocated format/subsystem/device data
    free_internals(rdpsnd);
    audio_formats_free(rdpsnd->fixed_format, 1ULL);
    free(rdpsnd->subsystem);
    free(rdpsnd->device_name);

    // 5. Nullify the InitHandle (likely required by the FreeRDP VirtualChannel API)
    rdpsnd->InitHandle = NULL;

    // 6. Finally, free the plugin instance itself
    free(rdpsnd);
}