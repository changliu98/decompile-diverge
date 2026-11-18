static void func0(struct kvm_vm *vm)
{
	if (vm->fd_pagemap >= 0)
		close(vm->fd_pagemap);
	vm->fd_pagemap = -1;
}