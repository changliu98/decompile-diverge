void rdpsnd_virtual_channel_event_terminated(rdpsnd_virtual_channel_t* self) {
  if (self) {
    if (self->mq) MessageQueue_PostQuit(self->mq, 0);
    if (self->thread) {
      WaitForSingleObject(self->thread, 0xFFFFFFFF);
      CloseHandle(self->thread);
    }
    do {
      if (self->mq) {
        do {
          if (self->mq) {
            delete self->mq;
            self->mq = 0;
          }
        } while (0);
      }
    } while (0);
    free_internals(self);
    audio_formats_free(self->audio_formats, 1);
    free(self->device_name);
    free(self->device_id);
    self->initialized = 0;
  }
  free(self);
}