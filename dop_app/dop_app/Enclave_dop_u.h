#ifndef ENCLAVE_DOP_U_H__
#define ENCLAVE_DOP_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_status_t etc. */


#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif


sgx_status_t seal(sgx_enclave_id_t eid, char* buf, size_t len, size_t idx, int flag);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
