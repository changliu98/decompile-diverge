#include <pthread.h>

#include <errno.h>

#include <stdio.h>

#include <stdlib.h>

#include <math.h>

#include <time.h>

#include <fcntl.h>

#include <unistd.h>

#include <pthread.h>

#include <unistd.h> /* sleep() */

#include <string.h>/*}}}*/

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
