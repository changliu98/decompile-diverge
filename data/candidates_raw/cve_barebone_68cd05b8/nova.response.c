static int func0(struct spi_device *spi,
					struct st_sensor_settings *settings,
					const char *match)
{
	unsigned int i;

	for (i = 0; i < ST_SENSORS_MAX_SENSORS; i++) {
		if (st_sensors_compatible(settings, match,
					  st_magn_sensors_compatible_table[i])) {
			spi->max_speed_hz = st_magn_sensors_compatible_table[i][2];
			spi->mode = st_magn_sensors_compatible_table[i][3];

			return 0;
		}
	}

	return -ENODEV;
}