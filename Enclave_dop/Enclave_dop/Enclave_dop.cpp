#include "Enclave_dop_t.h"

#include "sgx_trts.h"
#include <string.h>
#include "sgx_tseal.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

char encrypt_data[6][41] = {
    "7eb5ecd8ce73ae063e7ae783c54eac15748667a7",
    "1c25628f790fd2258821bfe33d6284e8cacf445e",
    "f4bace63c61af4dc9e1e3c1b6a4271f3bf2c7b25",
    "ff018ffa70d2deccc38483d5cacc41d7321088f6",
    "318e469cfb3582c4f6d280ff09654201bd218e85"
};

/*int plaintext_len = 41;
uint32_t ciph_size = sgx_calc_sealed_data_size(0, plaintext_len);
uint8_t* sealed_for_un = (uint8_t*)malloc(ciph_size);*/

/*uint32_t get_sealed_data_size(size_t idx)
{
    return sgx_calc_sealed_data_size(0, (uint32_t)strlen(encrypt_data[idx]));
}*/

void seal(char* buf, size_t len, size_t idx, int flag)
{
    int plaintext_len = 41;
    sgx_status_t res;
    uint8_t* plaintext = (uint8_t*)encrypt_data[idx];
    // Do something in plaintext memory space.

    // Allocate space for sealing
    uint32_t ciph_size = sgx_calc_sealed_data_size(0, plaintext_len);
    uint8_t* sealed = (uint8_t*)malloc(ciph_size);
    uint32_t plain_size = plaintext_len;

    // Seal and unseal the data
    res = sgx_seal_data(0, NULL, plaintext_len, plaintext, ciph_size, (sgx_sealed_data_t*)sealed);
    if (res != SGX_SUCCESS) {
        memcpy(buf, "Data Sealing Error", strlen("Data Sealing Error"));
        return;
    };
    //sealed_for_un = sealed;
    //memcpy(buf, "Data Sealing", strlen("Data Sealing"));
    //return;
    uint8_t* plaintext2 = (uint8_t*)malloc(plain_size);
    if (flag == 1) {
        res = sgx_unseal_data((sgx_sealed_data_t*)sealed, NULL, NULL, plaintext2, &plain_size);

        if (res != SGX_SUCCESS) {
            memcpy(buf, "Data UNSealing Error", strlen("Data UNSealing Error"));
            return;
        };
        memcpy(buf, plaintext2, plain_size);
        return;
    }
    else {
        memcpy(buf, "Data Sealing", strlen("Data Sealing"));
    }

}

/*void unseal(char* buf, size_t len, size_t idx)
{
    //int plaintext_len = 41;
    sgx_status_t res;
    uint8_t* plaintext = (uint8_t*)encrypt_data[idx];
    // Do something in plaintext memory space.

    // Allocate space for sealing
    //uint32_t ciph_size = sgx_calc_sealed_data_size(0, plaintext_len);
    //uint8_t* sealed = (uint8_t*)malloc(ciph_size);
    uint32_t plain_size = plaintext_len;

    res = sgx_unseal_data((sgx_sealed_data_t*)::sealed_for_un, NULL, NULL, plaintext, &plain_size);
    if (res != SGX_SUCCESS) {
        memcpy(buf, "Data UNSealing Error", strlen("Data UNSealing Error"));
        return;
    };
    memcpy(buf, plaintext, plain_size);
    return;
}

char unseal2(uint8_t* sealed, size_t idx)
{
    //int plaintext_len = 41;
    sgx_status_t res;
    uint8_t* plaintext = (uint8_t*)encrypt_data[idx];
    // Do something in plaintext memory space.

    // Allocate space for sealing
    //uint32_t ciph_size = sgx_calc_sealed_data_size(0, plaintext_len);
    //uint8_t* sealed = (uint8_t*)malloc(ciph_size);
    uint32_t plain_size = plaintext_len;

    res = sgx_unseal_data((sgx_sealed_data_t*)sealed, NULL, NULL, plaintext, &plain_size);
    if (res != SGX_SUCCESS) {
        //memcpy(buf, "Data UNSealing Error", strlen("Data UNSealing Error"));
        return;
    };
    //memcpy(buf, plaintext, plain_size);
    return (char)plaintext;
}*/