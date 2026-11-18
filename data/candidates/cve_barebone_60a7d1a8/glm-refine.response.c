define PJ_STUN_HDR_LEN               20

pj_status_t __cdecl pjstun_parse_msg(void *buf, pj_size_t buf_len, pjstun_msg *msg)
{
  msg->hdr = (pjstun_msg_hdr *)buf;

  // Validate STUN message type
  pj_uint16_t msg_type = foldCase(msg->hdr->type);
  if ( (unsigned int)(msg_type - 1) >= 2 && 
       (unsigned int)(msg_type - 257) >= 2 && 
       (unsigned int)(msg_type - 273) > 1 )
  {
    return PJ_STUN_ERR_INVALID_MSG_TYPE;
  }

  // Validate STUN message length
  pj_uint16_t msg_len = foldCase(msg->hdr->length);
  if (msg_len != buf_len - PJ_STUN_HDR_LEN)
    return PJ_STUN_ERR_INVALID_LENGTH;

  // Parse attributes
  msg->attr_count = 0;
  char *p_attr = (char *)buf + PJ_STUN_HDR_LEN;
  
  while (msg_len)
  {
    pjstun_attr_hdr **attr = &msg->attr[msg->attr_count];
    *attr = (pjstun_attr_hdr *)p_attr;
    
    // Calculate 32-bit aligned attribute length
    unsigned int attr_len = (foldCase((*attr)->length) + 7) & 0xFFFFFFFC;
    
    if (msg_len < attr_len)
      return PJ_STUN_ERR_INVALID_ATTR;
    
    // The return value of this call is discarded; likely validates or byte-swaps the type
    foldCase((*attr)->type);
    
    msg_len -= attr_len;
    p_attr += attr_len;
    ++msg->attr_count;
  }
  
  return 0;
}