static void func0(unsigned int channel,
					    struct snd_pcm_hardware *hardware)
{
	if (channel > 128)
		hardware->rates = 0;
	else {
		hardware->rates = 0;
		hardware->rate_min = 229376 + channel * 256;
		hardware->rate_max = hardware->rate_min;
	}
}