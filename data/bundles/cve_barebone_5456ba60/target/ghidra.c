int kwajd_read_headers(mspack_system *sys,mspack_file *fh,mskwajd_header *hdr)

{
  uchar uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  int local_58;
  int local_54;
  char *fn;
  off_t pos;
  int i;
  uchar buf [16];
  mskwajd_header *hdr_local;
  mspack_file *fh_local;
  mspack_system *sys_local;
  int local_c;
  
  iVar2 = (*sys->read)(fh,buf,0xe);
  if (iVar2 == 0xe) {
    if ((((uint)buf[3] << 0x18 | (uint)buf[2] << 0x10 | (uint)buf[1] << 8 | (uint)buf[0]) ==
         0x4a41574b) &&
       (((uint)buf[7] << 0x18 | (uint)buf[6] << 0x10 | (uint)buf[5] << 8 | (uint)buf[4]) ==
        0xd127f088)) {
      hdr->comp_type = buf._8_2_;
      hdr->data_offset = (long)(int)(uint)(ushort)buf._10_2_;
      hdr->headers = (uint)(ushort)buf._12_2_;
      hdr->length = 0;
      hdr->filename = (char *)0x0;
      hdr->extra = (char *)0x0;
      hdr->extra_length = 0;
      if ((hdr->headers & 1U) != 0) {
        iVar2 = (*sys->read)(fh,buf,4);
        if (iVar2 != 4) {
          return 3;
        }
        hdr->length = (long)(int)((uint)buf[3] << 0x18 | (uint)buf[2] << 0x10 | (uint)buf[1] << 8 |
                                 (uint)buf[0]);
      }
      if (((hdr->headers & 2U) == 0) || (iVar2 = (*sys->read)(fh,buf,2), iVar2 == 2)) {
        if ((hdr->headers & 4U) != 0) {
          iVar2 = (*sys->read)(fh,buf,2);
          if (iVar2 != 2) {
            return 3;
          }
          iVar2 = (*sys->seek)(fh,(off_t)buf._0_2_,1);
          if (iVar2 != 0) {
            return 5;
          }
        }
        if ((hdr->headers & 0x18U) != 0) {
          pos = (*sys->tell)(fh);
          fn = (*sys->alloc)(sys,0xd);
          if (fn == (char *)0x0) {
            return 6;
          }
          hdr->filename = fn;
          if ((hdr->headers & 8U) != 0) {
            iVar2 = (*sys->read)(fh,buf,9);
            if (iVar2 != 9) {
              return 3;
            }
            for (i = 0; (i < 9 && (uVar1 = buf[i], *fn = uVar1, uVar1 != '\0')); i = i + 1) {
              fn = fn + 1;
            }
            if (i < 9) {
              local_54 = i + 1;
            }
            else {
              local_54 = 9;
            }
            pos = local_54 + pos;
            iVar2 = (*sys->seek)(fh,pos,0);
            if (iVar2 != 0) {
              return 5;
            }
          }
          if ((hdr->headers & 0x10U) != 0) {
            *fn = '.';
            iVar2 = (*sys->read)(fh,buf,4);
            if (iVar2 != 4) {
              return 3;
            }
            for (i = 0; (fn = fn + 1, i < 4 && (uVar1 = buf[i], *fn = uVar1, uVar1 != '\0'));
                i = i + 1) {
            }
            if (i < 4) {
              local_58 = i + 1;
            }
            else {
              local_58 = 4;
            }
            iVar2 = (*sys->seek)(fh,local_58 + pos,0);
            if (iVar2 != 0) {
              return 5;
            }
          }
          *fn = '\0';
        }
        if ((hdr->headers & 0x20U) != 0) {
          iVar2 = (*sys->read)(fh,buf,2);
          if (iVar2 != 2) {
            return 3;
          }
          uVar3 = (uint)(ushort)buf._0_2_;
          pcVar5 = (*sys->alloc)(sys,(long)(int)uVar3 + 1);
          hdr->extra = pcVar5;
          if (hdr->extra == (char *)0x0) {
            return 6;
          }
          uVar4 = (*sys->read)(fh,hdr->extra,uVar3);
          if (uVar4 != uVar3) {
            return 3;
          }
          hdr->extra[(int)uVar3] = '\0';
          hdr->extra_length = buf._0_2_;
        }
        local_c = 0;
      }
      else {
        local_c = 3;
      }
    }
    else {
      local_c = 7;
    }
  }
  else {
    local_c = 3;
  }
  return local_c;
}