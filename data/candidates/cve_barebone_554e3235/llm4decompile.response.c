int
parse_matrix_header(char *line, int *width, int *height,
      double *scale, double *offset)
{
 double header[4];
 char *p, *q;
 int n;

 q = strchr(line, '\r');
 if(q)
  *q = '\0';
 else
  q = strchr(line, '\n');
 if(q)
  *q = '\0';

 p = line;
 for(n = 0; (q = vips_break_token(p, " \t")) && n < 4; n++) {
  if(vips_strtod(p, &header[n])) {
   vips_error("matload", "bad number \"%s\"", p);
   return -1;
  }
  p = q;
 }

 if(n < 4)
  header[3] = 0.0;
 if(n < 3)
  header[2] = 1.0;
 if(n < 2) {
  vips_error("matload", "%s", "no width / height");
  return -1;
 }

 if(floor(header[0]) != header[0] || floor(header[1]) != header[1]) {
  vips_error("mask2vips", "%s", "width / height not int");
  return -1;
 }

 *width = (int)header[0];
 *height = (int)header[1];

 if(*width < 1 || *width > 100000 ||
    *height < 1 || *height > 100000) {
  vips_error("mask2vips", "%s", "width / height out of range");
  return -1;
 }

 if(header[2] == 0.0) {
  vips_error("mask2vips", "%s", "zero scale");
  return -1;
 }

 *scale = header[2];
 *offset = header[3];

 return 0;
}