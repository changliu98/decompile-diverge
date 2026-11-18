int plot_digit_wierd(char digit,float row,float col,float hgt,float h,float *vx,float *vy)

{
  int iVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  int num;
  int llel;
  int llin;
  int ie;
  int ib;
  int i;
  float he;
  float hl;
  float cs;
  float rs;
  float *vy_local;
  float *vx_local;
  float h_local;
  float hgt_local;
  float col_local;
  float row_local;
  char digit_local;
  int local_c;
  
  num = 0;
  if ((digit < '0') || ('9' < digit)) {
    local_c = 0;
  }
  else {
    iVar2 = plot_digit_wierd::lt[digit + -0x2e];
    iVar1 = plot_digit_wierd::lt[digit + -0x2f];
    for (i = iVar1; i <= iVar2 + -1; i = i + 1) {
      fVar3 = hgt * (float)(plot_digit_wierd::lb[i] / 10);
      fVar4 = h * (float)(plot_digit_wierd::lb[i] + (plot_digit_wierd::lb[i] / 10) * -10);
      if (i != iVar1) {
        vx[num] = rs;
        vy[num] = cs;
        vx[num + 1] = row - fVar3;
        vy[num + 1] = col - fVar4;
        num = num + 2;
      }
      rs = row - fVar3;
      cs = col - fVar4;
    }
    local_c = num;
  }
  return local_c;
}