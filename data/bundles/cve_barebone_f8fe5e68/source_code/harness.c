/* cve_barebone direct-call harness for CVE-2016-10189 (bitlbee)
 * Target: imcb_file_send_start  (protocols/bee_ft.c)
 * Bug class: NULL pointer dereference (CWE-476).
 *
 * Fix commit 701ab8129ba9ea64f569daedca9a8603abad740f changed the guard from
 *     if (bee->ui->ft_in_start) {
 * to
 *     if (bee->ui->ft_in_start && bu) {
 * imcb_file_send_start() looks up the sender's `bee_user_t *bu` via
 * bee_user_by_handle() and, pre-fix, hands it straight to the UI's
 * ft_in_start callback *even when bu is NULL* (unknown handle / buddy not
 * on the list -- e.g. an inbound file-transfer offer from a JID that isn't
 * a known buddy). The IRC UI's callback, bee_irc_ft_in_start() (irc_im.c:
 * 1082-1085), immediately dereferences bu->ic -- a NULL-pointer read one
 * call frame below imcb_file_send_start.
 *
 * This harness calls imcb_file_send_start() directly with a minimal,
 * hand-built object graph: ONE known buddy "alice" is registered on the
 * bee_t's user list; the whole input file becomes the attacker-controlled
 * `handle` argument. A handle that case-insensitively matches "alice"
 * resolves to a real bee_user_t (SAFE). Any other handle makes
 * bee_user_by_handle() return NULL, reproducing the pre-fix crash
 * (TRIGGERING).
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <strings.h>   /* strcasecmp(3) -- stands in for glib's g_strcasecmp,
                         * which is what every real prpl (jabber, msn, oscar,
                         * twitter, yahoo, purple, skype) assigns to
                         * prpl->handle_cmp; see e.g.
                         * protocols/jabber/jabber.c:792
                         * `ret->handle_cmp = g_strcasecmp;` */

/* ==== forward declarations for the mutually-pointing structs (mirrors the
 * forward decls at the top of protocols/bee.h) ==== */
struct bee;
struct bee_user;
struct bee_ui_funcs;
struct im_connection;
struct prpl;
struct account;
struct file_transfer;
struct irc_user;

typedef struct bee bee_t;
typedef struct bee_user bee_user_t;
typedef struct bee_ui_funcs bee_ui_funcs_t;
typedef struct account account_t;
typedef struct file_transfer file_transfer_t;
typedef struct irc_user irc_user_t;

/* ==== minimal glib-container shim (real public field layout: data/next),
 * not invented -- bee_t->users is a GSList* and we don't link glib. ==== */
typedef struct _GSList {
	void *data;
	struct _GSList *next;
} GSList;

/* ==== struct bee_user (protocols/bee.h:67-84), trimmed to the fields
 * touched on this crash path: ic (bee_user_by_handle's identity check +
 * bee_irc_ft_in_start's NULL deref), handle (bee_user_by_handle's string
 * compare), ui_data (bee_irc_ft_in_start's 2nd arg to dccs_send_start). ==== */
struct bee_user {
	struct im_connection *ic;
	char *handle;
	void *ui_data;
};

/* ==== struct prpl (protocols/nogaim.h:142+), trimmed to handle_cmp, the
 * only member reached from imcb_file_send_start's call graph. ==== */
struct prpl {
	int (*handle_cmp)(const char *who1, const char *who2);
};

/* ==== account_t (protocols/account.h:29-47), trimmed to prpl. ==== */
struct account {
	struct prpl *prpl;
};

/* ==== struct im_connection (protocols/nogaim.h:75-99), trimmed to acc/bee. ==== */
struct im_connection {
	account_t *acc;
	bee_t *bee;
};

/* ==== struct bee_ui_funcs (protocols/bee.h:98-139), trimmed to
 * ft_in_start -- the only callback imcb_file_send_start invokes. ==== */
struct bee_ui_funcs {
	struct file_transfer *(*ft_in_start)(bee_t *bee, bee_user_t *bu, const char *file_name, size_t file_size);
};

/* ==== struct bee (protocols/bee.h:32-52), trimmed to users/ui/ui_data. ==== */
struct bee {
	GSList *users;  /* struct bee_user */
	const struct bee_ui_funcs *ui;
	void *ui_data;
};

/* ==== dccs_send_start -- real declaration copied from dcc.h:97. Its full
 * body (dcc.c) does DCC/GLib socket setup that is entirely incidental to
 * the NULL-deref bug (only reached here on the SAFE path, once bu is
 * already known non-NULL) -- EXCEPT its real first line, dcc.c:91
 * `irc_t *irc = (irc_t *) ic->bee->ui_data;`, which this stub keeps
 * verbatim-in-spirit. That is not cosmetic: without a genuine use of `ic`
 * here, clang -O1 inlines this stub into bee_irc_ft_in_start(), proves the
 * `ic` argument (== bu->ic at the actual crash site) is dead, and deletes
 * the very dereference under test -- silently curing the NULL deref. The
 * real dcc.c never has that problem (dcc.c:107 uses `irc->fd`), so
 * preserving this first touch + branching on it (noinline too) is what
 * makes the stub behave like the real linked binary. ==== */
