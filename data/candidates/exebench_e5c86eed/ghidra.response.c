int SeekPoint(uchar *TOC,int file_bytes,float percent)

{
  float fx;
  float fb;
  float fa;
  int seekpoint;
  int a;
  float percent_local;
  int file_bytes_local;
  uchar *TOC_local;
  
  percent_local = percent;
  if (percent < 0.0) {
    percent_local = 0.0;
  }
  if (DAT_00102004 < percent_local) {
    percent_local = DAT_00102004;
  }
  a = (int)percent_local;
  if (99 < a) {
    a = 99;
  }
  if (a < 99) {
    fb = (float)TOC[(long)a + 1];
  }
  else {
    fb = DAT_00102008;
  }
  return (int)(DAT_0010200c * ((fb - (float)TOC[a]) * (percent_local - (float)a) + (float)TOC[a]) *
              (float)file_bytes);
}