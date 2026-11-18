int imagetopnm(opj_image_t *image, const char *filename, int force_pgm) {
  const char *p = filename;
  unsigned char *alpha = NULL;
  int precision = image->comps[0].prec;
  if (precision > 16) {
    fprintf(stderr,
            "%s:%d:imagetopnm\n\tprecision %d is larger than 16\n\t: refused.\n",
            "/work/harness.c", 161, precision);
    return 1;
  }
  while (*p) p++;
  p -= 2;
  int is_gray = (*p == 'g' || *p == 'G');
  unsigned int num_comps = image->numcomps;
  if (is_gray) num_comps = 1;
  if (!force_pgm &&
      (num_comps == 2 || (num_comps > 2 && image->comps[0].w ==
                                               image->comps[1].w &&
                           image->comps[1].w == image->comps[2].w &&
                           image->comps[0].h == image->comps[1].h &&
                           image->comps[1].h == image->comps[2].h &&
                           image->comps[0].prec == image->comps[1].prec &&
                           image->comps[1].prec == image->comps[2].prec))) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
      fprintf(stderr, "ERROR -> failed to open %s for writing\n", filename);
      return 1;
    }
    int width = image->comps[0].w;
    int height = image->comps[0].h;
    int is_rgb = (num_comps == 4 || num_comps == 2);
    unsigned char *data = image->comps[0].data;
    unsigned char *data1 = NULL;
    unsigned char *data2 = NULL;
    if (num_comps > 2) {
      data1 = image->comps[1].data;
      data2 = image->comps[2].data;
    }
    int offset;
    if (is_rgb) {
      fprintf(fp,
              "P7\n# OpenJPEG-%s\nWIDTH %d\nHEIGHT %d\nDEPTH %u\nMAXVAL "
              "%d\nTUPLTYPE %s\nENDHDR\n",
              opj_version(), width, height, num_comps, (1 << precision) - 1,
              num_comps > 2 ? "RGB_ALPHA" : "GRAYSCALE_ALPHA");
      alpha = image->comps[num_comps - 1].data;
      offset = image->comps[num_comps - 1].sgnd ? (1 << (image->comps[num_comps - 1].prec - 1))
                                                : 0;
    } else {
      fprintf(fp, "P6\n# OpenJPEG-%s\n%d %d\n%d\n", opj_version(), width,
              height, (1 << precision) - 1);
      offset = 0;
    }
    int offset0 = image->comps[0].sgnd ? (1 << (image->comps[0].prec - 1)) : 0;
    int offset1 = 0;
    int offset2 = 0;
    if (num_comps > 2) {
      offset1 = image->comps[1].sgnd ? (1 << (image->comps[1].prec - 1)) : 0;
      offset2 = image->comps[2].sgnd ? (1 << (image->comps[2].prec - 1)) : 0;
    }
    int i;
    for (i = 0; i < width * height; i++) {
      if (precision > 8) {
        int val = offset0 + *data++;
        if (val > 65535)
          val = 65535;
        else if (val < 0)
          val = 0;
        fprintf(fp, "%c%c", (val >> 8) & 0xff, val & 0xff);
        if (num_comps > 2) {
          val = offset1 + *data1++;
          if (val > 65535)
            val = 65535;
          else if (val < 0)
            val = 0;
          fprintf(fp, "%c%c", (val >> 8) & 0xff, val & 0xff);
          val = offset2 + *data2++;
          if (val > 65535)
            val = 65535;
          else if (val < 0)
            val = 0;
          fprintf(fp, "%c%c", (val >> 8) & 0xff, val & 0xff);
        }
        if (is_rgb) {
          val = offset + *alpha++;
          if (val > 65535)
            val = 65535;
          else if (val < 0)
            val = 0;
          fprintf(fp, "%c%c", (val >> 8) & 0xff, val & 0xff);
        }
      } else {
        int val = *data++;
        if (val > 255)
          val = 255;
        else if (val < 0)
          val = 0;
        fprintf(fp, "%c", val);
        if (num_comps > 2) {
          val = *data1++;
          if (val > 255)
            val = 255;
          else if (val < 0)
            val = 0;
          fprintf(fp, "%c", val);
          val = *data2++;
          if (val > 255)
            val = 255;
          else if (val < 0)
            val = 0;
          fprintf(fp, "%c", val);
        }
        if (is_rgb) {
          val = *alpha++;
          if (val > 255)
            val = 255;
          else if (val < 0)
            val = 0;
          fprintf(fp, "%c", val);
        }
      }
    }
    fclose(fp);
    return 0;
  } else if (image->numcomps > num_comps) {
    fprintf(stderr, "WARNING -> [PGM file] Only the first component\n");
    fprintf(stderr, "           is written to the file\n");
  }
  char *filename_comp = malloc(strlen(filename) + 8);
  if (!filename_comp) {
    fprintf(stderr, "imagetopnm: memory out\n");
    return 1;
  }
  unsigned int compno;
  for (compno = 0; compno < num_comps; compno++) {
    if (num_comps > 1) {
      unsigned int len = strlen(filename) - 4;
      strncpy(filename_comp, filename, len);
      sprintf(filename_comp + len, "_%u.pgm", compno);
    } else {
      sprintf(filename_comp, "%s", filename);
    }
    FILE *fp = fopen(filename_comp, "wb");
    if (!fp) {
      fprintf(stderr, "ERROR -> failed to open %s for writing\n",
              filename_comp);
      free(filename_comp);
      return 1;
    }
    int width = image->comps[compno].w;
    int height = image->comps[compno].h;
    int precision = image->comps[compno].prec;
    fprintf(fp, "P5\n#OpenJPEG-%s\n%d %d\n%d\n", opj_version(), width, height,
            (1 << precision) - 1);
    unsigned char *data = image->comps[compno].data;
    int offset = image->comps[compno].sgnd ? (1 << (image->comps[compno].prec - 1))
                                           : 0;
    int i;
    if (precision > 8) {
      for (i = 0; i < width * height; i++) {
        int val = offset + *data++;
        if (val > 65535)
          val = 65535;
        else if (val < 0)
          val = 0;
        fprintf(fp, "%c%c", (val >> 8) & 0xff, val & 0xff);
      }
    } else {
      for (i = 0; i < width * height; i++) {
        int val = *data++ + offset;
        if (val > 255)
          val = 255;
        else if (val < 0)
          val = 0;
        fprintf(fp, "%c", val);
      }
    }
    fclose(fp);
  }
  free(filename_comp);
  return 0;
}