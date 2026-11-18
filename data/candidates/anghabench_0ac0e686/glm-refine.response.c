int __cdecl int_to_ibta_mtu(int mtu)
{
    // IBTA MTUs are always powers of 2, starting from 256 up to 4096.
    // We can map them directly to an array using their base-2 logarithm.
    static const int mtu_map[] = {
        -1,          // 1
        -1,          // 2
        -1,          // 4
        -1,          // 8
        -1,          // 16
        -1,          // 32
        -1,          // 64
        -1,          // 128
        IB_MTU_256,  // 256
        IB_MTU_512,  // 512
        IB_MTU_1024, // 1024
        IB_MTU_2048, // 2048
        IB_MTU_4096  // 4096
    };

    // Check if the MTU is a valid power of 2 within our supported range
    if (mtu >= 256 && mtu <= 4096 && (mtu & (mtu - 1)) == 0)
    {
        // Calculate index: log2(mtu)
        int index = 0;
        int val = mtu;
        while (val > 1) {
            val >>= 1;
            index++;
        }
        return mtu_map[index];
    }

    return -1;
}