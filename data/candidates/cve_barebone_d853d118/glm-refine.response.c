int __cdecl imagetopnm(opj_image_t *image, const char *outfile, int force_split)
{
  const char *tt;
  char *destname;
  FILE *fdest;
  int adjustR, adjustG, adjustB, adjustA;
  unsigned int ncomp;
  unsigned int compno;
  int i;
  unsigned int hr, wr;
  int *alpha, *blue, *green, *red;
  int prec;
  bool has_alpha;
  int v;

  prec = image->comps->prec;
  if ( prec > 16 )
  {
    fprintf(
      stderr,
      "%s:%d:imagetopnm\n\tprecision %d is larger than 16\n\t: refused.\n",
      "/work/harness.c",
      161LL,
      (unsigned int)prec);
    return 1;
  }

  // Check if the file extension is ".pgm" or ".PGM"
  size_t len = strlen(outfile);
  bool is_pgm = (len >= 2 && (outfile[len - 2] == 'g' || outfile[len - 2] == 'G') && outfile[len - 1] == 'm');
  
  ncomp = image->numcomps;
  if ( is_pgm )
    ncomp = 1;

  if ( !force_split
    && (ncomp == 2
     || ncomp > 2
     && image->comps->dx == image->comps[1].dx
     && image->comps[1].dx == image->comps[2].dx
     && image->comps->dy == image->comps[1].dy
     && image->comps[1].dy == image->comps[2].dy
     && image->comps->prec == image->comps[1].prec
     && image->comps[1].prec == image->comps[2].prec) )
  {
    fdest = fopen(outfile, "wb");
    if ( !fdest )
    {
      fprintf(stderr, "ERROR -> failed to open %s for writing\n", outfile);
      return 1;
    }

    wr = image->comps->w;
    hr = image->comps->h;
    has_alpha = (ncomp == 4 || ncomp == 2);
    red = image->comps->data;
    if ( ncomp <= 2 )
    {
      blue = NULL;
      green = NULL;
    }
    else
    {
      green = image->comps[1].data;
      blue = image->comps[2].data;
    }

    if ( has_alpha )
    {
      tt = (ncomp > 2) ? "RGB_ALPHA" : "GRAYSCALE_ALPHA";
      fprintf(
        fdest,
        "P7\n# OpenJPEG-%s\nWIDTH %d\nHEIGHT %d\nDEPTH %u\nMAXVAL %d\nTUPLTYPE %s\nENDHDR\n",
        opj_version(),
        wr,
        hr,
        ncomp,
        (1 << prec) - 1,
        tt);
      alpha = image->comps[(unsigned __int64)(ncomp - 1)].data;
      adjustA = image->comps[(unsigned __int64)(ncomp - 1)].sgnd ? (1 << (LOBYTE(image->comps[(unsigned __int64)(ncomp - 1)].prec) - 1)) : 0;
    }
    else
    {
      fprintf(fdest, "P6\n# OpenJPEG-%s\n%d %d\n%d\n", opj_version(), wr, hr, (unsigned int)((1 << prec) - 1));
      adjustA = 0;
    }

    adjustR = image->comps->sgnd ? (1 << (LOBYTE(image->comps->prec) - 1)) : 0;
    if ( ncomp <= 2 )
    {
      adjustB = 0;
      adjustG = 0;
    }
    else
    {
      adjustG = image->comps[1].sgnd ? (1 << (LOBYTE(image->comps[1].prec) - 1)) : 0;
      adjustB = image->comps[2].sgnd ? (1 << (LOBYTE(image->comps[2].prec) - 1)) : 0;
    }

    for ( i = 0; i < (int)(hr * wr); ++i )
    {
      if ( prec <= 8 )
      {
        v = adjustR + *red++;
        if ( v > 255 ) v = 255;
        else if ( v < 0 ) v = 0;
        fprintf(fdest, "%c", (unsigned __int8)v);

        if ( ncomp > 2 )
        {
          v = adjustG + *green++;
          if ( v > 255 ) v = 255;
          else if ( v < 0 ) v = 0;
          fprintf(fdest, "%c", (unsigned __int8)v);

          v = adjustB + *blue++;
          if ( v > 255 ) v = 255;
          else if ( v < 0 ) v = 0;
          fprintf(fdest, "%c", (unsigned __int8)v);
        }

        if ( has_alpha )
        {
          v = adjustA + *alpha++;
          if ( v > 255 ) v = 255;
          else if ( v < 0 ) v = 0;
          fprintf(fdest, "%c", (unsigned __int8)v);
        }
      }
      else
      {
        v = adjustR + *red++;
        if ( v > 0xFFFF ) v = 0xFFFF;
        else if ( v < 0 ) v = 0;
        fprintf(fdest, "%c%c", BYTE1(v), (unsigned __int8)v);

        if ( ncomp > 2 )
        {
          v = adjustG + *green++;
          if ( v > 0xFFFF ) v = 0xFFFF;
          else if ( v < 0 ) v = 0;
          fprintf(fdest, "%c%c", BYTE1(v), (unsigned __int8)v);

          v = adjustB + *blue++;
          if ( v > 0xFFFF ) v = 0xFFFF;
          else if ( v < 0 ) v = 0;
          fprintf(fdest, "%c%c", BYTE1(v), (unsigned __int8)v);
        }

        if ( has_alpha )
        {
          v = adjustA + *alpha++;
          if ( v > 0xFFFF ) v = 0xFFFF;
          else if ( v < 0 ) v = 0;
          fprintf(fdest, "%c%c", BYTE1(v), (unsigned __int8)v);
        }
      }
    }
    fclose(fdest);
    return 0;
  }
  else
  {
    if ( image->numcomps > ncomp )
    {
      fprintf(stderr, "WARNING -> [PGM file] Only the first component\n");
      fprintf(stderr, "           is written to the file\n");
    }
    destname = (char *)malloc(strlen(outfile) + 8);
    if ( !destname )
    {
      fprintf(stderr, "imagetopnm: memory out\n");
      return 1;
    }

    for ( compno = 0; compno < ncomp; ++compno )
    {
      if ( ncomp <= 1 )
      {
        sprintf(destname, "%s", outfile);
      }
      else
      {
        size_t dotpos = strlen(outfile) - 4;
        strncpy(destname, outfile, dotpos);
        sprintf(&destname[dotpos], "_%u.pgm", compno);
      }

      fdest = fopen(destname, "wb");
      if ( !fdest )
      {
        fprintf(stderr, "ERROR -> failed to open %s for writing\n", destname);
        free(destname);
        return 1;
      }

      unsigned int w = image->comps[(unsigned __int64)compno].w;
      unsigned int h = image->comps[(unsigned __int64)compno].h;
      int p = image->comps[(unsigned __int64)compno].prec;
      fprintf(fdest, "P5\n#OpenJPEG-%s\n%d %d\n%d\n", opj_version(), w, h, (unsigned int)((1 << p) - 1));
      
      int *data = image->comps[(unsigned __int64)compno].data;
      int adjust = image->comps[(unsigned __int64)compno].sgnd ? (1 << (LOBYTE(image->comps[(unsigned __int64)compno].prec) - 1)) : 0;

      if ( p <= 8 )
      {
        for ( i = 0; i < (int)(h * w); ++i )
        {
          v = adjust + *data++;
          if ( v > 255 ) v = 255;
          else if ( v < 0 ) v = 0;
          fprintf(fdest, "%c", (unsigned __int8)v);
        }
      }
      else
      {
        for ( i = 0; i < (int)(h * w); ++i )
        {
          v = adjust + *data++;
          if ( v > 0xFFFF ) v = 0xFFFF;
          else if ( v < 0 ) v = 0;
          fprintf(fdest, "%c%c", BYTE1(v), (unsigned __int8)v);
        }
      }
      fclose(fdest);
    }
    free(destname);
    return 0;
  }
}