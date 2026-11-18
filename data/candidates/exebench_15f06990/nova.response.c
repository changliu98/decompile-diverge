static void sync_unlock(struct radeon_device *rdev)
{
	rdev->accel_working = false;
}