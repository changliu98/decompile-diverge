void rdpsnd_virtual_channel_event_terminated(rdpsndPlugin *plugin)
{
    // Check if the plugin instance is valid
    if (plugin) {
        // If the message queue exists, post a quit message to stop the thread
        if (plugin->queue) {
            MessageQueue_PostQuit(plugin->queue, 0);
        }
        // If the thread exists, wait for it to terminate and then close its handle
        if (plugin->thread) {
            WaitForSingleObject(plugin->thread, 0xffffffff);
            CloseHandle(plugin->thread);
        }
        // Free the message queue
        MessageQueue_Free(plugin->queue);
        // Free internal resources associated with the plugin
        free_internals(plugin);
        // Free audio format structures
        audio_formats_free(plugin->fixed_format, 1);
        // Free the subsystem string
        free(plugin->subsystem);
        // Free the device name string
        free(plugin->device_name);
        // Clear the initialization handle
        plugin->InitHandle = NULL;
    }
    // Free the plugin instance itself
    free(plugin);
}