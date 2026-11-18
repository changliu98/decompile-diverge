__attribute__((used)) static int mtu_to_enum(u32 mtu)
{
	int enum_mtu;

	switch (mtu) {
	case 256: enum_mtu = IB_MTU_256; break;
	case 512: enum_mtu = IB_MTU_512; break;
	case 1024: enum_mtu = IB_MTU_1024; break;
	case 2048: enum_mtu = IB_MTU_2048; break;
	case 4096: enum_mtu = IB_MTU_4096; break;
	default: enum_mtu = -1;
	}

	return enum_mtu;
}