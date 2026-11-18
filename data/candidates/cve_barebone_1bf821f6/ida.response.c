void __cdecl rdpsnd_virtual_channel_event_terminated(rdpsndPlugin *rdpsnd)
{
  if ( rdpsnd )
  {
    if ( rdpsnd->queue )
      MessageQueue_PostQuit(rdpsnd->queue, 0);
    if ( rdpsnd->thread )
    {
      WaitForSingleObject(rdpsnd->thread, 0xFFFFFFFF);
      CloseHandle(rdpsnd->thread);
    }
    QScopedPointerPodDeleter::cleanup(rdpsnd->queue);
    free_internals(rdpsnd);
    audio_formats_free(rdpsnd->fixed_format, 1uLL);
    free(rdpsnd->subsystem);
    free(rdpsnd->device_name);
    rdpsnd->InitHandle = 0LL;
  }
  free(rdpsnd);
}