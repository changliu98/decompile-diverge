int do_core_note(magic_set *ms,uchar *nbuf,uint32_t type,int swap,uint32_t namesz,uint32_t descsz,
                size_t noff,size_t doff,int *flags,size_t size,int clazz)

{
  byte bVar1;
  ulong uVar2;
  bool bVar3;
  int iVar4;
  uint32_t uVar5;
  uint32_t uVar6;
  uint32_t uVar7;
  uint32_t uVar8;
  uint32_t uVar9;
  uint32_t uVar10;
  uint32_t uVar11;
  char *pcVar12;
  ushort **ppuVar13;
  uchar *puVar14;
  bool bVar15;
  size_t local_3c0;
  size_t local_3a0;
  size_t local_388;
  ulong local_378;
  size_t local_360;
  int adjust;
  size_t no;
  size_t k;
  size_t noffset;
  size_t reloffset;
  uchar *cp;
  uchar *cname;
  uchar c;
  size_t j;
  size_t i;
  NetBSD_elfcore_procinfo pi;
  char sbuf [512];
  int os_style;
  uint32_t descsz_local;
  uint32_t namesz_local;
  int swap_local;
  uint32_t type_local;
  uchar *nbuf_local;
  magic_set *ms_local;
  
  os_style = -1;
  if (((namesz == 4) && (iVar4 = strncmp((char *)(nbuf + noff),"CORE",4), iVar4 == 0)) ||
     ((namesz == 5 && (iVar4 = strcmp((char *)(nbuf + noff),"CORE"), iVar4 == 0)))) {
    os_style = 0;
  }
  if ((namesz == 8) && (iVar4 = strcmp((char *)(nbuf + noff),"FreeBSD"), iVar4 == 0)) {
    os_style = 1;
  }
  if ((10 < namesz) && (iVar4 = strncmp((char *)(nbuf + noff),"NetBSD-CORE",0xb), iVar4 == 0)) {
    os_style = 2;
  }
  if ((os_style != -1) && ((*flags & 0x20U) == 0)) {
    iVar4 = file_printf(ms,", %s-style",os_style_names + os_style);
    if (iVar4 == -1) {
      return 1;
    }
    *flags = *flags | 0x20;
    *flags = os_style | *flags;
  }
  if (os_style == 2) {
    if (type == 1) {
      memset(&pi,0,0xa0);
      memcpy(&pi,nbuf + doff,(ulong)descsz);
      pcVar12 = file_printable(sbuf,0x200,pi.cpi_name);
      uVar5 = getu32(swap,pi.cpi_pid);
      uVar6 = getu32(swap,pi.cpi_euid);
      uVar7 = getu32(swap,pi.cpi_egid);
      uVar8 = getu32(swap,pi.cpi_nlwps);
      uVar9 = getu32(swap,pi.cpi_siglwp);
      uVar10 = getu32(swap,pi.cpi_signo);
      uVar11 = getu32(swap,pi.cpi_sigcode);
      iVar4 = file_printf(ms,
                          ", from \'%.31s\', pid=%u, uid=%u, gid=%u, nlwps=%u, lwp=%u (signal %u/code %u)"
                          ,pcVar12,(ulong)uVar5,(ulong)uVar6,(ulong)uVar7,uVar8,uVar9,uVar10,uVar11)
      ;
      if (iVar4 != -1) {
        *flags = *flags | 4;
        return 1;
      }
      return 1;
    }
  }
  else if ((type == 3) && ((*flags & 0x800U) != 0)) {
    i = 0;
LAB_00101722:
    if (i < 5) {
      if (clazz == 1) {
        local_360 = prpsoffsets32[i];
      }
      else {
        local_360 = prpsoffsets64[i];
      }
      reloffset = local_360;
      noffset = doff + local_360;
      j = 0;
      do {
        k = i;
        if (0xf < j) {
LAB_001018c2:
          while (k = k + 1, k < 5) {
            bVar15 = true;
            if (clazz == 1) {
              uVar2 = prpsoffsets32[k];
              local_378 = prpsoffsets32[i];
            }
            else {
              uVar2 = prpsoffsets64[k];
              local_378 = prpsoffsets64[i];
            }
            if (uVar2 < local_378) {
              if (clazz == 1) {
                local_388 = prpsoffsets32[k];
              }
              else {
                local_388 = prpsoffsets64[k];
              }
              no = doff + local_388;
              while( true ) {
                if (clazz == 1) {
                  local_3a0 = prpsoffsets32[i];
                }
                else {
                  local_3a0 = prpsoffsets64[i];
                }
                if (doff + local_3a0 <= no) break;
                bVar3 = false;
                if (bVar15) {
                  ppuVar13 = __ctype_b_loc();
                  bVar3 = ((*ppuVar13)[(int)(uint)nbuf[no]] & 0x4000) != 0;
                }
                bVar15 = bVar3;
                no = no + 1;
              }
              if (bVar15) {
                i = k;
              }
            }
          }
          if (clazz == 1) {
            local_3c0 = prpsoffsets32[i];
          }
          else {
            local_3c0 = prpsoffsets64[i];
          }
          puVar14 = nbuf + doff + local_3c0;
          cp = puVar14;
          while( true ) {
            bVar15 = false;
            if (*cp != '\0') {
              ppuVar13 = __ctype_b_loc();
              bVar15 = ((*ppuVar13)[(int)(uint)*cp] & 0x4000) != 0;
            }
            if (!bVar15) break;
            cp = cp + 1;
          }
          while( true ) {
            bVar15 = false;
            if (puVar14 < cp) {
              ppuVar13 = __ctype_b_loc();
              bVar15 = ((*ppuVar13)[(int)(uint)cp[-1]] & 0x2000) != 0;
            }
            if (!bVar15) break;
            cp = cp + -1;
          }
          iVar4 = file_printf(ms,", from \'%.*s\'",(ulong)(uint)((int)cp - (int)puVar14),puVar14);
          if (iVar4 != -1) {
            *flags = *flags | 4;
          }
          return 1;
        }
        if ((size <= noffset) || (descsz <= reloffset)) goto LAB_00101ce7;
        bVar1 = nbuf[noffset];
        if (bVar1 == 0) goto code_r0x0010180d;
        ppuVar13 = __ctype_b_loc();
        if ((((*ppuVar13)[(int)(uint)bVar1] & 0x4000) == 0) ||
           (pcVar12 = strchr("\'\"`",(uint)bVar1), pcVar12 != (char *)0x0)) goto LAB_00101ce7;
        j = j + 1;
        noffset = noffset + 1;
        reloffset = reloffset + 1;
      } while( true );
    }
  }
  return 0;
code_r0x0010180d:
  if (j != 0) goto LAB_001018c2;
LAB_00101ce7:
  i = i + 1;
  goto LAB_00101722;
}