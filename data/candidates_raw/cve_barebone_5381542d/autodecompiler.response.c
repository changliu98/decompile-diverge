int
win_num_columns(Win *w)
{
 int ncol, wcol, wcol2;

 if (!w->cols.num) {
  ncol = 0;
 } else {
  wcol = w->wcols - win_col_off(w);
  if (w->cols.num >= wcol) {
   wcol2 = w->cols.num - wcol;
   ncol = wcol2 / (wcol + win_col_off2(w)) + 1;
  } else {
   ncol = 0;
  }
 }

 return ncol;
}