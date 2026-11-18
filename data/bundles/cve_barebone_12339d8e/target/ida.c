MOBI_RET __cdecl mobi_reconstruct_infl(char *outstring, const MOBIIndx *infl, const MOBIIndexEntry *orth_entry)
{
  size_t v3; // rax
  size_t v5; // [rsp+0h] [rbp-6C0h]
  MOBI_RET ret; // [rsp+10h] [rbp-6B0h]
  int decoded_length; // [rsp+14h] [rbp-6ACh] BYREF
  unsigned __int8 *rule; // [rsp+18h] [rbp-6A8h]
  unsigned __int8 decoded[501]; // [rsp+20h] [rbp-6A0h] BYREF
  char *group_name; // [rsp+218h] [rbp-4A8h]
  size_t j; // [rsp+220h] [rbp-4A0h]
  size_t part_cnt; // [rsp+228h] [rbp-498h]
  uint32_t *parts; // [rsp+230h] [rbp-490h] BYREF
  size_t group_cnt; // [rsp+238h] [rbp-488h]
  uint32_t *groups; // [rsp+240h] [rbp-480h] BYREF
  size_t offset; // [rsp+248h] [rbp-478h]
  size_t i; // [rsp+250h] [rbp-470h]
  size_t label_length; // [rsp+258h] [rbp-468h]
  size_t outlen; // [rsp+260h] [rbp-460h]
  size_t initlen; // [rsp+268h] [rbp-458h]
  char infl_tag[501]; // [rsp+270h] [rbp-450h] BYREF
  char name_attr[501]; // [rsp+470h] [rbp-250h] BYREF
  const char *iform_tag; // [rsp+670h] [rbp-50h]
  const char *end_tag; // [rsp+678h] [rbp-48h]
  const char *start_tag; // [rsp+680h] [rbp-40h]
  size_t infl_count; // [rsp+688h] [rbp-38h]
  uint32_t *infl_groups; // [rsp+690h] [rbp-30h] BYREF
  const char *label; // [rsp+698h] [rbp-28h]
  const MOBIIndexEntry *orth_entrya; // [rsp+6A0h] [rbp-20h]
  const MOBIIndx *infla; // [rsp+6A8h] [rbp-18h]
  char *outstringa; // [rsp+6B0h] [rbp-10h]

  outstringa = outstring;
  infla = infl;
  orth_entrya = orth_entry;
  label = orth_entry->label;
  infl_groups = 0LL;
  infl_count = mobi_get_indxentry_tagarray(&infl_groups, orth_entry, 0x2AuLL);
  if ( !infl_count || !infl_groups )
    return 0;
  start_tag = "<idx:infl>";
  end_tag = "</idx:infl>";
  iform_tag = "<idx:iform%s value=\"%s\"/>";
  strcpy(outstringa, "<idx:infl>");
  v5 = strlen("<idx:infl>");
  initlen = strlen("</idx:infl>") + v5;
  outlen = initlen;
  label_length = strlen(label);
  if ( label_length > 0x1F4 )
    return 3;
  if ( !infla->cncx_record )
    return 3;
  for ( i = 0LL; i < infl_count; ++i )
  {
    offset = infl_groups[i];
    if ( offset >= infla->entries_count )
      return 3;
    group_cnt = mobi_get_indxentry_tagarray(&groups, &infla->entries[offset], 5uLL);
    part_cnt = mobi_get_indxentry_tagarray(&parts, &infla->entries[offset], 0x1AuLL);
    if ( group_cnt != part_cnt )
      return 3;
    for ( j = 0LL; j < part_cnt; ++j )
    {
      name_attr[0] = 0;
      group_name = mobi_get_cncx_string(infla->cncx_record, groups[j]);
      if ( !group_name )
        return 7;
      if ( strlen(group_name) )
        snprintf(name_attr, 0x1F4uLL, " name=\"%s\"", group_name);
      free(group_name);
      memset(decoded, 0, sizeof(decoded));
      rule = (unsigned __int8 *)infla->entries[parts[j]].label;
      memcpy(decoded, label, label_length);
      decoded_length = label_length;
      ret = mobi_decode_infl(decoded, &decoded_length, rule);
      if ( ret )
        return ret;
      if ( decoded_length && snprintf(infl_tag, 0x1F4uLL, iform_tag, name_attr, decoded) <= 500 )
      {
        v3 = strlen(infl_tag);
        outlen += v3;
        if ( outlen > 0x61A8 )
          return 1;
        strcat(outstringa, infl_tag);
      }
    }
  }
  if ( outlen == initlen )
    *outstringa = 0;
  else
    strcat(outstringa, end_tag);
  return 0;
}