void getRange(double lb, double ub, double *lower, double *upper, double new_value){

  if (new_value >= ub){
    *upper = ub;
  } else {
    *upper = new_value;
  }

  if (new_value <= lb){
    *lower = lb;
  } else {
    *lower = new_value;
  }
}