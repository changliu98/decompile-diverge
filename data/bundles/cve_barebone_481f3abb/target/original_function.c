static UINT xf_rail_server_execute_result(RailClientContext* context,
                                          const RAIL_EXEC_RESULT_ORDER* execResult)
{
	WINPR_ASSERT(context);
	WINPR_ASSERT(execResult);

	xfContext* xfc = (xfContext*)context->custom;
	WINPR_ASSERT(xfc);

	if (execResult->execResult != RAIL_EXEC_S_OK)
	{
		WLog_ERR(TAG, "RAIL exec error: execResult=%s NtError=0x%X\n",
		         error_code_names[execResult->execResult], execResult->rawResult);
		freerdp_abort_connect_context(&xfc->common.context);
	}

	return CHANNEL_RC_OK;
}