int __cdecl imagetopnm(opj_image_t *image, const char *outfile, int force_split)
{
  const char *v3; // rax
  const char *v4; // rdx
  const char *v5; // rax
  int *v6; // rax
  int *v7; // rax
  int *v8; // rax
  int *v9; // rax
  size_t v10; // rax
  const char *v11; // rax
  int v13; // [rsp+1Ch] [rbp-F4h]
  int v14; // [rsp+2Ch] [rbp-E4h]
  int v15; // [rsp+30h] [rbp-E0h]
  int v16; // [rsp+34h] [rbp-DCh]
  int v17; // [rsp+44h] [rbp-CCh]
  bool v18; // [rsp+56h] [rbp-BAh]
  bool v19; // [rsp+57h] [rbp-B9h]
  size_t dotpos; // [rsp+58h] [rbp-B8h]
  const char *tt; // [rsp+68h] [rbp-A8h]
  char *destname; // [rsp+70h] [rbp-A0h]
  const char *tmp; // [rsp+78h] [rbp-98h]
  const char *tmpa; // [rsp+78h] [rbp-98h]
  FILE *fdest; // [rsp+80h] [rbp-90h]
  FILE *fdesta; // [rsp+80h] [rbp-90h]
  int v; // [rsp+8Ch] [rbp-84h]
  int va; // [rsp+8Ch] [rbp-84h]
  int vb; // [rsp+8Ch] [rbp-84h]
  int vc; // [rsp+8Ch] [rbp-84h]
  int vd; // [rsp+8Ch] [rbp-84h]
  int ve; // [rsp+8Ch] [rbp-84h]
  int vf; // [rsp+8Ch] [rbp-84h]
  int vg; // [rsp+8Ch] [rbp-84h]
  int vh; // [rsp+8Ch] [rbp-84h]
  int vi; // [rsp+8Ch] [rbp-84h]
  int prec; // [rsp+90h] [rbp-80h]
  int preca; // [rsp+90h] [rbp-80h]
  int adjustA; // [rsp+A8h] [rbp-68h]
  int adjustB; // [rsp+ACh] [rbp-64h]
  int adjustG; // [rsp+B0h] [rbp-60h]
  unsigned int ncomp; // [rsp+B8h] [rbp-58h]
  unsigned int compno; // [rsp+BCh] [rbp-54h]
  int i; // [rsp+C0h] [rbp-50h]
  int ia; // [rsp+C0h] [rbp-50h]
  int ib; // [rsp+C0h] [rbp-50h]
  unsigned int hr; // [rsp+C8h] [rbp-48h]
  unsigned int hra; // [rsp+C8h] [rbp-48h]
  unsigned int wr; // [rsp+CCh] [rbp-44h]
  unsigned int wra; // [rsp+CCh] [rbp-44h]
  int *alpha; // [rsp+D0h] [rbp-40h]
  int *blue; // [rsp+D8h] [rbp-38h]
  int *green; // [rsp+E0h] [rbp-30h]
  int *red; // [rsp+E8h] [rbp-28h]
  int *reda; // [rsp+E8h] [rbp-28h]

  tmp = outfile;
  alpha = 0LL;
  prec = image->comps->prec;
  if ( prec <= 16 )
  {
    while ( *tmp )
      ++tmp;
    tmpa = tmp - 2;
    v19 = 1;
    if ( *tmpa != 103 )
      v19 = *tmpa == 71;
    ncomp = image->numcomps;
    if ( v19 )
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
      if ( fdest )
      {
        wr = image->comps->w;
        hr = image->comps->h;
        v18 = 1;
        if ( ncomp != 4 )
          v18 = ncomp == 2;
        red = image->comps->data;
        if ( ncomp <= 2 )
        {
          blue = 0LL;
          green = 0LL;
        }
        else
        {
          green = image->comps[1].data;
          blue = image->comps[2].data;
        }
        if ( v18 )
        {
          v3 = "GRAYSCALE_ALPHA";
          if ( ncomp > 2 )
            v3 = "RGB_ALPHA";
          tt = v3;
          v4 = opj_version();
          fprintf(
            fdest,
            "P7\n# OpenJPEG-%s\nWIDTH %d\nHEIGHT %d\nDEPTH %u\nMAXVAL %d\nTUPLTYPE %s\nENDHDR\n",
            v4,
            wr,
            hr,
            ncomp,
            (1 << prec) - 1,
            tt);
          alpha = image->comps[(unsigned __int64)(ncomp - 1)].data;
          if ( image->comps[(unsigned __int64)(ncomp - 1)].sgnd )
            v17 = 1 << (LOBYTE(image->comps[(unsigned __int64)(ncomp - 1)].prec) - 1);
          else
            v17 = 0;
          adjustA = v17;
        }
        else
        {
          v5 = opj_version();
          fprintf(fdest, "P6\n# OpenJPEG-%s\n%d %d\n%d\n", v5, wr, hr, (unsigned int)((1 << prec) - 1));
          adjustA = 0;
        }
        if ( image->comps->sgnd )
          v16 = 1 << (LOBYTE(image->comps->prec) - 1);
        else
          v16 = 0;
        if ( ncomp <= 2 )
        {
          adjustB = 0;
          adjustG = 0;
        }
        else
        {
          if ( image->comps[1].sgnd )
            v15 = 1 << (LOBYTE(image->comps[1].prec) - 1);
          else
            v15 = 0;
          adjustG = v15;
          if ( image->comps[2].sgnd )
            v14 = 1 << (LOBYTE(image->comps[2].prec) - 1);
          else
            v14 = 0;
          adjustB = v14;
        }
        for ( i = 0; i < (int)(hr * wr); ++i )
        {
          if ( prec <= 8 )
          {
            v6 = red++;
            vd = *v6;
            if ( *v6 <= 255 )
            {
              if ( vd < 0 )
                LOBYTE(vd) = 0;
            }
            else
            {
              LOBYTE(vd) = -1;
            }
            fprintf(fdest, "%c", (unsigned __int8)vd);
            if ( ncomp > 2 )
            {
              v7 = green++;
              ve = *v7;
              if ( *v7 <= 255 )
              {
                if ( ve < 0 )
                  LOBYTE(ve) = 0;
              }
              else
              {
                LOBYTE(ve) = -1;
              }
              fprintf(fdest, "%c", (unsigned __int8)ve);
              v8 = blue++;
              vf = *v8;
              if ( *v8 <= 255 )
              {
                if ( vf < 0 )
                  LOBYTE(vf) = 0;
              }
              else
              {
                LOBYTE(vf) = -1;
              }
              fprintf(fdest, "%c", (unsigned __int8)vf);
            }
            if ( v18 )
            {
              v9 = alpha++;
              vg = *v9;
              if ( *v9 <= 255 )
              {
                if ( vg < 0 )
                  LOBYTE(vg) = 0;
              }
              else
              {
                LOBYTE(vg) = -1;
              }
              fprintf(fdest, "%c", (unsigned __int8)vg);
            }
          }
          else
          {
            v = v16 + *red++;
            if ( v <= 0xFFFF )
            {
              if ( v < 0 )
                LOWORD(v) = 0;
            }
            else
            {
              LOWORD(v) = -1;
            }
            fprintf(fdest, "%c%c", BYTE1(v), (unsigned __int8)v);
            if ( ncomp > 2 )
            {
              va = adjustG + *green++;
              if ( va <= 0xFFFF )
              {
                if ( va < 0 )
                  LOWORD(va) = 0;
              }
              else
              {
                LOWORD(va) = -1;
              }
              fprintf(fdest, "%c%c", BYTE1(va), (unsigned __int8)va);
              vb = adjustB + *blue++;
              if ( vb <= 0xFFFF )
              {
                if ( vb < 0 )
                  LOWORD(vb) = 0;
              }
              else
              {
                LOWORD(vb) = -1;
              }
              fprintf(fdest, "%c%c", BYTE1(vb), (unsigned __int8)vb);
            }
            if ( v18 )
            {
              vc = adjustA + *alpha++;
              if ( vc <= 0xFFFF )
              {
                if ( vc < 0 )
                  LOWORD(vc) = 0;
              }
              else
              {
                LOWORD(vc) = -1;
              }
              fprintf(fdest, "%c%c", BYTE1(vc), (unsigned __int8)vc);
            }
          }
        }
        fclose(fdest);
        return 0;
      }
      else
      {
        fprintf(stderr, "ERROR -> failed to open %s for writing\n", outfile);
        return 1;
      }
    }
    else
    {
      if ( image->numcomps > ncomp )
      {
        fprintf(stderr, "WARNING -> [PGM file] Only the first component\n");
        fprintf(stderr, "           is written to the file\n");
      }
      v10 = strlen(outfile);
      destname = (char *)malloc(v10 + 8);
      if ( destname )
      {
        for ( compno = 0; compno < ncomp; ++compno )
        {
          if ( ncomp <= 1 )
          {
            sprintf(destname, "%s", outfile);
          }
          else
          {
            dotpos = strlen(outfile) - 4;
            strncpy(destname, outfile, dotpos);
            sprintf(&destname[dotpos], "_%u.pgm", compno);
          }
          fdesta = fopen(destname, "wb");
          if ( !fdesta )
          {
            fprintf(stderr, "ERROR -> failed to open %s for writing\n", destname);
            free(destname);
            return 1;
          }
          wra = image->comps[(unsigned __int64)compno].w;
          hra = image->comps[(unsigned __int64)compno].h;
          preca = image->comps[(unsigned __int64)compno].prec;
          v11 = opj_version();
          fprintf(fdesta, "P5\n#OpenJPEG-%s\n%d %d\n%d\n", v11, wra, hra, (unsigned int)((1 << preca) - 1));
          reda = image->comps[(unsigned __int64)compno].data;
          if ( image->comps[(unsigned __int64)compno].sgnd )
            v13 = 1 << (LOBYTE(image->comps[(unsigned __int64)compno].prec) - 1);
          else
            v13 = 0;
          if ( preca <= 8 )
          {
            for ( ib = 0; ib < (int)(hra * wra); ++ib )
            {
              vi = v13 + *reda++;
              if ( vi <= 255 )
              {
                if ( vi < 0 )
                  LOBYTE(vi) = 0;
              }
              else
              {
                LOBYTE(vi) = -1;
              }
              fprintf(fdesta, "%c", (unsigned __int8)vi);
            }
          }
          else
          {
            for ( ia = 0; ia < (int)(hra * wra); ++ia )
            {
              vh = v13 + *reda++;
              if ( vh <= 0xFFFF )
              {
                if ( vh < 0 )
                  LOWORD(vh) = 0;
              }
              else
              {
                LOWORD(vh) = -1;
              }
              fprintf(fdesta, "%c%c", BYTE1(vh), (unsigned __int8)vh);
            }
          }
          fclose(fdesta);
        }
        free(destname);
        return 0;
      }
      else
      {
        fprintf(stderr, "imagetopnm: memory out\n");
        return 1;
      }
    }
  }
  else
  {
    fprintf(
      stderr,
      "%s:%d:imagetopnm\n\tprecision %d is larger than 16\n\t: refused.\n",
      "/work/harness.c",
      161LL,
      (unsigned int)prec);
    return 1;
  }
}