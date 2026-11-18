void msf_free_gif_state(MsfGifState *handle)
{
    if (handle->previousFrame.pixels)
        free(handle->previousFrame.pixels);
    if (handle->currentFrame.pixels)
        free(handle->currentFrame.pixels);
    if (handle->lzwMem)
        free(handle->lzwMem);
    if (handle->tlbMem)
        free(handle->tlbMem);
    if (handle->usedMem)
        free(handle->usedMem);

    MsfGifBuffer *node = handle->listHead;
    while (node)
    {
        MsfGifBuffer *next = node->next;
        free(node);
        node = next;
    }
    handle->listHead = NULL;
}