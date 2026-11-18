void OPLL_calcCh2(OPLL * opll) {
 int i;
 signed short out[2];

 out[0] = out[1] = 0;

 for (i = 0; i < 15; i++) {
  if (opll[16 + i].key_status & 2) {
   out[0] += (signed short)(opll[i].op_out[0] * opll[16 + i].fnum);
  }
  if (opll[16 + i].key_status & 1) {
   out[1] += (signed short)(opll[i].op_out[0] * opll[16 + i].fnum);
  }
 }

 if (opll[14].conv) {
  OPLL_RateConv_putData(opll[14].conv, 0, out[0]);
  OPLL_RateConv_putData(opll[14].conv, 1, out[1]);
 }
}