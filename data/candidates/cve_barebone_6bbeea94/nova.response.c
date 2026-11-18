static int opj_j2k_add_tlmarker(unsigned int chan, struct comedi_device *dev,
			  unsigned int range, unsigned long iobase,
			  unsigned int ao_scan_period)
{
	unsigned int val;
	int ret;

	
	do {
		ret = 0;

		do {
			val = devpriv->ao_readback[chan];
			if (devpriv->ao_readback[chan] <
			    devpriv->ao_min_max[chan][0])
				devpriv->ao_readback[chan] =
				    devpriv->ao_min_max[chan][0];
			else if (devpriv->ao_readback[chan] >
				 devpriv->ao_min_max[chan][1])
				devpriv->ao_readback[chan] =
				    devpriv->ao_min_max[chan][1];

			outb(devpriv->ao_readback[chan],
			     devpriv->daqio + DAQP_AO_REG(chan, 24));
			outb(devpriv->ao_readback[chan],
			     devpriv->daqio + DAQP_AO_REG(chan, 24));
			outb(devpriv->ao_readback[chan],
			     devpriv->daqio + DAQP_AO_REG(chan, 24));
			outb(devpriv->ao_readback[chan],
			     devpriv->daqio + DAQP_AO_REG(chan, 24));

			devpriv->ao_readback[chan]++;
		} while (devpriv->ao_readback[chan]!= val);

		if (range == 0xffe0) {
			val = devpriv->ao_readback[chan];
			if (devpriv->ao_readback[chan])
				devpriv->ao_readback[chan] = val;
			else
				ret = 1;
		}