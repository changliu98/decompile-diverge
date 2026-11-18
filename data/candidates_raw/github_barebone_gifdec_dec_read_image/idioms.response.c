int gdImageGIFGetFrame(struct gdImage *image)
{
    int interlace;
    unsigned char fisrz;
    struct gdImage *im = (gdImage *) image;
    im->fx = read_int(im->fd);
    im->fy = read_int(im->fd);
    if (im->fx >= im->width || im->fy >= im->height)
        return -1;
    im->fw = read_int(im->fd);
    im->fh = read_int(im->fd);
    if (im->fw >= (im->width - im->fx))
        im->fw = (im->width - im->fx);
    else
        im->fw = im->fw;
    if (im->fh >= (im->height - im->fy))
        im->fh = (im->height - im->fy);
    else
        im->fh = im->fh;
    read_all(im->fd, &fisrz, sizeof(unsigned char));
    interlace = (fisrz & 0x40);
    if (fisrz & 0x80)
    {
        im->lct.size = (1 << (fisrz & 0x07)) + 1;
        read_all(im->fd, im->lct.colors,
            im->lct.size * (sizeof(struct gdBmpColor)));
        im->palette = &im->lct;
    }
    else
    {
        im->palette = &im->gct;
    }
    return gdImageGIFGetLine(im, interlace);
}