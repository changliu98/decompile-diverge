void rdpsnd_virtual_channel_event_terminated(rdpsndPlugin *rdpsnd)

{
  rdpsndPlugin *rdpsnd_local;
  
  if (rdpsnd != (rdpsndPlugin *)0x0) {
    if (rdpsnd->queue != (wMessageQueue *)0x0) {
      MessageQueue_PostQuit(rdpsnd->queue,0);
    }
    if (rdpsnd->thread != (HANDLE)0x0) {
      WaitForSingleObject(rdpsnd->thread,0xffffffff);
      CloseHandle(rdpsnd->thread);
    }
    MessageQueue_Free(rdpsnd->queue);
    free_internals(rdpsnd);
    audio_formats_free(rdpsnd->fixed_format,1);
    free(rdpsnd->subsystem);
    free(rdpsnd->device_name);
    rdpsnd->InitHandle = (void *)0x0;
  }
  free(rdpsnd);
  return;
}