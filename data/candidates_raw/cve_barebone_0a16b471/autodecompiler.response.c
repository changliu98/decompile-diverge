static int iwgif_read_image(iwgifstruct *gif)
{
 unsigned char *buf;
 int local_ct_size, has_local_ct, codesize, subblocksize;
 int ret=0;
 lzwdeccontext lzw;

 if(!iwgif_read(gif, &(gif->image_buffer[0]), 9))
  goto done;

 gif->img_x = iw_get_ui16le(&(gif->image_buffer[0]));
 gif->img_y = iw_get_ui16le(&(gif->image_buffer[2]));
 gif->img_w = iw_get_ui16le(&(gif->image_buffer[4]));
 gif->img_h = iw_get_ui16le(&(gif->image_buffer[6]));

 gif->img_interlace = (gif->image_buffer[8] & 0x40) >> 6;
 has_local_ct = (gif->image_buffer[8] & 0x80) >> 7;

 if(has_local_ct) {
  local_ct_size = (gif->image_buffer[8] & 0x07);
  gif->ct_size = 1 << (local_ct_size + 1);
 }

 if(has_local_ct) {
  if(!iwgif_read_color_table(gif, &(gif->ct_size)))
   goto done;
 } else {
  if(gif->global_ct_size)
   gif->ct_buffer[gif->ct_size] = 0;

  if(!iwgif_read(gif, &(gif->image_buffer[0]), 1))
   goto done;

  codesize = gif->image_buffer[0];

  if((codesize < 2) || (codesize > 11)) {
   iw_set_error(gif->iwp, "Invalid LZW minimum code size");
   goto done;
  }
 }

 if(!iwgif_init_screen(gif))
  goto done;

 gif->img_rows = gif->img_w * gif->img_h;

 if(!iwgif_make_row_pointers(gif))
  goto done;

 lzw_init(&lzw, codesize);
 lzw_clear(&lzw);

 while(1) {
  if(!iwgif_read(gif, &(gif->image_buffer[0]), 1))
   goto done;

  subblocksize = gif->image_buffer[0];

  if(subblocksize == 0)
   break;

  if(!iwgif_read(gif, &(gif->image_buffer[0]), subblocksize))
   goto done;

  if(!lzw_process_bytes(&lzw, &(gif->image_buffer[0]),
                        &(gif->image_buffer[0]), subblocksize))
   goto done;

  if(lzw.eoi_flag)
   break;

  if(gif->img_y >= gif->img_rows)
   break;
 }

 ret = 1;

done:
 return ret;
}