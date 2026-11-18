const char *hcfs2string(int state) {
    switch (state) {
        case 128: return "suspend";
        case 129: return "resume";
        case 130: return "reset";
        case 131: return "operational";
        default:  return "?";
    }
}