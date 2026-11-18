void bmp_iter_next(bmp_iterator *iter) {
  iter->mask >>= 1;
  if (iter->mask == 0) {
    iter->index++;
    iter->mask = iter->first_mask;
  }
}