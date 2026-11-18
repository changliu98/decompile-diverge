int editorSyntaxToColor(int hl) {
    switch (hl) {
        case 2:
            return 36; // 0x24
        case 3:
            return 33; // 0x21
        case 4:
            return 32; // 0x20
        case 5:
            return 35; // 0x23
        case 6:
            return 31; // 0x1f
        case 7:
            return 34; // 0x22
        default:
            return 37; // 0x25
    }
}