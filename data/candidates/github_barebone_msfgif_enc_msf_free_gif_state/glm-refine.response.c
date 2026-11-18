void __cdecl msf_free_gif_state(MsfGifState *handle)
{
  MsfGifBuffer *node;

  if (!handle)
    return;

  free(handle->previousFrame.pixels);
  free(handle->currentFrame.pixels);
  free(handle->lzwMem);
  free(handle->tlbMem);
  free(handle->usedMem);

  for (node = handle->listHead; node; )
  {
    MsfGifBuffer *next = node->next;
    free(node);
    node = next;
  }
  
  handle->listHead = NULL;
}