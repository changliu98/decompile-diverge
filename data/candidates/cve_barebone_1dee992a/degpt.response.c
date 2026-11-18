int eval_tuple(char_u **arg,typval_T *rettv,evalarg_T *evalarg,int do_error)

{
  char_u cVar1;
  int iVar2;
  int iVar3;
  char_u *pcVar4;
  bool bVar5;
  uint local_54;
  int had_comma;
  int vim9script;
  typval_T tv;
  tuple_T *tuple;
  int evaluate;
  int do_error_local;
  evalarg_T *evalarg_local;
  typval_T *rettv_local;
  char_u **arg_local;
  int local_c;
  
  if (evalarg == (evalarg_T *)0x0) {
    local_54 = 0;
  }
  else {
    local_54 = evalarg->eval_flags & 1;
  }
  tuple = (tuple_T *)0x0;
  iVar2 = in_vim9script();
  iVar3 = check_typval_is_value(rettv);
  if (iVar3 == 0) {
    clear_tv(rettv);
    return 0;
  }
  if (local_54 != 0) {
    tuple = tuple_alloc();
    if (tuple == (tuple_T *)0x0) {
      return 0;
    }
    if ((rettv->v_type != VAR_UNKNOWN) && (iVar3 = tuple_append_tv(tuple,rettv), iVar3 == 0)) {
      return 0;
    }
  }
  if (**arg == ')') {
LAB_00101988:
    *arg = *arg + 1;
    if (local_54 != 0) {
      rettv_tuple_set(rettv,tuple);
    }
    local_c = 1;
  }
  else {
    if ((((iVar2 == 0) || ((*arg)[1] == ' ')) || ((*arg)[1] == '\t')) ||
       ((((*arg)[1] == '\n' || ((*arg)[1] == '\0')) || ((*arg)[1] == ')')))) {
      pcVar4 = skipwhite_and_linebreak(*arg + 1,evalarg);
      *arg = pcVar4;
      do {
        bVar5 = false;
        if (**arg != ')') {
          bVar5 = **arg != '\0';
        }
        if (!bVar5) {
LAB_0010192d:
          if (**arg == ')') goto LAB_00101988;
          if (do_error != 0) {
            semsg("E1526: Missing end of Tuple \')\': %s",*arg);
          }
          goto LAB_00101964;
        }
        iVar3 = eval1(arg,&tv,evalarg);
        if (iVar3 == 0) goto LAB_00101964;
        iVar3 = check_typval_is_value(&tv);
        if (iVar3 == 0) {
          if (local_54 != 0) {
            clear_tv(&tv);
          }
          goto LAB_00101964;
        }
        if ((local_54 != 0) && (iVar3 = tuple_append_tv(tuple,&tv), iVar3 == 0)) {
          clear_tv(&tv);
          goto LAB_00101964;
        }
        if (iVar2 == 0) {
          pcVar4 = skipwhite(*arg);
          *arg = pcVar4;
        }
        cVar1 = **arg;
        if (cVar1 == ',') {
          if (((((iVar2 != 0) && ((*arg)[1] != ' ')) && ((*arg)[1] != '\t')) &&
              (((*arg)[1] != '\n' && ((*arg)[1] != '\0')))) && ((*arg)[1] != ')')) {
            semsg("E1069: White space required after \'%s\': %s",&DAT_00103114,*arg);
            goto LAB_00101964;
          }
          pcVar4 = skipwhite(*arg + 1);
          *arg = pcVar4;
        }
        pcVar4 = skipwhite_and_linebreak(*arg,evalarg);
        *arg = pcVar4;
        if (**arg == ')') goto LAB_0010192d;
      } while (cVar1 == ',');
      if (do_error != 0) {
        if (**arg == ',') {
          semsg("E1068: No white space allowed before \'%s\': %s",&DAT_00103114,*arg);
        }
        else {
          semsg("E1527: Missing comma in Tuple: %s",*arg);
        }
      }
    }
    else {
      semsg("E1069: White space required after \'%s\': %s",&DAT_00103114,*arg);
    }
LAB_00101964:
    if (local_54 != 0) {
      tuple_free(tuple);
    }
    local_c = 0;
  }
  return local_c;
}