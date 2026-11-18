static void msf_free_gif_state(MsfGifState * handle) {
    if (handle->previousFrame.pixels) MSF_GIF_FREE(handle->customAllocatorContext, handle->previousFrame.pixels,
                                                   handle->width * handle->height * sizeof(uint32_t));
    if (handle->currentFrame.pixels)  MSF_GIF_FREE(handle->customAllocatorContext, handle->currentFrame.pixels,
                                                   handle->width * handle->height * sizeof(uint32_t));
    if (handle->lzwMem) MSF_GIF_FREE(handle->customAllocatorContext, handle->lzwMem, lzwAllocSize);
    if (handle->tlbMem) MSF_GIF_FREE(handle->customAllocatorContext, handle->tlbMem, tlbAllocSize);
    if (handle->usedMem) MSF_GIF_FREE(handle->customAllocatorContext, handle->usedMem, usedAllocSize);
    for (MsfGifBuffer * node = handle->listHead; node;) {
        MsfGifBuffer * next = node->next; //NOTE: we have to copy the `next` pointer BEFORE freeing the node holding it
        MSF_GIF_FREE(handle->customAllocatorContext, node, offsetof(MsfGifBuffer, data) + node->size);
        node = next;
    }
    handle->listHead = NULL; //this implicitly marks the handle as invalid until the next msf_gif_begin() call
}