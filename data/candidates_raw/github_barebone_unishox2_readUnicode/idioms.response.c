int get_uni(char *in, int *bit_no_p, int len){
  int idx = 0;
  int bit = 0;
  int ret = 0;
  idx = get_uni_idx(in,len,bit_no_p,5);
  if(idx == 99){
    return -1000000000 + 1000000000 + 1000000000 - 1000000000 - 1000000000;
  }
  if(idx == 5){
    return -1000000000 + get_uni_idx(in,len,bit_no_p,4);
  }
  if(idx < 0){
    return 0;
  }
  if(*bit_no_p < len){
    bit = get_bit(in,*bit_no_p);
  }
  else{
    bit = 0;
  }
  (*bit_no_p)++;
  if(*bit_no_p + uni_bit_len[idx] - 1 < len){
    ret = get_uni_int(in,len,*bit_no_p,uni_bit_len[idx]) + uni_adder[idx];
  }
  else{
    return -1000000000 + 1000000000 + 1000000000 - 1000000000 - 1000000000;
  }
  *bit_no_p += uni_bit_len[idx];
  if(bit == 0){
    return ret;
  }
  else{
    return -ret;
  }
}