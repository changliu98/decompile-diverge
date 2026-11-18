int int_to_ibta_mtu(int mtu) {
    int ret_val;
    
    if (mtu == 0x100) {
        ret_val = IB_MTU_256;
    } else if (mtu == 0x200) {
        ret_val = IB_MTU_512;
    } else if (mtu == 0x400) {
        ret_val = IB_MTU_1024;
    } else if (mtu == 0x800) {
        ret_val = IB_MTU_2048;
    } else if (mtu == 0x1000) {
        ret_val = IB_MTU_4096;
    } else {
        ret_val = -1;
    }
    
    return ret_val;
}