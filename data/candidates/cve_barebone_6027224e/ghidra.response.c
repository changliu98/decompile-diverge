void shift_line(int left,int round,int amount,int call_changed_bytes)

{
  int iVar1;
  int iVar2;
  long lVar3;
  int sw_val;
  int j;
  int i;
  int count;
  int call_changed_bytes_local;
  int amount_local;
  int round_local;
  int left_local;
  
  lVar3 = get_sw_value_indent(curbuf);
  iVar1 = (int)lVar3;
  iVar2 = get_indent();
  if (round == 0) {
    if (left == 0) {
      count = iVar1 * amount + iVar2;
    }
    else {
      count = iVar2 - iVar1 * amount;
      if (count < 0) {
        count = 0;
      }
    }
  }
  else {
    amount_local = amount;
    if ((iVar2 % iVar1 != 0) && (left != 0)) {
      amount_local = amount + -1;
    }
    if (left == 0) {
      i = amount_local + iVar2 / iVar1;
    }
    else {
      i = iVar2 / iVar1 - amount_local;
      if (i < 0) {
        i = 0;
      }
    }
    count = i * iVar1;
  }
  if ((State & 0x200U) == 0) {
    set_indent(count,(uint)(call_changed_bytes != 0));
  }
  else {
    change_indent(1,count,0,0,call_changed_bytes);
  }
  return;
}