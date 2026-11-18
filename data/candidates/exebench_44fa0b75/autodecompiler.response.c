void
calculate_proportions(int src_w, int src_h, int *pdst_w, int *pdst_h)
{
 int dst_w, dst_h;

 if (pdst_w != NULL) {
  dst_w = *pdst_w;
 } else {
  dst_w = 0;
 }
 if (pdst_h != NULL) {
  dst_h = *pdst_h;
 } else {
  dst_h = 0;
 }

 if ((src_w > 0) && (src_w >= src_h)) {

  if ((dst_w > 0) || (dst_h > 0)) {

   dst_h = (src_h * dst_w) / src_w;
  } else {

   dst_h = src_h;
  }
 } else {

  if (src_h > 0) {

   dst_w = (src_w * dst_h) / src_h;
  } else {

   dst_w = src_w;
  }
 }

 if (pdst_w != NULL) {
  *pdst_w = dst_w;
 }
 if (pdst_h != NULL) {
  *pdst_h = dst_h;
 }
}