void msf_free_gif_state(MsfGifState *handle)

{
  MsfGifBuffer *pMVar1;
  MsfGifBuffer *next;
  MsfGifBuffer *node;
  MsfGifState *handle_local;
  
  if ((handle->previousFrame).pixels != (uint32_t *)0x0) {
    free((handle->previousFrame).pixels);
  }
  if ((handle->currentFrame).pixels != (uint32_t *)0x0) {
    free((handle->currentFrame).pixels);
  }
  if (handle->lzwMem != (int16_t *)0x0) {
    free(handle->lzwMem);
  }
  if (handle->tlbMem != (uint8_t *)0x0) {
    free(handle->tlbMem);
  }
  if (handle->usedMem != (uint8_t *)0x0) {
    free(handle->usedMem);
  }
  node = handle->listHead;
  while (node != (MsfGifBuffer *)0x0) {
    pMVar1 = node->next;
    free(node);
    node = pMVar1;
  }
  handle->listHead = (MsfGifBuffer *)0x0;
  return;
}