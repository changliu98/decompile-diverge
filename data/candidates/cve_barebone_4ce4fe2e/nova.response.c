static void gf_av1_reset_state(struct rpc_xprt *xprt, bool force)
{
	struct rpc_xprt_switch *xps;
	struct rpc_xprt_iter iter;

	if (xprt->xprt_switch) {
		while (rpc_xprt_iter_switch_start(xprt->xprt_switch, &iter)) {
			xps = rpc_xprt_iter_switch(xprt->xprt_switch, &iter);
			if (xps->xps_iter.xpi_ops)
				rpc_xprt_iter_switch_stop(xps->xps_iter.xpi_ops);
			rpc_xprt_iter_switch_stop(&xps->xps_iter);
		}
	}
	if (xprt->xprt_socket) {
		while (rpc_xprt_iter_socket_start(xprt->xprt_socket, &iter)) {
			xps = rpc_xprt_iter_socket(xprt->xprt_socket, &iter);
			if (xps->xps_iter.xpi_ops)
				rpc_xprt_iter_socket_stop(xps->xps_iter.xpi_ops);
			rpc_xprt_iter_socket_stop(&xps->xps_iter);
		}
	}
	xps = xprt->xprt_switch;
	xprt->xprt_switch = xprt->xprt_socket;
	xprt->xprt_socket = xps;
	memset(&xprt->xprt_iter, 0, sizeof(xprt->xprt_iter));
	xprt->xprt_iter.xpi_ops = &xprt_iter_ops;
	xprt->xprt_iter.xpi_active = true;
	if (force) {
		rpc_xpr