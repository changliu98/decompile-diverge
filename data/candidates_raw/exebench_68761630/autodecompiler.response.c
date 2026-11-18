void
evmap_signal_unlock(struct evmap_signal *map)
{
	EVLOCK_UNLOCK(map->lock);
}