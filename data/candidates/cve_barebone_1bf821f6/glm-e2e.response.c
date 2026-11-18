void rdpsnd_virtual_channel_event_terminated(struct rdpsnd_plugin* plugin) {
    if (plugin == NULL) {
        return;
    }

    if (plugin->queue != NULL) {
        MessageQueue_PostQuit(plugin->queue, 0);
    }

    if (plugin->thread != NULL) {
        WaitForSingleObject(plugin->thread, 0xFFFFFFFF);
        CloseHandle(plugin->thread);
    }

    MessageQueue_Free(plugin->queue);
    free_internals(plugin);
    audio_formats_free(plugin->formats, 1);
    free(plugin->field_18);
    free(plugin->field_20);
    plugin->field_8 = NULL;

    free(plugin);
}