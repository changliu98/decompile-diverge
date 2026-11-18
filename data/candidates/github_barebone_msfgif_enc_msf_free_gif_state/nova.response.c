void msf_free_gif_state(struct radeon_device *rdev)
{
	struct radeon_ring *ring;

	if (rdev->ib_pool_ready)
		radeon_sa_bo_manager_suspend(rdev->ring_tmp_bo);
	if (rdev->fence_drv.initialized)
		radeon_fence_driver_suspend(rdev->ddev);
	if (rdev->gem.ready)
		radeon_gem_suspend(rdev->ddev);
	if (rdev->asic->utility_funcs)
		radeon_utility_suspend(rdev->ddev);
	if (rdev->accel_working)
		radeon_accel_suspend(rdev->ddev);

	ring = rdev->ring[0];
	while (ring) {
		struct radeon_ring *tmp = ring->next;
		radeon_ring_fini(ring);
		ring = tmp;
	}
	rdev->ring[0] = NULL;
}