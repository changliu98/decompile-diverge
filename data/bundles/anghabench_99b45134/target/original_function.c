void get_scl_sda_value(uint8_t line, uint8_t *scl, uint8_t *sda)
{
	switch (line) {
	case SMU7_I2CLineID_DDC1:
		*scl = SMU7_I2C_DDC1CLK;
		*sda = SMU7_I2C_DDC1DATA;
		break;
	case SMU7_I2CLineID_DDC2:
		*scl = SMU7_I2C_DDC2CLK;
		*sda = SMU7_I2C_DDC2DATA;
		break;
	case SMU7_I2CLineID_DDC3:
		*scl = SMU7_I2C_DDC3CLK;
		*sda = SMU7_I2C_DDC3DATA;
		break;
	case SMU7_I2CLineID_DDC4:
		*scl = SMU7_I2C_DDC4CLK;
		*sda = SMU7_I2C_DDC4DATA;
		break;
	case SMU7_I2CLineID_DDC5:
		*scl = SMU7_I2C_DDC5CLK;
		*sda = SMU7_I2C_DDC5DATA;
		break;
	case SMU7_I2CLineID_DDC6:
		*scl = SMU7_I2C_DDC6CLK;
		*sda = SMU7_I2C_DDC6DATA;
		break;
	case SMU7_I2CLineID_SCLSDA:
		*scl = SMU7_I2C_SCL;
		*sda = SMU7_I2C_SDA;
		break;
	case SMU7_I2CLineID_DDCVGA:
		*scl = SMU7_I2C_DDCVGACLK;
		*sda = SMU7_I2C_DDCVGADATA;
		break;
	default:
		*scl = 0;
		*sda = 0;
		break;
	}
}