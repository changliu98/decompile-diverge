/*
 * cve_barebone direct-call harness for schannel_FreeCredentialsHandle
 * (freerdp, winpr/libwinpr/sspi/Schannel/schannel.c)
 *
 * Bug (fixed in freerdp commit 8078b8af1359055972e4fb2f509f543b69169391):
 * schannel_FreeCredentialsHandle() looks up the credentials pointer stored in the
 * caller-supplied PCredHandle, frees it, and returns -- but it never invalidates the
 * handle (sspi_SecureHandleInvalidate()). The handle's dwLower field keeps pointing
 * (encoded) at the now-freed SCHANNEL_CREDENTIALS block. A second call on the SAME
 * handle (e.g. a duplicate/duplicate-cleanup call in an error path) therefore fetches
 * the same pointer again and frees it a second time -> heap double-free (CWE-415).
 * The fix adds sspi_SecureHandleInvalidate(phCredential) right after the pointer is
 * fetched, so a second call sees dwLower==0 and returns SEC_E_INVALID_HANDLE instead.
 *
 * This harness reproduces the bug in isolation: it builds a real SecHandle pointing at
 * a heap-allocated SCHANNEL_CREDENTIALS block using the project's own handle-encoding
 * helpers (verbatim from winpr/libwinpr/sspi/sspi_winpr.c), then calls
 * schannel_FreeCredentialsHandle() one or two times depending on the input byte.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- minimal winpr type/macro surface schannel_FreeCredentialsHandle needs ---- */

typedef long LONG;
typedef uintptr_t ULONG_PTR;
typedef LONG SECURITY_STATUS;

#define SEC_ENTRY
#define nullptr NULL

#define SEC_E_OK ((SECURITY_STATUS)0x00000000)
#define SEC_E_INVALID_HANDLE ((SECURITY_STATUS)0x80090301)

/* winpr/include/winpr/sspi.h (verbatim layout) */
typedef struct
{
	ULONG_PTR dwLower;
	ULONG_PTR dwUpper;
} SecHandle;
typedef SecHandle* PSecHandle;

typedef SecHandle CredHandle;
typedef CredHandle* PCredHandle;

#define SecIsValidHandle(x)                                        \
	((((PSecHandle)(x))->dwLower != ((ULONG_PTR)((intptr_t)-1))) && \
	 (((PSecHandle)(x))->dwUpper != ((ULONG_PTR)((intptr_t)-1))))

/* winpr/libwinpr/sspi/sspi_winpr.c (verbatim bodies) */

void* sspi_SecureHandleGetLowerPointer(SecHandle* handle)
{
	void* pointer = nullptr;

	if (!handle || !SecIsValidHandle(handle) || !handle->dwLower)
		return nullptr;

	pointer = (void*)~((size_t)handle->dwLower);
	return pointer;
}

void sspi_SecureHandleSetLowerPointer(SecHandle* handle, void* pointer)
{
	if (!handle)
		return;

	handle->dwLower = (ULONG_PTR)(~((size_t)pointer));
}

void sspi_SecureHandleSetUpperPointer(SecHandle* handle, void* pointer)
{
	if (!handle)
		return;

	handle->dwUpper = (ULONG_PTR)(~((size_t)pointer));
}

/* ---- Schannel credentials (winpr/libwinpr/sspi/Schannel/schannel.h + schannel.c) ---- */

/* Opaque here: schannel_FreeCredentialsHandle's own body never dereferences a field of
 * this struct, only frees the block -- so only its allocation identity matters. */
typedef struct
{
	int placeholder;
} SCHANNEL_CREDENTIALS;

static void schannel_CredentialsFree(SCHANNEL_CREDENTIALS* credentials)
{
	free(credentials);
}

/* ---- target function, byte-for-byte from target/original_function.c ---- */

static SECURITY_STATUS SEC_ENTRY schannel_FreeCredentialsHandle(PCredHandle phCredential)
{
	SCHANNEL_CREDENTIALS* credentials = nullptr;

	if (!phCredential)
		return SEC_E_INVALID_HANDLE;

	credentials = (SCHANNEL_CREDENTIALS*)sspi_SecureHandleGetLowerPointer(phCredential);

	if (!credentials)
		return SEC_E_INVALID_HANDLE;

	schannel_CredentialsFree(credentials);
	return SEC_E_OK;
}

/* ---- driver ---- */

int main(int argc, char** argv)
{
	if (argc < 2)
		return 0;

	FILE* f = fopen(argv[1], "rb");
	if (!f)
		return 0;

	fseek(f, 0, SEEK_END);
	long fsz = ftell(f);
	fseek(f, 0, SEEK_SET);
	if (fsz < 0)
		fsz = 0;

	unsigned char* buf = (unsigned char*)malloc((size_t)fsz + 1);
	if (!buf)
	{
		fclose(f);
		return 0;
	}
	size_t n = fread(buf, 1, (size_t)fsz, f);
	fclose(f);

	/* byte 0 selects behaviour: odd -> free the handle twice (the bug: double-free),
	 * even -> free it once (safe, matches the post-fix behaviour too). */
	unsigned char mode = (n > 0) ? buf[0] : 0;
	int do_double_free = mode & 1;
	free(buf);

	/* Acquire a credentials handle the way schannel_AcquireCredentialsHandleW does:
	 * heap-allocate SCHANNEL_CREDENTIALS and stash the pointer in a SecHandle. */
	SCHANNEL_CREDENTIALS* credentials =
	    (SCHANNEL_CREDENTIALS*)calloc(1, sizeof(SCHANNEL_CREDENTIALS));
	if (!credentials)
		return 0;

	CredHandle credHandle;
	sspi_SecureHandleSetLowerPointer(&credHandle, (void*)credentials);
	sspi_SecureHandleSetUpperPointer(&credHandle, (void*)"Schannel");

	/* First release: always legitimate, consumes `credentials`. */
	schannel_FreeCredentialsHandle(&credHandle);

	if (do_double_free)
	{
		/* The handle was never invalidated (that's the missing fix), so
		 * sspi_SecureHandleGetLowerPointer() still yields the freed pointer here ->
		 * schannel_CredentialsFree() frees it a second time. */
		schannel_FreeCredentialsHandle(&credHandle);
	}

	return 0;
}
