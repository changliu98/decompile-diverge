void decode_mode10_short_delta(int delta,int *dr,int *dg,int *db)

{
  int *db_local;
  int *dg_local;
  int *dr_local;
  int delta_local;
  
  *db = delta & 0x1f;
  if ((*db & 0x10U) != 0) {
    *db = *db | 0xfffffff0;
  }
  *db = *db << 1;
  *dg = (int)(delta & 0x3e0U) >> 5;
  if ((*dg & 0x10U) != 0) {
    *dg = *dg | 0xfffffff0;
  }
  *dr = (int)(delta & 0x7c00U) >> 10;
  if ((*dr & 0x10U) != 0) {
    *dr = *dr | 0xfffffff0;
  }
  return;
}