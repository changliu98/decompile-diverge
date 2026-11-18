static inline unsigned int func0(struct i2c_adapter *adap)
{
	return sizeof(struct i2c_msg) + 2 * sizeof(union i2c_smbus_data);
}