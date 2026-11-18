int xpm_decode_frame(AVCodecContext *avctx,void *data,int *got_frame,AVPacket *avpkt)

{
  int iVar1;
  uint32_t uVar2;
  size_t sVar3;
  uint8_t *puVar4;
  char *pcVar5;
  size_t sVar6;
  int len;
  uint8_t *index;
  uint32_t *dst;
  int64_t size;
  int j;
  int i;
  int ret;
  int cpp;
  int ncolors;
  uint8_t *ptr;
  uint8_t *end;
  AVFrame *p;
  XPMDecContext *x;
  AVPacket *avpkt_local;
  int *got_frame_local;
  void *data_local;
  AVCodecContext *avctx_local;
  int local_c;
  
  x = avctx->priv_data;
  ptr = avpkt->data;
  avctx->pix_fmt = 1;
  end = avpkt->data + avpkt->size;
  p = data;
  avpkt_local = avpkt;
  got_frame_local = got_frame;
  data_local = data;
  avctx_local = avctx;
  while (iVar1 = memcmp(ptr,"/* XPM */",9), iVar1 != 0 && ptr < end + -9) {
    ptr = ptr + 1;
  }
  if (ptr < end) {
    sVar3 = mod_strcspn((char *)ptr,"\"");
    ptr = ptr + sVar3;
    iVar1 = __isoc99_sscanf(ptr,"\"%u %u %u %u\",",&avctx_local->width,&avctx_local->height,&ncolors
                            ,&cpp);
    if (iVar1 == 4) {
      local_c = ff_set_dimensions(avctx_local,avctx_local->width,avctx_local->height);
      if ((-1 < local_c) && (local_c = ff_get_buffer(avctx_local,p,0), -1 < local_c)) {
        if ((cpp < 1) || (4 < cpp)) {
          av_log(avctx_local,0x10,"unsupported/invalid number of chars per pixel: %d\n",
                 (ulong)(uint)cpp);
          local_c = -0x41444e49;
        }
        else {
          size = 1;
          for (i = 0; i < cpp; i = i + 1) {
            size = size * 0x5e;
          }
          if ((ncolors < 1) || (size < ncolors)) {
            av_log(avctx_local,0x10,"invalid number of colors: %d\n",(ulong)(uint)ncolors);
            local_c = -0x41444e49;
          }
          else {
            av_fast_padded_malloc(x,&x->pixels_size,size << 2);
            if (x->pixels == (uint32_t *)0x0) {
              local_c = -0xc;
            }
            else {
              sVar3 = mod_strcspn((char *)ptr,",");
              ptr = ptr + sVar3 + 1;
              for (i = 0; i < ncolors; i = i + 1) {
                sVar3 = mod_strcspn((char *)ptr,"\"");
                puVar4 = ptr + sVar3 + 1;
                if (end < puVar4 + cpp) {
                  return -0x41444e49;
                }
                ptr = puVar4 + cpp;
                pcVar5 = strstr((char *)ptr,"c ");
                if (pcVar5 == (char *)0x0) {
                  return -0x41444e49;
                }
                ptr = (uint8_t *)(pcVar5 + 2);
                sVar6 = strcspn((char *)ptr,"\" ");
                iVar1 = ascii2index(puVar4,cpp);
                if (iVar1 < 0) {
                  return iVar1;
                }
                uVar2 = color_string_to_rgba((char *)ptr,(int)sVar6);
                x->pixels[iVar1] = uVar2;
                sVar3 = mod_strcspn((char *)ptr,",");
                ptr = ptr + sVar3 + 1;
              }
              for (i = 0; i < avctx_local->height; i = i + 1) {
                puVar4 = p->data[0];
                iVar1 = p->linesize[0];
                sVar3 = mod_strcspn((char *)ptr,"\"");
                ptr = ptr + sVar3 + 1;
                dst = (uint32_t *)(puVar4 + i * iVar1);
                for (j = 0; j < avctx_local->width; j = j + 1) {
                  if (end < ptr + cpp) {
                    return -0x41444e49;
                  }
                  iVar1 = ascii2index(ptr,cpp);
                  if (iVar1 < 0) {
                    return iVar1;
                  }
                  *dst = x->pixels[iVar1];
                  ptr = ptr + cpp;
                  dst = dst + 1;
                }
                sVar3 = mod_strcspn((char *)ptr,",");
                ptr = ptr + sVar3 + 1;
              }
              p->key_frame = 1;
              p->pict_type = 1;
              *got_frame_local = 1;
              local_c = avpkt_local->size;
            }
          }
        }
      }
    }
    else {
      av_log(avctx_local,0x10,"missing image parameters\n");
      local_c = -0x41444e49;
    }
  }
  else {
    av_log(avctx_local,0x10,"missing signature\n");
    local_c = -0x41444e49;
  }
  return local_c;
}