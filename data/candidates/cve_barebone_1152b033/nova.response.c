int hci_req_sync(struct dm_cache_metadata *cmd,
			   struct dm_cache_policy *policy,
			   load_mapping_fn fn, void *context,
			   bool fast_copy)
{
	int r;

	if (!dm_cache_discard_begin(cmd, policy)) {
		r = -EWOULDBLOCK;
		goto out;
	}

	READ_LOCK(cmd);
	r = __load_mappings(cmd, policy, fn, context, fast_copy);
	READ_UNLOCK(cmd);

out:
	dm_cache_discard_end(cmd);
	return r;
}