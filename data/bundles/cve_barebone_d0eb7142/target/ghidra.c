MOBI_RET mobi_search_links_kf7(MOBIResult *result,uchar *data_start,uchar *data_end)

{
  int iVar1;
  size_t __n;
  size_t __n_00;
  ushort **ppuVar2;
  bool bVar3;
  size_t local_68;
  int i;
  uchar last_border;
  uchar tag_close;
  uchar tag_open;
  uchar *data;
  size_t needle_length;
  size_t needle2_length;
  size_t needle1_length;
  char *needle2;
  char *needle1;
  uchar *data_end_local;
  uchar *data_start_local;
  MOBIResult *result_local;
  MOBI_RET local_c;
  
  if (result == (MOBIResult *)0x0) {
    local_c = MOBI_PARAM_ERR;
  }
  else {
    result->end = (uchar *)0x0;
    result->start = (uchar *)0x0;
    result->value[0] = '\0';
    if ((data_start == (uchar *)0x0) || (data_end == (uchar *)0x0)) {
      local_c = MOBI_PARAM_ERR;
    }
    else {
      __n = strlen("filepos=");
      __n_00 = strlen("recindex=");
      local_68 = __n_00;
      if (__n_00 < __n) {
        local_68 = __n;
      }
      if (data_end < data_start + local_68) {
        local_c = MOBI_SUCCESS;
      }
      else {
        last_border = '<';
        data = data_start;
        while (data <= data_end) {
          if ((*data == '<') || (*data == '>')) {
            last_border = *data;
          }
          if ((data_end < data + local_68) ||
             ((iVar1 = memcmp(data,"filepos=",__n), iVar1 != 0 &&
              (iVar1 = memcmp(data,"recindex=",__n_00), iVar1 != 0)))) {
            data = data + 1;
          }
          else {
            if (last_border == '<') {
              while( true ) {
                bVar3 = false;
                if (data_start <= data) {
                  ppuVar2 = __ctype_b_loc();
                  bVar3 = false;
                  if (((*ppuVar2)[(int)(uint)*data] & 0x2000) == 0) {
                    bVar3 = *data != '<';
                  }
                }
                if (!bVar3) break;
                data = data + -1;
              }
              result->start = data + 1;
              i = 0;
              data = data + 1;
              while( true ) {
                bVar3 = false;
                if (data <= data_end) {
                  ppuVar2 = __ctype_b_loc();
                  bVar3 = false;
                  if ((((*ppuVar2)[(int)(uint)*data] & 0x2000) == 0) &&
                     (bVar3 = false, *data != '>')) {
                    bVar3 = i < 0x96;
                  }
                }
                if (!bVar3) break;
                result->value[i] = *data;
                i = i + 1;
                data = data + 1;
              }
              if ((data[-1] == '/') && (*data == '>')) {
                data = data + -1;
                i = i + -1;
              }
              result->end = data;
              result->value[i] = '\0';
              return MOBI_SUCCESS;
            }
            data = data + local_68;
          }
        }
        local_c = MOBI_SUCCESS;
      }
    }
  }
  return local_c;
}