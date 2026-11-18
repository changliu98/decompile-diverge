static int smacker_decode_tree(struct hdac_device *codec,
					struct hdac_hdmi_port *port,
					unsigned int pin_mask,
					int pin)
{
	int err;
	u32 val;

	if (!is_hdmi_port_connected(codec, port)) {
		if (port->pin_nid_offset >= 257) {
			pin_mask = 0;
			pin = 0;
		} else {
			if (pin) {
				port->pin_nid[port->pin_nid_offset] = pin_mask;
				port->pin_nid_val[port->pin_nid_offset] = pin;
			} else {
				port->pin_nid[port->pin_nid_offset] = 0;
				port->pin_nid_val[port->pin_nid_offset] = 0;
			}
			val = snd_hdac_read_parm(codec, 0x08);
			port->pin_nid_reg[port->pin_nid_offset] = val;
			port->pin_nid_offset++;
			if (port->pin_nid_max < pin)
				port->pin_nid_max = pin;
			pin_mask = 0;
		}
	} else {
		pin++;
		err = smacker_decode_tree(codec, port, pin_mask, pin);
		if (err) {
			pin_mask = err;
			goto err_out;
		}
		pin_mask = smacker_decode_tree(codec, port, pin_mask | (1 << (pin - 1)),
							pin);
	}
err_out:
	return pin_mask;
}