const char *SSL_alert_desc_string_long(int value) {
    unsigned char val = (unsigned char)value;
    const char *str;

    switch (val) {
        case 128: str = "close notify"; break;
        case 129: str = "user canceled"; break;
        case 130: str = "no renegotiation"; break;
        case 131: str = "unsupported extension"; break;
        case 132: str = "certificate unobtainable"; break;
        case 133: str = "unrecognized name"; break;
        case 134: str = "bad certificate status response"; break;
        case 135: str = "bad certificate hash value"; break;
        case 136: str = "unknown psk identity"; break;
        case 137: str = "certificate required"; break;
        case 138: str = "generic alert"; break;
        case 139: str = "no application protocol"; break;
        case 140: str = "bad certificate"; break;
        case 141: str = "unsupported certificate"; break;
        case 142: str = "certificate revoked"; break;
        case 143: str = "certificate expired"; break;
        case 144: str = "certificate unknown"; break;
        case 145: str = "illegal parameter"; break;
        case 146: str = "unknown ca"; break;
        case 147: str = "access denied"; break;
        case 148: str = "decode error"; break;
        case 149: str = "decrypt error"; break;
        case 150: str = "export restriction"; break;
        case 151: str = "protocol version"; break;
        case 152: str = "insufficient security"; break;
        case 153: str = "internal error"; break;
        case 154: str = "inappropriate fallback"; break;
        case 155: str = "user canceled"; break;
        case 156: str = "no renegotiation"; break;
        case 157: str = "missing extension"; break;
        case 158: str = "unsupported extension"; break;
        default:  str = "unknown"; break;
    }

    return str;
}