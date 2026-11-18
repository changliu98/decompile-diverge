char *errstr(int err)
{
    char *str;
    switch (err & 0xff) {
    case -103:
        str = "close notify";
        break;
    case -102:
        str = "certificate unknown";
        break;
    case -101:
        str = "certificate revoked";
        break;
    case -100:
        str = "certificate expired";
        break;
    case -99:
        str = "bad record mac";
        break;
    case -98:
        str = "bad certificate";
        break;
    case -112:
        str = "bad certificate status response";
        break;
    case -113:
        str = "certificate unobtainable";
        break;
    case -114:
        str = "decode error";
        break;
    case -115:
        str = "decryption failed";
        break;
    case -116:
        str = "decrypt error";
        break;
    case -117:
        str = "export restriction";
        break;
    case -118:
        str = "insufficient security";
        break;
    case -119:
        str = "internal error";
        break;
    case -120:
        str = "no application protocol";
        break;
    case -121:
        str = "no renegotiation";
        break;
    case -122:
        str = "protocol version";
        break;
    case -123:
        str = "record overflow";
        break;
    case -124:
        str = "unknown CA";
        break;
    case -125:
        str = "unknown PSK identity";
        break;
    case -126:
        str = "unrecognized name";
        break;
    case -127:
        str = "unsupported extension";
        break;
    case -111:
        str = "bad certificate hash value";
        break;
    case -110:
        str = "access denied";
        break;
    case -109:
        str = "unsupported certificate";
        break;
    case -108:
        str = "unexpected_message";
        break;
    case -107:
        str = "no certificate";
        break;
    case -106:
        str = "illegal parameter";
        break;
    case -105:
        str = "handshake failure";
        break;
    case -104:
        str = "decompression failure";
        break;
    case -11:
        str = "out of memory";
        break;
    case -10:
        str = "no cipher";
        break;
    case -9:
        str = "no such file or directory";
        break;
    case -8:
        str = "file exists";
        break;
    case -7:
        str = "out of data";
        break;
    case -6:
        str = "invalid data";
        break;
    case -5:
        str = "invalid argument";
        break;
    case -4:
        str = "out of range";
        break;
    case -3:
        str = "not implemented";
        break;
    case -2:
        str = "out of resources";
        break;
    case -1:
        str = "system call error";
        break;
    case 0:
        str = "ok";
        break;
    case 1:
        str = "temporary error";
        break;
    case 2:
        str = "no such cipher";
        break;
    case 3:
        str = "no such hash";
        break;
    case 4:
        str = "no such pkey";
        break;
    case 5:
        str = "no such engine";
        break;
    case 6:
        str = "unmatched";
        break;
    case 7:
        str = "unhandled";
        break;
    case 8:
        str = "unverified";
        break;
    case 9:
        str = "unsupported";
        break;
    case 10:
        str = "unavailable";
        break;
    case 11:
        str = "unloaded";
        break;
    case 12:
        str = "uninitialized";
        break;
    case 13:
        str = "unreadable";
        break;
    case 14:
        str = "unwritable";
        break;
    case 15:
        str = "unrecoverable";
        break;
    case 16:
        str = "unparsable";
        break;
    case 17:
        str = "unverifiable";
        break;
    case 18:
        str = "unsupported data";
        break;
    case 19:
        str = "unsupported format";
        break;
    case 20:
        str = "unsupported version";
        break;
    case 21:
        str = "unsupported feature";
        break;
    case 22:
        str = "unsupported compression";
        break;
    case 23:
        str = "unsupported point";
        break;
    case 24:
        str = "unsupported curve";
        break;
    case 25:
        str = "unsupported message";
        break;
    case 26:
        str = "unsupported name";
        break;
    case 27:
        str = "unsupported type";
        break;
    case 28:
        str = "unsupported side";
        break;
    case 29:
        str = "unsupported role";
        break;
    case 30:
        str = "unsupported state";
        break;
    case 31:
        str = "unsupported size";
        break;
    case 32:
        str = "unsupported range";
        break;
    case 33:
        str = "unsupported length";
        break;
    case 34:
        str = "unsupported data type";
        break;
    case 35:
        str = "unsupported key type";
        break;
    case 36:
        str = "unsupported key size";
        break;
    case 37:
        str = "unsupported key range";
        break;
    case 38:
        str = "unsupported key length";
        break;
    case 39:
        str = "unsupported key data";
        break;
    case 40:
        str = "unsupported key format";
        break;
    case 41:
        str = "unsupported key version";
        break;
    case 42:
        str = "unsupported key feature";
        break;
    case 43:
        str = "unsupported key size";
        break;
    case 44:
        str = "unsupported key range";
        break;
    case 45:
        str = "unsupported key length";
        break;
    case 46:
        str = "unsupported key data";
        break;
    case 47:
        str = "unsupported key format";
        break;
    case 48:
        str = "unsupported key version";
        break;
    case 49:
        str = "unsupported key feature";
        break;
    case 50:
        str = "unsupported key size";
        break;
    case 51:
        str = "unsupported key range";
        break;
    case 52:
        str = "unsupported key length";
        break;
    case 53:
        str = "unsupported key data";
        break;
    case 54:
        str = "unsupported key format";
        break;
    case 55:
        str = "unsupported key version";
        break;
    case 56:
        str = "unsupported key feature";
        break;
    case 57:
        str = "unsupported key size";
        break;
    case 58:
        str = "unsupported key range";
        break;
    case 59:
        str = "unsupported key length";
        break;
    case 60:
        str = "unsupported key data";
        break;
    case 61:
        str = "unsupported key format";