void ex_history(exarg_T *eap)

{
  byte *name;
  char_u *s;
  int iVar1;
  char_u *pcVar2;
  size_t sVar3;
  char *__dest;
  size_t sVar4;
  undefined8 uVar5;
  bool bVar6;
  int local_6c;
  int local_60;
  char_u *arg;
  char_u *end;
  int k;
  int j;
  int i;
  int idx;
  int hisidx2;
  int hisidx1;
  int histype2;
  int histype1;
  histentry_T *hist;
  exarg_T *eap_local;
  
  histype1 = 0;
  histype2 = 0;
  hisidx1 = 1;
  hisidx2 = -1;
  name = eap->arg;
  eap_local = eap;
  if (hislen == 0) {
    msg("\'history\' option is zero");
  }
  else {
    end = name;
    if (((9 < *name - 0x30) && (*name != 0x2d)) && (*name != 0x2c)) {
      while( true ) {
        if (((*end < 0x41) || (bVar6 = true, 0x5a < *end)) &&
           ((*end < 0x61 || (bVar6 = true, 0x7a < *end)))) {
          pcVar2 = vim_strchr((char_u *)":=@>/?",(uint)*end);
          bVar6 = pcVar2 != (char_u *)0x0;
        }
        if (!bVar6) break;
        end = end + 1;
      }
      i = (int)*end;
      *end = '\0';
      histype1 = get_histtype(name);
      iVar1 = histype1;
      if (histype1 == -1) {
        sVar3 = strlen((char *)name);
        iVar1 = strncasecmp((char *)name,"all",sVar3);
        if (iVar1 != 0) {
          *end = (char_u)i;
          semsg(e_trailing_characters_str,name);
          return;
        }
        histype1 = 0;
        histype2 = 4;
        iVar1 = histype2;
      }
      histype2 = iVar1;
      *end = (char_u)i;
    }
    iVar1 = get_list_range(&end,&hisidx1,&hisidx2);
    if ((iVar1 == 0) || (*end != '\0')) {
      semsg(e_trailing_characters_str,end);
    }
    else {
      for (; got_int == 0 && histype1 <= histype2; histype1 = histype1 + 1) {
        strcpy((char *)IObuff,"\n      #  ");
        __dest = strcat((char *)IObuff,history_names[histype1]);
        strcat(__dest," history");
        msg_puts_title((char *)IObuff);
        idx = hisidx[histype1];
        hist = history[histype1];
        j = hisidx1;
        k = hisidx2;
        if (hisidx1 < 0) {
          if (hislen < -hisidx1) {
            local_60 = 0;
          }
          else {
            local_60 = hist[(hislen + hisidx1 + idx + 1) % hislen].hisnum;
          }
          j = local_60;
        }
        if (hisidx2 < 0) {
          if (hislen < -hisidx2) {
            local_6c = 0;
          }
          else {
            local_6c = hist[(hislen + hisidx2 + idx + 1) % hislen].hisnum;
          }
          k = local_6c;
        }
        if ((-1 < idx) && (iVar1 = idx, j <= k)) {
          do {
            i = iVar1 + 1;
            if (got_int != 0) break;
            if (i == hislen) {
              i = 0;
            }
            if (((hist[i].hisstr != (char_u *)0x0) && (j <= hist[i].hisnum)) &&
               (hist[i].hisnum <= k)) {
              msg_putchar(10);
              uVar5 = 0x20;
              if (i == idx) {
                uVar5 = 0x3e;
              }
              sprintf((char *)IObuff,"%c%6d  ",uVar5,(ulong)(uint)hist[i].hisnum);
              iVar1 = vim_strsize(hist[i].hisstr);
              pcVar2 = IObuff;
              if ((int)Columns + -10 < iVar1) {
                s = hist[i].hisstr;
                sVar3 = strlen((char *)IObuff);
                iVar1 = (int)Columns;
                sVar4 = strlen((char *)IObuff);
                trunc_string(s,pcVar2 + sVar3,iVar1 + -10,0x401 - (int)sVar4);
              }
              else {
                strcat((char *)IObuff,(char *)hist[i].hisstr);
              }
              msg_outtrans(IObuff);
              out_flush();
            }
            iVar1 = i;
          } while (i != idx);
        }
      }
    }
  }
  return;
}