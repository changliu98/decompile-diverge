static int
mwifiex_cmd_append_vsie_tlv(unsigned char *buf, unsigned short vsie, char **p)
{
 struct vs_param_set *vset;
 int ret = 0, i;

 if (!p) {
  ret = 0;
 } else if (!*p) {
  ret = 0;
 } else {
  for (i = 0; i < 9; i++) {
   if ((vsie & (((unsigned short *)buf)[i])) != 0) {
    vset = (struct vs_param_set *)*p;
    vset->type = 0x10a;
    vset->len = (((unsigned short *)buf)[i + 2] & 0xff) + 2;
    memcpy(&vset->data, &((unsigned short *)buf)[i + 1],
           vset->len);
    *p += sizeof(struct vs_param_set) + vset->len;
    ret += sizeof(struct vs_param_set) + vset->len;
   }
  }
 }

 return ret;
}