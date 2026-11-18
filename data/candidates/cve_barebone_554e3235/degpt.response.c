int parse_matrix_header(char *line,int *width,int *height,double *scale,double *offset)

{
  int iVar1;
  char *pcVar2;
  double dVar3;
  int i;
  char *q;
  char *p;
  double header [4];
  double *offset_local;
  double *scale_local;
  int *height_local;
  int *width_local;
  char *line_local;
  
  p = strchr(line,0xd);
  if ((p != (char *)0x0) || (p = strchr(line,10), p != (char *)0x0)) {
    *p = '\0';
  }
  p = line;
  for (i = 0; pcVar2 = vips_break_token(p," \t"), pcVar2 != (char *)0x0 && i < 4; i = i + 1) {
    iVar1 = vips_strtod(p,header + i);
    if (iVar1 != 0) {
      vips_error("matload","bad number \"%s\"",p);
      return -1;
    }
    p = pcVar2;
  }
  if (i < 4) {
    header[3] = 0.0;
  }
  if (i < 3) {
    header[2] = DAT_00102008;
  }
  if (i < 2) {
    vips_error("matload","%s","no width / height");
  }
  else {
    dVar3 = floor(header[0]);
    if ((dVar3 == header[0]) && (!NAN(dVar3) && !NAN(header[0]))) {
      dVar3 = floor(header[1]);
      if ((dVar3 == header[1]) && (!NAN(dVar3) && !NAN(header[1]))) {
        *width = (int)header[0];
        *height = (int)header[1];
        if ((((0 < *width) && (*width < 0x186a1)) && (0 < *height)) && (*height < 0x186a1)) {
          if ((header[2] == 0.0) && (!NAN(header[2]))) {
            vips_error("mask2vips","%s","zero scale");
            return -1;
          }
          *scale = header[2];
          *offset = header[3];
          return 0;
        }
        vips_error("mask2vips","%s","width / height out of range");
        return -1;
      }
    }
    vips_error("mask2vips","%s","width / height not int");
  }
  return -1;
}