void set_autofs_type_offset(struct nfs4_compound_state *cstate)
{
	cstate->offset = sizeof(struct nfs4_autofs_args);
}