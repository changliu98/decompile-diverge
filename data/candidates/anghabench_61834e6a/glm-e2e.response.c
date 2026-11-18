const char *cmd_to_str(int cmd) {
    const char *str;
    switch (cmd) {
        case 0x80: str = "CMD_80"; break; // 0x20a4
        case 0x81: str = "CMD_81"; break; // 0x20ac
        case 0x82: str = "CMD_82"; break; // 0x20ba
        case 0x83: str = "CMD_83"; break; // 0x20c7
        case 0x84: str = "CMD_84"; break; // 0x20d4
        case 0x85: str = "CMD_85"; break; // 0x20e1
        case 0x86: str = "CMD_86"; break; // 0x20ec
        case 0x87: str = "CMD_87"; break; // 0x20fb
        case 0x88: str = "CMD_88"; break; // 0x210a
        case 0x89: str = "CMD_89"; break; // 0x2117
        case 0x8a: str = "CMD_8a"; break; // 0x212a
        case 0x8b: str = "CMD_8b"; break; // 0x213b
        case 0x8c: str = "CMD_8c"; break; // 0x214f
        case 0x8d: str = "CMD_8d"; break; // 0x2164
        case 0x8e: str = "CMD_8e"; break; // 0x2176
        case 0x8f: str = "CMD_8f"; break; // 0x218e
        case 0x90: str = "CMD_90"; break; // 0x219b
        case 0x91: str = "CMD_91"; break; // 0x21ab
        case 0x92: str = "CMD_92"; break; // 0x21bb
        case 0x93: str = "CMD_93"; break; // 0x21d0
        case 0x94: str = "CMD_94"; break; // 0x21d8
        case 0x95: str = "CMD_95"; break; // 0x21e4
        case 0x96: str = "CMD_96"; break; // 0x21f4
        case 0x97: str = "CMD_97"; break; // 0x2200
        case 0x98: str = "CMD_98"; break; // 0x2213
        case 0x99: str = "CMD_99"; break; // 0x2222
        case 0x9a: str = "CMD_9a"; break; // 0x2235
        case 0x9b: str = "CMD_9b"; break; // 0x224d
        case 0x9c: str = "CMD_9c"; break; // 0x2264
        case 0x9d: str = "CMD_9d"; break; // 0x2276
        case 0x9e: str = "CMD_9e"; break; // 0x2287
        case 0x9f: str = "CMD_9f"; break; // 0x229b
        case 0xa0: str = "CMD_a0"; break; // 0x22a9
        case 0xa1: str = "CMD_a1"; break; // 0x22b7
        case 0xa2: str = "CMD_a2"; break; // 0x22c5
        case 0xa3: str = "CMD_a3"; break; // 0x22dc
        case 0xa4: str = "CMD_a4"; break; // 0x22f0
        case 0xa5: str = "CMD_a5"; break; // 0x2300
        case 0xa6: str = "CMD_a6"; break; // 0x230b
        case 0xa7: str = "CMD_a7"; break; // 0x2316
        default:   str = "Unknown"; break; // 0x231b
    }
    return str;
}