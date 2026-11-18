MOBI_RET mobi_reconstruct_infl(char *outstring,MOBIIndx *infl,MOBIIndexEntry *orth_entry)

{
  MOBI_RET MVar1;
  int iVar2;
  size_t sVar3;
  size_t sVar4;
  size_t sVar5;
  size_t sVar6;
  char *__s;
  int n;
  MOBI_RET ret;
  int decoded_length;
  uchar *rule;
  uchar decoded [501];
  char *group_name;
  size_t j;
  size_t part_cnt;
  uint32_t *parts;
  size_t group_cnt;
  uint32_t *groups;
  size_t offset;
  size_t i;
  size_t label_length;
  size_t outlen;
  size_t initlen;
  char infl_tag [501];
  char name_attr [501];
  char *iform_tag;
  char *end_tag;
  char *start_tag;
  size_t infl_count;
  uint32_t *infl_groups;
  char *label;
  MOBIIndexEntry *orth_entry_local;
  MOBIIndx *infl_local;
  char *outstring_local;
  MOBI_RET local_c;
  
  label = orth_entry->label;
  infl_groups = (uint32_t *)0x0;
  orth_entry_local = orth_entry;
  infl_local = infl;
  outstring_local = outstring;
  sVar3 = mobi_get_indxentry_tagarray(&infl_groups,orth_entry,0x2a);
  if ((sVar3 == 0) || (infl_groups == (uint32_t *)0x0)) {
    local_c = MOBI_SUCCESS;
  }
  else {
    strcpy(outstring_local,"<idx:infl>");
    sVar4 = strlen("<idx:infl>");
    sVar5 = strlen("</idx:infl>");
    outlen = sVar4 + sVar5;
    initlen = outlen;
    label_length = strlen(label);
    if (label_length < 0x1f5) {
      if (infl_local->cncx_record == (MOBIPdbRecord *)0x0) {
        local_c = MOBI_DATA_CORRUPT;
      }
      else {
        for (i = 0; i < sVar3; i = i + 1) {
          offset = (size_t)infl_groups[i];
          if (infl_local->entries_count <= offset) {
            return MOBI_DATA_CORRUPT;
          }
          group_cnt = mobi_get_indxentry_tagarray(&groups,infl_local->entries + offset,5);
          sVar6 = mobi_get_indxentry_tagarray(&parts,infl_local->entries + offset,0x1a);
          if (group_cnt != sVar6) {
            return MOBI_DATA_CORRUPT;
          }
          for (j = 0; j < sVar6; j = j + 1) {
            name_attr[0] = '\0';
            __s = mobi_get_cncx_string(infl_local->cncx_record,groups[j]);
            if (__s == (char *)0x0) {
              return MOBI_MALLOC_FAILED;
            }
            sVar4 = strlen(__s);
            if (sVar4 != 0) {
              snprintf(name_attr,500," name=\"%s\"",__s);
            }
            free(__s);
            memset(decoded,0,0x1f5);
            rule = (uchar *)infl_local->entries[parts[j]].label;
            memcpy(decoded,label,label_length);
            decoded_length = (int)label_length;
            MVar1 = mobi_decode_infl(decoded,&decoded_length,rule);
            if (MVar1 != MOBI_SUCCESS) {
              return MVar1;
            }
            if ((decoded_length != 0) &&
               (iVar2 = snprintf(infl_tag,500,"<idx:iform%s value=\"%s\"/>",name_attr,decoded),
               iVar2 < 0x1f5)) {
              sVar4 = strlen(infl_tag);
              outlen = sVar4 + outlen;
              if (25000 < outlen) {
                return MOBI_ERROR;
              }
              strcat(outstring_local,infl_tag);
            }
          }
        }
        if (outlen == initlen) {
          *outstring_local = '\0';
        }
        else {
          strcat(outstring_local,"</idx:infl>");
        }
        local_c = MOBI_SUCCESS;
      }
    }
    else {
      local_c = MOBI_DATA_CORRUPT;
    }
  }
  return local_c;
}