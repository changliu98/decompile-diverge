int dxa_read_header(AVFormatContext *s)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int64_t iVar4;
  bool bVar5;
  uint32_t fsize;
  uint32_t size;
  int ret;
  int flags;
  int den;
  int num;
  int h;
  int w;
  int32_t fps;
  uint32_t tag;
  AVStream *ast;
  AVStream *st;
  DXAContext *c;
  AVIOContext *pb;
  AVFormatContext *s_local;
  int local_c;
  
  pb = s->pb;
  c = s->priv_data;
  s_local = s;
  tag = avio_rl32(pb);
  if (tag == 0x41584544) {
    uVar1 = avio_r8(pb);
    uVar2 = avio_rb16(pb);
    c->frames = uVar2;
    if (c->frames == 0) {
      av_log(s_local,0x10,"File contains no frames ???\n");
      local_c = -0x41444e49;
    }
    else {
      fps = avio_rb32(pb);
      if (fps < 1) {
        if ((fps < 0) && (-0x80000000 < fps)) {
          den = 100000;
          num = -fps;
        }
        else {
          den = 10;
          num = 1;
        }
      }
      else {
        den = 1000;
        num = fps;
      }
      w = avio_rb16(pb);
      h = avio_rb16(pb);
      c->has_sound = 0;
      st = avformat_new_stream(s_local,(AVCodec *)0x0);
      if (st == (AVStream *)0x0) {
        local_c = -0xc;
      }
      else {
        uVar2 = avio_rl32(pb);
        if (uVar2 == 0x45564157) {
          c->has_sound = 1;
          uVar2 = avio_rb32(pb);
          iVar4 = avio_tell(pb);
          c->vidpos = iVar4 + (ulong)uVar2;
          avio_skip(pb,0x10);
          fsize = avio_rl32(pb);
          ast = avformat_new_stream(s_local,(AVCodec *)0x0);
          if (ast == (AVStream *)0x0) {
            return -0xc;
          }
          iVar3 = ff_get_wav_header(s_local,pb,ast->codecpar,fsize,0);
          if (iVar3 < 0) {
            return iVar3;
          }
          if (0 < ast->codecpar->sample_rate) {
            avpriv_set_pts_info(ast,0x40,1,ast->codecpar->sample_rate);
          }
          while( true ) {
            iVar4 = avio_tell(pb);
            bVar5 = false;
            if (iVar4 < c->vidpos) {
              iVar3 = avio_feof(pb);
              bVar5 = iVar3 == 0;
            }
            if (!bVar5) break;
            tag = avio_rl32(pb);
            fsize = avio_rl32(pb);
            if (tag == 0x61746164) break;
            avio_skip(pb,(ulong)fsize);
          }
          c->bpc = (int)((long)((ulong)fsize + (long)c->frames + -1) / (long)c->frames);
          if (ast->codecpar->block_align != 0) {
            if (-0x80000000 - ast->codecpar->block_align < c->bpc) {
              return -0x41444e49;
            }
            c->bpc = ((c->bpc + ast->codecpar->block_align + -1) / ast->codecpar->block_align) *
                     ast->codecpar->block_align;
          }
          c->bytes_left = fsize;
          iVar4 = avio_tell(pb);
          c->wavpos = iVar4;
          avio_seek(pb,c->vidpos,0);
        }
        st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
        st->codecpar->codec_id = AV_CODEC_ID_DXA;
        st->codecpar->width = w;
        st->codecpar->height = h;
        av_reduce(&den,&num,(long)den,(long)num,0x7fffffff);
        avpriv_set_pts_info(st,0x21,num,den);
        if ((uVar1 & 0xc0) != 0) {
          st->codecpar->height = st->codecpar->height >> 1;
        }
        c->readvid = (uint)((c->has_sound != 0 ^ 0xffU) & 1);
        iVar4 = avio_tell(pb);
        c->vidpos = iVar4;
        s_local->start_time = 0;
        iVar4 = av_rescale((long)c->frames,(long)num * 1000000,(long)den);
        s_local->duration = iVar4;
        av_log(s_local,0x30,"%d frame(s)\n",(ulong)(uint)c->frames);
        local_c = 0;
      }
    }
  }
  else {
    local_c = -0x41444e49;
  }
  return local_c;
}