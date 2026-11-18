void print_attr_string(netdissect_options *ndo,u_char *data,u_int length,u_short attr_code)

{
  _func_int_netdissect_options_ptr_char_ptr_varargs *p_Var1;
  uint uVar2;
  char *pcVar3;
  uint local_54;
  u_int i;
  u_short attr_code_local;
  u_int length_local;
  u_char *data_local;
  netdissect_options *ndo_local;
  
  if ((ndo->ndo_snapend < ndo->ndo_snapend + -(ulong)length) ||
     (ndo->ndo_snapend + -(ulong)length < data)) {
    (*ndo->ndo_printf)(ndo,"%s"," [|radius]");
    return;
  }
  uVar2 = (uint)attr_code;
  if (uVar2 == 0x3a) {
    p_Var1 = ndo->ndo_printf;
    pcVar3 = tok2str(rfc4675_tagged,"Unknown tag",(uint)*data);
    (*p_Var1)(ndo,"%s (0x%02x) ",pcVar3,(ulong)*data);
    data_local = data + 1;
    length_local = length - 1;
    goto LAB_001017ab;
  }
  length_local = length;
  data_local = data;
  if (1 < uVar2 - 0x42) {
    if (uVar2 == 0x45) {
      if (length < 3) {
        (*ndo->ndo_printf)(ndo,"%s"," [|radius]");
        return;
      }
      if ((*data == '\0') || (0x1f < *data)) {
        (*ndo->ndo_printf)(ndo,"Tag[Unused] ");
      }
      else {
        (*ndo->ndo_printf)(ndo,"Tag[%u] ",(ulong)*data);
      }
      (*ndo->ndo_printf)(ndo,"Salt %u ",(ulong)CONCAT11(data[1],data[2]));
      data_local = data + 3;
      length_local = length - 3;
      goto LAB_001017ab;
    }
    if ((1 < uVar2 - 0x51) && (1 < uVar2 - 0x5a)) goto LAB_001017ab;
  }
  if (*data < 0x20) {
    if (length == 0) {
      (*ndo->ndo_printf)(ndo,"%s"," [|radius]");
      return;
    }
    if (*data == '\0') {
      (*ndo->ndo_printf)(ndo,"Tag[Unused] ");
    }
    else {
      (*ndo->ndo_printf)(ndo,"Tag[%u] ",(ulong)*data);
    }
    data_local = data + 1;
    length_local = length - 1;
  }
LAB_001017ab:
  i = 0;
  for (; *data_local != '\0' && i < length_local; data_local = data_local + 1) {
    if ((*data_local < 0x20) || (0x7e < *data_local)) {
      local_54 = 0x2e;
    }
    else {
      local_54 = (uint)*data_local;
    }
    (*ndo->ndo_printf)(ndo,"%c",(ulong)local_54);
    i = i + 1;
  }
  return;
}