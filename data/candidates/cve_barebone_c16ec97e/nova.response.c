static int njs_array_convert_to_slow_array(struct net_device *dev, struct sk_buff *skb)
{
	struct can_frame frame;
	struct can_frame *cf;
	unsigned char *data;
	unsigned int i, len;
	int err;

	can_get_echo_skb(skb, &frame);

	
	skb->data[0] &= 0xFE;

	len = skb->len;
	for (i = 0; i < len; i++) {
		if (skb->data[i]!= 0x07) {
			can_end_echo_skb(dev, &frame, i);
			cf = skb_put_can_frame(dev, &frame, &data, 0);
			if (!cf) {
				err = -EINVAL;
				goto err;
			}
			cf->can_id = skb->data[i];
			cf->can_dlc = skb->data[i+1];
		} else {
			i++;
		}
	}

	can_end_echo_skb(dev, &frame, i);
	skb->data = NULL;

	err = 0;
err:
	return err;
}