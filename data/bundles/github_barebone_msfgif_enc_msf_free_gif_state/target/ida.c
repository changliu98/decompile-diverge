void __cdecl msf_free_gif_state(MsfGifState *handle)
{
  MsfGifBuffer *next; // [rsp+8h] [rbp-18h]
  MsfGifBuffer *node; // [rsp+10h] [rbp-10h]

  if ( handle->previousFrame.pixels )
    free(handle->previousFrame.pixels);
  if ( handle->currentFrame.pixels )
    free(handle->currentFrame.pixels);
  if ( handle->lzwMem )
    free(handle->lzwMem);
  if ( handle->tlbMem )
    free(handle->tlbMem);
  if ( handle->usedMem )
    free(handle->usedMem);
  for ( node = handle->listHead; node; node = next )
  {
    next = node->next;
    free(node);
  }
  handle->listHead = 0LL;
}