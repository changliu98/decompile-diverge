void
a_or(struct evmap_signal *map)
{
	EVLOCK_UNLOCK(map->lock);
}