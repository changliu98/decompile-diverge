void ndo_print_vqp(struct netdissect_options *ndo, unsigned char *pptr, unsigned int length)
{
  struct vqp_msg *msg;
  struct vqp_obj *obj;
  int i;
  int items;
  int len;
  int lenb;
  int lenc;
  int (*printf)(struct netdissect_options *ndo, char *fmt, ...);
  int (*printfb)(struct netdissect_options *ndo, char *fmt, ...);
  int (*printfc)(struct netdissect_options *ndo, char *fmt, ...);
  int vqp_ver;
  char *type;
  char *err;
  unsigned int errcode;
  unsigned int seq;
  if (ndo->ndo_snapend < (pptr + sizeof(struct vqp_msg)) ||
      pptr > ndo->ndo_snapend - sizeof(struct vqp_msg)) {
    ndo->ndo_printf(ndo, "\n\t[|VQP]");
    return;
  }
  msg = (struct vqp_msg *)pptr;
  if (msg->vqp_ver != 1) {
    ndo->ndo_printf(ndo, "VQP version %u packet not supported", msg->vqp_ver);
    return;
  }
  if (ndo->ndo_vflag < 1) {
    printf = ndo->ndo_printf;
    printf(ndo, "VQPv%u %s Message, error-code %s (%u), length %u",
           msg->vqp_ver,
           vqp_msg_type_val2str(&vqp_msg_type_values, msg->vqp_type),
           vqp_msg_type_val2str(&vqp_error_code_values, msg->vqp_errcode),
           msg->vqp_errcode,
           length);
    return;
  }
  items = msg->vqp_items;
  printf = ndo->ndo_printf;
  printf(ndo, "\n\tVQPv%u, %s Message, error-code %s (%u), seq 0x%08x, "
         "items %u, length %u",
         msg->vqp_ver,
         vqp_msg_type_val2str(&vqp_msg_type_values, msg->vqp_type),
         vqp_msg_type_val2str(&vqp_error_code_values, msg->vqp_errcode),
         msg->vqp_errcode,
         ntohll(msg->vqp_seq),
         items,
         length);
  pptr = (unsigned char *)msg->vqp_obj;
  len = length - sizeof(struct vqp_msg);
  for (i = items; i > 0 && len > 0; i--) {
    obj = (struct vqp_obj *)pptr;
    lenb = len - sizeof(struct vqp_obj);
    if (lenb < 0)
      break;
    obj->vqp_type = ntohll(obj->vqp_type);
    obj->vqp_len = ntohll(obj->vqp_len);
    pptr = (unsigned char *)obj->vqp_val;
    lenc = lenb - obj->vqp_len;
    if (lenc < 0)
      break;
    printf = ndo->ndo_printf;
    printf(ndo, "\n\t  %s Object (0x%08x), length %u, value: ",
           vqp_obj_val2str(&vqp_obj_values, obj->vqp_type),
           obj->vqp_type,
           obj->vqp_len);
    if (obj->vqp_type == 0 || obj->vqp_len == 0)
      break;
    switch (obj->vqp_type) {
      case VQP_OBJ_ID:
        printfb = ndo->ndo_printf;
        printfb(ndo, "%s (0x%08x)",
               vqp_id_val2str(ndo, pptr),
               ntohll(pptr));
        break;
      case VQP_OBJ_IPADDR:
      case VQP_OBJ_IPADDR6:
      case VQP_OBJ_IPNET:
      case VQP_OBJ_IPNET6:
        vqp_ip_print(ndo, pptr, obj->vqp_len);
        break;
      case VQP_OBJ_TEXT:
      case VQP_OBJ_TEXT_ID:
        printfc = ndo->ndo_printf;
        printfc(ndo, "%s",
               vqp_text_val2str(ndo, pptr));
        break;
      default:
        if (ndo->ndo_vflag < 2)
          vqp_print_bytes(ndo, pptr, "    ", obj->vqp_len);
        break;
    }
    pptr = (unsigned char *)pptr + obj->vqp_len;
    len = lenc;
  }
}