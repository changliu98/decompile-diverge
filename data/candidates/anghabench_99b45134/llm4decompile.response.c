void get_scl_sda_value(uint8_t line, uint8_t *scl, uint8_t *sda)
{
	switch (line) {
	case SMU_I2C_LINE_ID_0:
		*scl = SMU7_I2C_SCL;
		*sda = SMU7_I2C_SDA;
		break;
	case SMU_I2C_LINE_ID_1:
		*scl = SMU7_I2C_DDC1CLK;
		*sda = SMU7_I2C_DDC1DATA;
		break;
	case SMU_I2C_LINE_ID_2:
		*scl = SMU7_I2C_DDC2CLK;
		*sda = SMU7_I2C_DDC2DATA;
		break;
	case SMU_I2C_LINE_ID_3:
		*scl = SMU7_I2C_DDC3CLK;
		*sda = SMU7_I2C_DDC3DATA;
		break;
	case SMU_I2C_LINE_ID_4:
		*scl = SMU7_I2C_DDC4CLK;
		*sda = SMU7_I2C_DDC4DATA;
		break;
	case SMU_I2C_LINE_ID_5:
		*scl = SMU7_I2C_DDC5CLK;
		*sda = SMU7_I2C_DDC5DATA;
		break;
	case SMU_I2C_LINE_ID_6:
		*scl = SMU7_I2C_DDC6CLK;
		*sda = SMU7_I2C_DDC6DATA;
		break;
	case SMU_I2C_LINE_ID_VGA:
		*scl = SMU7_I2C_DDCVGACLK;
		*sda = SMU7_I2C_DDCVGADATA;
		break;
	default:
		*scl = 0;
		*sda = 0;
		break;
	}
}