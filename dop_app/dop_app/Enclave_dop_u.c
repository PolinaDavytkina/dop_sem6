#include "Enclave_dop_u.h"
#include <errno.h>

typedef struct ms_seal_t {
	char* ms_buf;
	size_t ms_len;
	size_t ms_idx;
	int ms_flag;
} ms_seal_t;

static const struct {
	size_t nr_ocall;
	void * func_addr[1];
} ocall_table_Enclave_dop = {
	0,
	{ NULL },
};

sgx_status_t seal(sgx_enclave_id_t eid, char* buf, size_t len, size_t idx, int flag)
{
	sgx_status_t status;
	ms_seal_t ms;
	ms.ms_buf = buf;
	ms.ms_len = len;
	ms.ms_idx = idx;
	ms.ms_flag = flag;
	status = sgx_ecall(eid, 0, &ocall_table_Enclave_dop, &ms);
	return status;
}

