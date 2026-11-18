static void disable(struct drm_i915_private *dev_priv)
{
	dev_priv->csr.wakeref = 0;
}