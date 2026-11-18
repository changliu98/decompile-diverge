__attribute__((used)) static int q_GetSizeOfMaxRegion(struct drm_minor *minor)
{
#if defined(CONFIG_DEBUG_FS)
	unsigned count;

	struct drm_ttm_tt *ttm = &amdgpu_ttm_tt;
	static const struct drm_info_list info[] = {
		{ "ttm", ttm_tt_info },
		{ "ttm_tt", ttm_tt_stats },
	};

	for (count = 0; count < ARRAY_SIZE(info); ++count) {
		drm_debugfs_create_files(&info[count],
					 1, ttm->debugfs_root, minor);
	}

	return 0;
#else
	return 0;
#endif
}