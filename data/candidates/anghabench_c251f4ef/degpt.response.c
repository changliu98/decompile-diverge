char * hcfs2string(int hcfs_state)
{
    switch(hcfs_state) {
    case 0x80:
        return "suspend";
    case 0x81:
        return "resume";
    case 0x82:
        return "reset";
    case 0x83:
        return "operational";
    default:
        return "?";
    }
}