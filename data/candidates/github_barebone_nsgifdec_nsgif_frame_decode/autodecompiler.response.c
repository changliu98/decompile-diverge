int nsgif_frame_decode(struct nsgif *gif, unsigned int frame, struct nsbitmap **bitmap)
{
 unsigned int f;
 int err = 0;

 int ret;

 if (frame >= gif->frame_count) {
  ret = 3;
  goto out;
 }

 if (frame == gif->decoded_frame) {
  *bitmap = gif->bitmap;
  ret = 0;
  goto out;
 }

 unsigned int start_frame;
 if (frame <= gif->decoded_frame || gif->decoded_frame == ((unsigned int) -1)) {
  start_frame = 0;
 } else {
  start_frame = nsgif__frame_next(gif, NULL, gif->decoded_frame);
 }

 while (1) {
  for (f = start_frame; f <= frame; f++) {
   err = nsgif__process_frame(gif, f, 1);
   if (err != 0) {
    ret = err;
    goto out;
   }
  }

  *bitmap = gif->bitmap;
  ret = err;
out:
  return ret;
 }
}