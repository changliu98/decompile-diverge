int toml_value_timestamp(toml_unparsed_t src_,toml_timestamp_t *ret)

{
  _Bool _Var1;
  char cVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  char *qq;
  _Bool must_parse_time;
  char *p;
  toml_timestamp_t *ret_local;
  toml_unparsed_t src__local;
  int local_c;
  
  if (src_ == (toml_unparsed_t)0x0) {
    local_c = -1;
  }
  else {
    must_parse_time = false;
    p = src_;
    ret_local = ret;
    src__local = src_;
    memset(ret,0,0x24);
    _Var1 = scan_date(p,&ret_local->year,&ret_local->month,&ret_local->day);
    pcVar4 = p;
    if (_Var1) {
      if ((((ret_local->month < 1) || (ret_local->day < 1)) || (0xc < ret_local->month)) ||
         (0x1f < ret_local->day)) {
        return -1;
      }
      if (ret_local->month == 2) {
        iVar3 = ret_local->day;
        _Var1 = is_leap(ret_local->year);
        iVar5 = 0x1c;
        if (_Var1) {
          iVar5 = 0x1d;
        }
        if (iVar5 < iVar3) {
          return -1;
        }
      }
      ret_local->kind = 'D';
      pcVar4 = p + 10;
      if (*pcVar4 != '\0') {
        if (((*pcVar4 != 'T') && (*pcVar4 != 't')) && (*pcVar4 != ' ')) {
          return -1;
        }
        must_parse_time = true;
        pcVar4 = p + 0xb;
      }
    }
    p = pcVar4;
    _Var1 = scan_time(p,&ret_local->hour,&ret_local->minute,&ret_local->second);
    if (_Var1) {
      if (((ret_local->minute < 0) || (ret_local->hour < 0)) ||
         ((0x17 < ret_local->hour || ((0x3b < ret_local->minute || (0x3c < ret_local->second)))))) {
        return -1;
      }
      iVar3 = 8;
      if (ret_local->second == -1) {
        iVar3 = 5;
      }
      p = p + iVar3;
      cVar2 = 't';
      if (ret_local->kind == 'D') {
        cVar2 = 'l';
      }
      ret_local->kind = cVar2;
      if (ret_local->second == -1) {
        ret_local->second = 0;
      }
      if (*p == '.') {
        p = p + 1;
        iVar3 = parse_millisec(p,&qq);
        ret_local->millisec = iVar3;
        p = qq;
      }
      if (*p != '\0') {
        ret_local->kind = 'd';
        if ((*p == 'Z') || (*p == 'z')) {
          p = p + 1;
        }
        else if ((*p == '+') || (*p == '-')) {
          _Var1 = scan_offset(p,&ret_local->tz);
          if (!_Var1) {
            return -1;
          }
          p = p + 6;
        }
      }
    }
    if (*p == '\0') {
      if (((must_parse_time & 1U) == 0) || (ret_local->kind != 'D')) {
        local_c = 0;
      }
      else {
        local_c = -1;
      }
    }
    else {
      local_c = -1;
    }
  }
  return local_c;
}