BOOL __cdecl resize_vbar_entry(CLEAR_CONTEXT *clear, CLEAR_VBAR_ENTRY *vBarEntry)
{
    // If the current count exceeds the allocated size, we need to resize
    if (vBarEntry->count > vBarEntry->size)
    {
        UINT32 bpp = FreeRDPGetBytesPerPixel(clear->format);
        UINT32 oldPos = bpp * vBarEntry->size;
        UINT32 diffSize = bpp * (vBarEntry->count - vBarEntry->size);
        
        vBarEntry->size = vBarEntry->count;
        
        // Reallocate the pixel buffer to accommodate the new count
        // (Assuming the misidentified chip::ArgParser::HelpOptions::HelpOptions is a standard realloc)
        BYTE *tmp = (BYTE *)realloc(vBarEntry->pixels, (size_t)vBarEntry->count * bpp);
        if (!tmp)
            return 0;
            
        // Zero out the newly allocated memory region
        memset(&tmp[oldPos], 0, diffSize);
        vBarEntry->pixels = tmp;
    }
    
    // Return true if pixels are allocated, or if size is 0 (which implies no pixels are needed)
    return vBarEntry->pixels || !vBarEntry->size;
}