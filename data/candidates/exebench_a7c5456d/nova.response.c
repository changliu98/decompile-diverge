static inline u32 atomic_fetch_add(struct dw_i2c_dev *dev, size_t offset)
{
	u32 val = dev->read_fn(dev->dev, offset);

	dev->last_read_offset = offset;

	return val;
}