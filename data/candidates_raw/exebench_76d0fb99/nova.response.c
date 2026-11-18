static void func0(struct mlx5_wqe_umr_ctrl_seg *umr, u32 key)
{
	umr->mkey_mask |= (u64)key << 4;
}