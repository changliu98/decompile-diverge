void getRange(double lb, double ub, double *l, double *u, double x) {
 if(x < ub) {
  *u = x;
 } else {
  *u = ub;
 }
 if(x > lb) {
  *l = x;
 } else {
  *l = lb;
 }
}