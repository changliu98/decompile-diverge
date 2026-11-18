GF_Err abst_box_read(GF_Box *s,GF_BitStream *bs)

{
  GF_List *pGVar1;
  u32 uVar2;
  Bool BVar3;
  u64 uVar4;
  char *pcVar5;
  GF_AdobeFragmentRunTableBox *afrt;
  GF_AdobeSegmentRunTableBox *asrt;
  int j_1;
  int j;
  GF_Err e;
  char *tmp_str;
  u32 tmp_strsize;
  int i;
  GF_AdobeBootstrapInfoBox *ptr;
  GF_BitStream *bs_local;
  GF_Box *s_local;
  GF_Err local_c;
  
  if (s->size < 0x19) {
    local_c = GF_ISOM_INVALID_FILE;
  }
  else {
    s->size = s->size - 0x19;
    ptr = (GF_AdobeBootstrapInfoBox *)s;
    bs_local = bs;
    s_local = s;
    uVar2 = gf_bs_read_u32(bs);
    ptr->bootstrapinfo_version = uVar2;
    uVar2 = gf_bs_read_int(bs_local,2);
    ptr->profile = (u8)uVar2;
    BVar3 = gf_bs_read_int(bs_local,1);
    ptr->live = BVar3;
    BVar3 = gf_bs_read_int(bs_local,1);
    ptr->update = BVar3;
    uVar2 = gf_bs_read_int(bs_local,4);
    ptr->reserved = (u8)uVar2;
    uVar2 = gf_bs_read_u32(bs_local);
    ptr->time_scale = uVar2;
    uVar4 = gf_bs_read_u64(bs_local);
    ptr->current_media_time = uVar4;
    uVar4 = gf_bs_read_u64(bs_local);
    ptr->smpte_time_code_offset = uVar4;
    i = 0;
    if (ptr->size < 8) {
      local_c = GF_ISOM_INVALID_FILE;
    }
    else {
      tmp_strsize = (int)ptr->size - 8;
      tmp_str = gf_malloc((ulong)tmp_strsize);
      if (tmp_str == (char *)0x0) {
        local_c = GF_OUT_OF_MEM;
      }
      else {
        memset(tmp_str,0,(ulong)tmp_strsize);
        while (tmp_strsize != 0) {
          if (ptr->size == 0) {
            return GF_ISOM_INVALID_FILE;
          }
          ptr->size = ptr->size - 1;
          uVar2 = gf_bs_read_u8(bs_local);
          tmp_str[i] = (char)uVar2;
          tmp_strsize = tmp_strsize - 1;
          if (tmp_str[i] == '\0') break;
          i = i + 1;
        }
        if (i != 0) {
          pcVar5 = gf_strdup(tmp_str);
          ptr->movie_identifier = pcVar5;
        }
        if (ptr->size == 0) {
          local_c = GF_ISOM_INVALID_FILE;
        }
        else {
          ptr->size = ptr->size - 1;
          uVar2 = gf_bs_read_u8(bs_local);
          ptr->server_entry_count = (u8)uVar2;
          for (i = 0; i < (int)(uint)ptr->server_entry_count; i = i + 1) {
            j = 0;
            tmp_strsize = (u32)ptr->size;
            while (tmp_strsize != 0) {
              if (ptr->size == 0) {
                return GF_ISOM_INVALID_FILE;
              }
              ptr->size = ptr->size - 1;
              uVar2 = gf_bs_read_u8(bs_local);
              tmp_str[j] = (char)uVar2;
              tmp_strsize = tmp_strsize - 1;
              if (tmp_str[j] == '\0') break;
              j = j + 1;
            }
            if (j != 0) {
              pGVar1 = ptr->server_entry_table;
              pcVar5 = gf_strdup(tmp_str);
              gf_list_insert(pGVar1,pcVar5,i);
            }
          }
          if (ptr->size == 0) {
            local_c = GF_ISOM_INVALID_FILE;
          }
          else {
            ptr->size = ptr->size - 1;
            uVar2 = gf_bs_read_u8(bs_local);
            ptr->quality_entry_count = (u8)uVar2;
            for (i = 0; i < (int)(uint)ptr->quality_entry_count; i = i + 1) {
              j_1 = 0;
              tmp_strsize = (u32)ptr->size;
              while (tmp_strsize != 0) {
                if (ptr->size == 0) {
                  return GF_ISOM_INVALID_FILE;
                }
                ptr->size = ptr->size - 1;
                uVar2 = gf_bs_read_u8(bs_local);
                tmp_str[j_1] = (char)uVar2;
                tmp_strsize = tmp_strsize - 1;
                if (tmp_str[j_1] == '\0') break;
                j_1 = j_1 + 1;
              }
              if (j_1 != 0) {
                pGVar1 = ptr->quality_entry_table;
                pcVar5 = gf_strdup(tmp_str);
                gf_list_insert(pGVar1,pcVar5,i);
              }
            }
            i = 0;
            tmp_strsize = (u32)ptr->size;
            while (tmp_strsize != 0) {
              if (ptr->size == 0) {
                return GF_ISOM_INVALID_FILE;
              }
              ptr->size = ptr->size - 1;
              uVar2 = gf_bs_read_u8(bs_local);
              tmp_str[i] = (char)uVar2;
              tmp_strsize = tmp_strsize - 1;
              if (tmp_str[i] == '\0') break;
              i = i + 1;
            }
            if (i != 0) {
              pcVar5 = gf_strdup(tmp_str);
              ptr->drm_data = pcVar5;
            }
            i = 0;
            tmp_strsize = (u32)ptr->size;
            while (tmp_strsize != 0) {
              if (ptr->size == 0) {
                return GF_ISOM_INVALID_FILE;
              }
              ptr->size = ptr->size - 1;
              uVar2 = gf_bs_read_u8(bs_local);
              tmp_str[i] = (char)uVar2;
              tmp_strsize = tmp_strsize - 1;
              if (tmp_str[i] == '\0') break;
              i = i + 1;
            }
            if (i != 0) {
              pcVar5 = gf_strdup(tmp_str);
              ptr->meta_data = pcVar5;
            }
            if (ptr->size == 0) {
              local_c = GF_ISOM_INVALID_FILE;
            }
            else {
              ptr->size = ptr->size - 1;
              uVar2 = gf_bs_read_u8(bs_local);
              ptr->segment_run_table_count = (u8)uVar2;
              for (i = 0; i < (int)(uint)ptr->segment_run_table_count; i = i + 1) {
                asrt = (GF_AdobeSegmentRunTableBox *)0x0;
                e = gf_isom_box_parse((GF_Box **)&asrt,bs_local);
                if (e != GF_OK) {
                  if (asrt != (GF_AdobeSegmentRunTableBox *)0x0) {
                    gf_isom_box_del((GF_Box *)asrt);
                  }
                  gf_free(tmp_str);
                  return e;
                }
                gf_list_add(ptr->segment_run_table_entries,asrt);
              }
              if (ptr->size == 0) {
                local_c = GF_ISOM_INVALID_FILE;
              }
              else {
                ptr->size = ptr->size - 1;
                uVar2 = gf_bs_read_u8(bs_local);
                ptr->fragment_run_table_count = (u8)uVar2;
                for (i = 0; i < (int)(uint)ptr->fragment_run_table_count; i = i + 1) {
                  afrt = (GF_AdobeFragmentRunTableBox *)0x0;
                  e = gf_isom_box_parse((GF_Box **)&afrt,bs_local);
                  if (e != GF_OK) {
                    if (afrt != (GF_AdobeFragmentRunTableBox *)0x0) {
                      gf_isom_box_del((GF_Box *)afrt);
                    }
                    gf_free(tmp_str);
                    return e;
                  }
                  gf_list_add(ptr->fragment_run_table_entries,afrt);
                }
                gf_free(tmp_str);
                local_c = GF_OK;
              }
            }
          }
        }
      }
    }
  }
  return local_c;
}