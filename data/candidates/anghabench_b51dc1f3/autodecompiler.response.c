int get_sorting_mode(int eMode){
  int ret;
  if( eMode<0 || eMode>128 ){
    ret = -1;
  }else{
    ret = tbl_sorting_mode[eMode];
  }
  return ret;
}