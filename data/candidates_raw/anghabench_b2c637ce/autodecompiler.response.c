__attribute__((used)) static inline int M_Offset_PSG_Data(int port)
{
	return 0x70 + (port & 1) * 4;
}