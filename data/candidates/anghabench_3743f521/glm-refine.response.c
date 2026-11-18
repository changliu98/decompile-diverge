const char *__cdecl SSL_alert_desc_string_long(int value)
{
    switch ((unsigned char)value)
    {
        case 128: return "user canceled";
        case 129: return "unsupported extension";
        case 130: return "unrecognized name";
        case 131: return "unknown PSK identity";
        case 132: return "unknown CA";
        case 133: return "record overflow";
        case 134: return "protocol version";
        case 135: return "no renegotiation";
        case 136: return "no application protocol";
        case 137: return "internal error";
        case 138: return "insufficient security";
        case 139: return "export restriction";
        case 140: return "decrypt error";
        case 141: return "decryption failed";
        case 142: return "decode error";
        case 143: return "certificate unobtainable";
        case 144: return "bad certificate status response";
        case 145: return "bad certificate hash value";
        case 146: return "access denied";
        case 147: return "unsupported certificate";
        case 148: return "unexpected_message";
        case 149: return "no certificate";
        case 150: return "illegal parameter";
        case 151: return "handshake failure";
        case 152: return "decompression failure";
        case 153: return "close notify";
        case 154: return "certificate unknown";
        case 155: return "certificate revoked";
        case 156: return "certificate expired";
        case 157: return "bad record mac";
        case 158: return "bad certificate";
        default:  return "unknown";
    }
}