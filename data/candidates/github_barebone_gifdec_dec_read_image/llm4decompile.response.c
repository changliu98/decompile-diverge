int read_image(gd_GIF *gif) {
    unsigned char b;

    gif->fx = read_num(gif->fd);
    gif->fy = read_num(gif->fd);
    if (gif->fx >= gif->width || gif->fy >= gif->height)
        return -1;

    gif->fw = read_num(gif->fd);
    gif->fh = read_num(gif->fd);
    if (gif->fw < gif->width - gif->fx)
        gif->fw = gif->width - gif->fx;
    if (gif->fh < gif->height - gif->fy)
        gif->fh = gif->height - gif->fy;

    read(gif->fd, &b, 1);
    if (b & 0x80) {
        gif->lct.size = 1 << ((b & 7) + 1);
        read(gif->fd, gif->lct.colors, gif->lct.size * 3);
        gif->palette = &gif->lct;
    } else {
        gif->palette = &gif->gct;
    }

    return read_image_data(gif, b & 0x40);
}