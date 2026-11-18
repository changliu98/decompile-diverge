int imagetopnm(struct opj_image_t *image, char *outfile, int force_split)
{
  char *out = outfile;
  char *out2;
  int i;
  int w; int h;
  int compno;
  int ncomp;
  int *red; int *green; int *blue; int *alpha;
  int adjustA; int adjustB; int adjustG;
  int v; int a; int b; int g;
  int v1; int a1; int b1; int g1;
  int prec;
  int pmax;
  int pmax1;
  int pmax2;
  int pmax3;
  int pmax4;
  int pmax12;
  int pmax123;
  int pmax1234;
  int pmax12345;
  int pmax123456;
  int pmax1234567;
  int pmax12345678;
  int pmax12345