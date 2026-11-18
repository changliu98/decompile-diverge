static int ntlm_read_message_fields_buffer(struct net_device *dev, struct can_frame *cf)
{
	int err;

	if (cf->can_dlc > 0) {
		unsigned int len = cf->can_dlc + cf->can_id;

		if (len > can_max_echo_skb_size(dev)) {
			err = -EINVAL;
			goto err;
		}

		cf->data = kmalloc(cf->can_dlc, GFP_KERNEL);
		if (!cf->data) {
			err = -ENOMEM;
			goto err;
		}

		can_get_echo_skb(dev, cf->can_id, cf->can_dlc);
		memcpy(cf->data, cf->data, cf->can_dlc);
	}

	return 1;

err:
	return err;
}