static void func0(struct mlx5_core_dev *dev,
				  struct mlx5_eq_comp *eq,
				  struct mlx5_eq_comp *next_eq)
{
	next_eq->irq_vector = dev->priv.eq_table.eq[eq->irq_vector].vector;
}