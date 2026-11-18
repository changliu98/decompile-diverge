void getRange(double lb, double ub,double *lower, double *upper, double new_value){

 if(ub > new_value){
  *upper = new_value;
 }else{
  *upper = ub;
 }

 if(lb < new_value){
  *lower = new_value;
 }else{
  *lower = lb;
 }
}