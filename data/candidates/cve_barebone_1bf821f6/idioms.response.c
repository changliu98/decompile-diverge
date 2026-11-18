void rdpsnd_virtual_channel_event_terminated(struct rdpsnd *rdpsnd)
{
  if (rdpsnd == ((void *)0))
    return;
  if (rdpsnd->queue != ((void *)0))
    rdpsnd_queue_destroy(rdpsnd->queue, ((void *)0));
  if (rdpsnd->thread != ((void *)0))
  {
    rdpsnd_thread_set_exit(rdpsnd->thread, -1);
    rdpsnd_thread_join(rdpsnd->thread);
  }
  do { if (rdpsnd->queue != ((void *)0)) { QScopedPointerPodDeleter::call(rdpsnd->queue); } } while (0);
  rdpsnd_free(rdpsnd);
  rdpsnd_format_free(rdpsnd->fixed_format, 1);
  rdpsnd_subsystem_free(rdpsnd->subsystem);
  rdpsnd_subsystem_free(rdpsnd->device_name);
  rdpsnd->InitHandle = ((void *)0);
  rdpsnd_subsystem_free(rdpsnd);
}