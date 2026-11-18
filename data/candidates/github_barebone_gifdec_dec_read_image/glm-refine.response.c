int __cdecl read_image(gd_GIF *gif)
{
    uint16_t fh;
    uint16_t fw;
    int interlace;
    uint8_t fisrz;
    
    // Read frame position
    gif->fx = read_num(gif->fd);
    gif->fy = read_num(gif->fd);
    
    // Validate frame offset
    if (gif->fx >= (int)gif->width || gif->fy >= (int)gif->height)
        return -1;
        
    // Read frame dimensions
    gif->fw = read_num(gif->fd);
    gif->fh = read_num(gif->fd);
    
    // Clamp frame width to remain within image bounds
    if (gif->fw >= gif->width - gif->fx)
        fw = gif->width - gif->fx;
    else
        fw = gif->fw;
    gif->fw = fw;
    
    // Clamp frame height to remain within image bounds
    if (gif->fh >= gif->height - gif->fy)
        fh = gif->height - gif->fy;
    else
        fh = gif->fh;
    gif->fh = fh;
    
    // Read Image Descriptor's packed byte (LCT flag, interlace flag, LCT size)
    read(gif->fd, &fisrz, 1uLL);
    
    interlace = fisrz & 0x40;
    
    // Check if a Local Color Table (LCT) is present
    if ((fisrz & 0x80) != 0)
    {
        gif->lct.size = 1 << ((fisrz & 7) + 1);
        read(gif->fd, gif->lct.colors, 3 * gif->lct.size);
        gif->palette = &gif->lct;
    }
    else
    {
        // Use the Global Color Table (GCT) instead
        gif->palette = &gif->gct;
    }
    
    return read_image_data(gif, interlace);
}