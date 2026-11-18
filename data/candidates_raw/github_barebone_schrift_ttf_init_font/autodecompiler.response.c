int TTF_Init(TTF_Font *font)
{
  int err;
  unsigned long scalerType, hhea, head;

  if (!is_safe_offset(font, 0, 12)) {
    err = -1;
  } else {
    scalerType = getu32(font, 0);
    if (scalerType != 0x00010000 && scalerType != 0x74727565) {

      err = -1;
    } else if ((err = gettable(font, "head", &head)) < 0) {

      err = -1;
    } else if (!is_safe_offset(font, head, 54)) {

      err = -1;
    } else {
      font->units_per_em = getu16(font, head + 18);
      font->index_to_loc_format = geti16(font, head + 50);

      if ((err = gettable(font, "hhea", &hhea)) < 0) {

        err = -1;
      } else if (!is_safe_offset(font, hhea, 36)) {

        err = -1;
      } else {
        font->num_h_metric = getu16(font, hhea + 34);
        err = 0;
      }
    }
  }

  return err;
}