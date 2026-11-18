static void func0(struct sony_sc *sc,
				  struct snd_pcm_runtime *runtime,
				  unsigned int offset)
{
	unsigned int i, j;
	unsigned int rate;
	unsigned int channels;
	unsigned int width;

	if (offset < 8 || offset > runtime->size - 18)
		return;

	rate = snd_pcm_rate_to_rate_bit(runtime->rate);
	if (rate > 1000)
		return;

	for (i = 0; i < rate; i++) {
		j = i + 2 + offset;

		if (j + 12 > runtime->size)
			return;

		channels = snd_pcm_rate_to_channels(runtime->rate,
						    runtime->channels);

		switch (channels) {
		case 1:
			if (sony_read_spdif_bit(runtime, j, &width))
				sc->spdif.mono = width;
			break;
		case 2:
			if (sony_read_spdif_bit(runtime, j, &width))
				sc->spdif.stereo = width;
			break;
		case 4:
			if (sony_read_spdif_bit(runtime, j, &width))
				sc->spdif.quad = width;
			break;
		case 6:
			if (sony_read_spdif_bit(runtime, j, &width))
				sc->spdif.surround = width;
			break;
		}
	}
}