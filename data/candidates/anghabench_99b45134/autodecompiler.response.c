__attribute__((used)) static void get_scl_sda_value(unsigned char id,
					unsigned char *psclk_index,
					unsigned char *pdclk_index)
{
	switch (id) {
	case SMU7_DPM_INDEX_0:
		*psclk_index = SMU7_I2C_DDC1CLK;
		*pdclk_index = SMU7_I2C_DDC1DATA;
		break;
	case SMU7_DPM_INDEX_1:
		*psclk_index = SMU7_I2C_DDC2CLK;
		*pdclk_index = SMU7_I2C_DDC2DATA;
		break;
	case SMU7_DPM_INDEX_2:
		*psclk_index = SMU7_I2C_DDC3CLK;
		*pdclk_index = SMU7_I2C_DDC3DATA;
		break;
	case SMU7_DPM_INDEX_3:
		*psclk_index = SMU7_I2C_DDC4CLK;
		*pdclk_index = SMU7_I2C_DDC4DATA;
		break;
	case SMU7_DPM_INDEX_4:
		*psclk_index = SMU7_I2C_DDC5CLK;
		*pdclk_index = SMU7_I2C_DDC5DATA;
		break;
	case SMU7_DPM_INDEX_5:
		*psclk_index = SMU7_I2C_DDC6CLK;
		*pdclk_index = SMU7_I2C_DDC6DATA;
		break;
	case SMU7_DPM_INDEX_6:
		*psclk_index = SMU7_I2C_SCL;
		*pdclk_index = SMU7_I2C_SDA;
		break;
	case SMU7_DPM_INDEX_7:
		*psclk_index = SMU7_I2C_DDCVGACLK;
		*pdclk_index = SMU7_I2C_DDCVGADATA;
		break;
	default:
		*psclk_index = 0;
		*pdclk_index = 0;
	}
}