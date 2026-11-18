int ff_norm_qscale(int qscale, int type) {
  int q;
  switch (type) {
    case FF_QSCALE_TYPE_MPEG1:
      q = qscale;
      break;
    case FF_QSCALE_TYPE_MPEG2:
      q = qscale >> 1;
      break;
    case FF_QSCALE_TYPE_H264:
      q = qscale >> 2;
      break;
    case FF_QSCALE_TYPE_VP56:
      q = (63 - qscale + 2) >> 2;
      break;
    default:
      q = qscale;
      break;
  }
  return q;
}