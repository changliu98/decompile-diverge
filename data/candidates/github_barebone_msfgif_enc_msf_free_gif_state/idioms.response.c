void msf_free_gif_state(struct MsfGifState *handle)
{
  struct MsfGifBuffer *current;
  struct MsfGifBuffer *next;
  if (handle->previousFrame.pixels)
    msf_gif_free_buffer (handle->previousFrame.pixels);
  if (handle->currentFrame.pixels)
    msf_gif_free_buffer (handle->currentFrame.pixels);
  if (handle->lzwMem)
    msf_gif_free_buffer (handle->lzwMem);
  if (handle->tlbMem)
    msf_gif_free_buffer (handle->tlbMem);
  if (handle->usedMem)
    msf_gif_free_buffer (handle->usedMem);
  current = handle->listHead;
  while (current)
  {
    next = current->next;
    msf_gif_free_buffer (current);
    current = next;
  }
  handle->listHead = ((void *)0);
}