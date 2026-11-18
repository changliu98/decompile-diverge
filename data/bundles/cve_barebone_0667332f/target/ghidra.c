int bracketed_paste(paste_mode_T mode,int drop,garray_T *gap)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint c_00;
  size_t sVar4;
  bool bVar5;
  int save_paste;
  int save_allow_keys;
  int ret_char;
  char_u *end;
  int idx;
  char_u buf [86];
  int c;
  garray_T *gap_local;
  int drop_local;
  paste_mode_T mode_local;
  
  idx = 0;
  end = find_termcode("PE");
  iVar2 = p_paste;
  iVar1 = allow_keys;
  ret_char = -1;
  if ((end != (char_u *)0x0) && (sVar4 = strlen((char *)end), 0x40 < sVar4)) {
    end = (char_u *)0x0;
  }
  no_mapping = no_mapping + 1;
  allow_keys = 0;
  if (p_paste == 0) {
    set_option_value((char_u *)"paste",1,(char_u *)0x0,0);
  }
  do {
    while( true ) {
      if ((end == (char_u *)0x0) && (iVar3 = vpeekc(), iVar3 == 0)) goto LAB_0010153e;
      do {
        iVar3 = vgetc();
        bVar5 = true;
        if ((iVar3 != 0x1001) && (bVar5 = true, iVar3 != 0x1002)) {
          bVar5 = iVar3 == 0x1003;
        }
      } while (bVar5);
      if (((iVar3 == 0) || (got_int != 0)) || ((0 < ex_normal_busy && (iVar3 == 3))))
      goto LAB_0010153e;
      if (has_mbyte == 0) {
        buf[idx] = (char_u)iVar3;
        idx = idx + 1;
      }
      else {
        iVar3 = (*mb_char2bytes)(iVar3,buf + idx);
        idx = iVar3 + idx;
      }
      buf[idx] = '\0';
      if ((end != (char_u *)0x0) && (iVar3 = strncmp((char *)buf,(char *)end,(long)idx), iVar3 == 0)
         ) break;
      if (drop == 0) {
        switch(mode) {
        case PASTE_INSERT:
          iVar3 = stop_arrow();
          if (iVar3 == 1) {
            c_00 = (uint)buf[0];
            if ((idx == 1) && (((c_00 == 0xd || (c_00 == 0x1004)) || (c_00 == 10)))) {
              ins_eol(c_00);
            }
            else {
              ins_char_bytes(buf,idx);
              AppendToRedobuffLit(buf,idx);
            }
          }
          break;
        case PASTE_CMDLINE:
          put_on_cmdline(buf,idx,1);
          break;
        case PASTE_EX:
          if ((gap != (garray_T *)0x0) && (iVar3 = ga_grow(gap,idx), iVar3 == 1)) {
            memmove((void *)((long)gap->ga_data + (long)gap->ga_len),buf,(long)idx);
            gap->ga_len = idx + gap->ga_len;
          }
          break;
        case PASTE_ONE_CHAR:
          if (ret_char == -1) {
            if (has_mbyte == 0) {
              ret_char = (int)buf[0];
            }
            else {
              ret_char = (*mb_ptr2char)(buf);
            }
          }
        }
      }
      idx = 0;
    }
  } while (end[idx] != '\0');
LAB_0010153e:
  no_mapping = no_mapping + -1;
  allow_keys = iVar1;
  if (iVar2 == 0) {
    set_option_value((char_u *)"paste",0,(char_u *)0x0,0);
  }
  return ret_char;
}