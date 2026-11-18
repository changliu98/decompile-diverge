static inline u32 qcom_nandc_calc_ecc_bytes(u8 rd, u8 rs1)
{
	return rs1 == 4? 0x10 : 0xc;
}