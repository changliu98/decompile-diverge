void sortVrtx(int *vrt)
{
  int i,j,k,done;
  int tmp;

  done = 0;
  while (!done) {
    done = 1;
    for (i=1; i<3; i++) {
      if (vrt[i] < vrt[i-1]) {
        tmp = vrt[i];
        vrt[i] = vrt[i-1];
        vrt[i-1] = tmp;
        done = 0;
      }
    }
  }
}