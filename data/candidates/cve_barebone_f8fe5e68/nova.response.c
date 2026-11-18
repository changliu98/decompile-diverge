static long imcb_file_send_start(struct drm_gem_object *obj,
				  unsigned long unaligned_addr,
				  unsigned long unaligned_size,
				  unsigned long max)
{
	struct etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);
	struct page **pages = etnaviv_obj->pages;
	long ret;

	if (etnaviv_obj->vaddr)
		ret = etnaviv_obj->ops->iommu_map(etnaviv_obj, pages,
						  unaligned_size, max);
	else
		ret = 0;

	return ret;
}