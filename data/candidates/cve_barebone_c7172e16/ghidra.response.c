pj_status_t
get_name_len(int rec_counter,pj_uint8_t *pkt,pj_uint8_t *start,pj_uint8_t *max,int *parsed_len,
            int *name_len)

{
  pj_uint16_t pVar1;
  pj_status_t pVar2;
  uint label_len;
  pj_uint16_t offset;
  int dummy;
  int ptr_len;
  pj_status_t status;
  pj_uint8_t *p;
  int *name_len_local;
  int *parsed_len_local;
  pj_uint8_t *max_local;
  pj_uint8_t *start_local;
  pj_uint8_t *pkt_local;
  int rec_counter_local;
  pj_status_t local_c;
  
  if (rec_counter < 0xb) {
    if (start < max) {
      *parsed_len = 0;
      *name_len = 0;
      p = start;
      while (*p != '\0') {
        if ((*p & 0xc0) == 0xc0) {
          ptr_len = 0;
          name_len_local = name_len;
          parsed_len_local = parsed_len;
          max_local = max;
          start_local = start;
          pkt_local = pkt;
          rec_counter_local = rec_counter;
          pj_memcpy(&offset,p,2);
          pVar1 = pj_htons(0xc000);
          offset = offset ^ pVar1;
          offset = pj_ntohs(offset);
          if ((long)max_local - (long)pkt_local <= (long)(ulong)offset) {
            return 0x4e22b;
          }
          pVar2 = get_name_len(rec_counter_local + 1,pkt_local,pkt_local + (int)(uint)offset,
                               max_local,&dummy,&ptr_len);
          if (pVar2 != 0) {
            return pVar2;
          }
          *parsed_len_local = *parsed_len_local + 2;
          *name_len_local = ptr_len + *name_len_local;
          return 0;
        }
        label_len = (uint)*p;
        if (max < p + (ulong)label_len + 2) {
          return 0x4e22b;
        }
        p = p + (label_len + 1);
        *parsed_len = label_len + 1 + *parsed_len;
        if (*p != '\0') {
          label_len = label_len + 1;
        }
        *name_len = label_len + *name_len;
      }
      *parsed_len = *parsed_len + 1;
      local_c = 0;
    }
    else {
      local_c = 0x4e22b;
    }
  }
  else {
    local_c = 0x4e22b;
  }
  return local_c;
}