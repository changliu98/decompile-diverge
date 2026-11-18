static int read_image(PPMImageRef image) {
  unsigned char c;
  int raw;
  image->x = read_num(image->fd);
  image->y = read_num(image->fd);
  if (image->x >= image->width || image->y >= image->height) {
    return -1;
  }
  image->w = read_num(image->fd);
  image->h = read_num(image->fd);
  image->w = (image->w < image->width - image->x) ? image->w
                                                  : image->width - image->x;
  image->h = (image->h < image->height - image->y) ? image->h
                                                   : image->height - image->y;
  read(image->fd, &c, 1);
  raw = c & 0x40;
  if (c & 0x80) {
    image->palette.ncolors = 1 << ((c & 7) + 1);
    read(image->fd, image->palette.colors, 3 * image->palette.ncolors);
    image->colormap = &image->palette;
  } else {
    image->colormap = &image->default_colormap;
  }
  return read_image_data(image, raw);
}