static inline int error(struct ipoib_dev_priv *priv)
{
	return priv->qp_counter++;
}