__attribute__((noinline))
file_transfer_t *dccs_send_start(struct im_connection *ic, irc_user_t *iu, const char *file_name, size_t file_size)
{
	(void)iu; (void)file_name; (void)file_size;
	void *irc = ic->bee->ui_data;
	if (irc == (void *)(intptr_t)-1) {
		return (file_transfer_t *)irc;   /* unreachable; keeps the load live */
	}
	return NULL;
}

/* ==== bee_irc_ft_in_start -- VERBATIM from irc_im.c:1082-1085. This is the
 * real callee wired up as bee->ui->ft_in_start for the IRC UI (irc_im.c:
 * 1139, `irc_ui_funcs = { ..., bee_irc_ft_in_start, ... }`) -- the ACTUAL
 * dereference of the possibly-NULL `bu` that CVE-2016-10189 is about. ==== */
static file_transfer_t *bee_irc_ft_in_start(bee_t *bee, bee_user_t *bu, const char *file_name, size_t file_size)
{
	return dccs_send_start(bu->ic, (irc_user_t *) bu->ui_data, file_name, file_size);
}

/* ==== bee_user_by_handle -- VERBATIM from protocols/bee_user.c:82-95. ==== */
bee_user_t *bee_user_by_handle(bee_t *bee, struct im_connection *ic, const char *handle)
{
	GSList *l;

	for (l = bee->users; l; l = l->next) {
		bee_user_t *bu = l->data;

		if (bu->ic == ic && ic->acc->prpl->handle_cmp(bu->handle, handle) == 0) {
			return bu;
		}
	}

	return NULL;
}

/* ==== VERBATIM from data_cve/cve_f8fe5e68/target/original_function.c ==== */
file_transfer_t *imcb_file_send_start(struct im_connection *ic, char *handle, char *file_name, size_t file_size)
{
	bee_t *bee = ic->bee;
	bee_user_t *bu = bee_user_by_handle(bee, ic, handle);

	if (bee->ui->ft_in_start) {
		return bee->ui->ft_in_start(bee, bu, file_name, file_size);
	} else {
		return NULL;
	}
}
/* ==== end verbatim ==== */

int main(int argc, char **argv)
{
	if (argc < 2) {
		return 0;
	}
	FILE *f = fopen(argv[1], "rb");
	if (!f) {
		return 0;
	}
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
	long sz = ftell(f);
	if (sz < 0) { fclose(f); return 0; }
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

	/* HEAP-allocate the input (ASAN-guarded) as a NUL-terminated C string:
	 * the whole file content becomes the attacker-controlled `handle`
	 * argument passed straight into imcb_file_send_start(). */
	char *buf = (char *)malloc((size_t)sz + 1);
	if (!buf) { fclose(f); return 0; }
	size_t n = fread(buf, 1, (size_t)sz, f);
	fclose(f);
	buf[n] = '\0';

	/* ---- minimal object graph imcb_file_send_start() needs: one known
	 * buddy "alice" registered on the bee_t's user list. ---- */
	struct prpl prpl_impl;
	account_t acc;
	struct im_connection conn;
	bee_user_t alice;
	GSList node;
	bee_ui_funcs_t ui_funcs;
	bee_t bee_state;

	prpl_impl.handle_cmp = strcasecmp;
	acc.prpl = &prpl_impl;
	conn.acc = &acc;
	conn.bee = &bee_state;
	alice.ic = &conn;
	alice.handle = "alice";
	alice.ui_data = NULL;
	node.data = &alice;
	node.next = NULL;
	ui_funcs.ft_in_start = bee_irc_ft_in_start;
	bee_state.users = &node;
	bee_state.ui = &ui_funcs;
	bee_state.ui_data = NULL;

	/* Attacker-controlled handle == the whole input file. A handle that is
	 * NOT (case-insensitively) "alice" makes bee_user_by_handle() return
	 * NULL, reproducing CVE-2016-10189 inside bee_irc_ft_in_start(). A
	 * handle that IS "alice" (any letter-case) resolves to the known
	 * bee_user_t and runs clean through the no-op dccs_send_start() stub. */
	file_transfer_t *ft = imcb_file_send_start(&conn, buf, "evil.txt", n);
	fprintf(stderr, "ft=%p handle_len=%zu\n", (void *)ft, n);

	free(buf);
	return 0;
}
