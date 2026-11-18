char * SSL_alert_desc_string_long(int value)

{
  int value_local;
  char *local_10;
  
  switch(value & 0xff) {
  case 0x80:
    local_10 = "user canceled";
    break;
  case 0x81:
    local_10 = "unsupported extension";
    break;
  case 0x82:
    local_10 = "unrecognized name";
    break;
  case 0x83:
    local_10 = "unknown PSK identity";
    break;
  case 0x84:
    local_10 = "unknown CA";
    break;
  case 0x85:
    local_10 = "record overflow";
    break;
  case 0x86:
    local_10 = "protocol version";
    break;
  case 0x87:
    local_10 = "no renegotiation";
    break;
  case 0x88:
    local_10 = "no application protocol";
    break;
  case 0x89:
    local_10 = "internal error";
    break;
  case 0x8a:
    local_10 = "insufficient security";
    break;
  case 0x8b:
    local_10 = "export restriction";
    break;
  case 0x8c:
    local_10 = "decrypt error";
    break;
  case 0x8d:
    local_10 = "decryption failed";
    break;
  case 0x8e:
    local_10 = "decode error";
    break;
  case 0x8f:
    local_10 = "certificate unobtainable";
    break;
  case 0x90:
    local_10 = "bad certificate status response";
    break;
  case 0x91:
    local_10 = "bad certificate hash value";
    break;
  case 0x92:
    local_10 = "access denied";
    break;
  case 0x93:
    local_10 = "unsupported certificate";
    break;
  case 0x94:
    local_10 = "unexpected_message";
    break;
  case 0x95:
    local_10 = "no certificate";
    break;
  case 0x96:
    local_10 = "illegal parameter";
    break;
  case 0x97:
    local_10 = "handshake failure";
    break;
  case 0x98:
    local_10 = "decompression failure";
    break;
  case 0x99:
    local_10 = "close notify";
    break;
  case 0x9a:
    local_10 = "certificate unknown";
    break;
  case 0x9b:
    local_10 = "certificate revoked";
    break;
  case 0x9c:
    local_10 = "certificate expired";
    break;
  case 0x9d:
    local_10 = "bad record mac";
    break;
  case 0x9e:
    local_10 = "bad certificate";
    break;
  default:
    local_10 = "unknown";
  }
  return local_10;
}