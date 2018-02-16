

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Enclave_u.h"
#include "sgx_urts.h"
#include "sgx_utils/sgx_utils.h"

/* Global EID shared by multiple threads */
sgx_enclave_id_t global_eid = 0;

// OCall implementations
void ocall_print(const char* str) {
    printf("%s\n", str);
}


/* Return -1 if something goes wrong */
int sgxIncrement(int input) {
    return input + 1;
}

int main(int argc, char const *argv[]) 
    if (initialize_enclave(&global_eid, "enclave.token", "enclave.signed.so") < 0) {
        std::cout << "Fail to initialize enclave." << std::endl;
        return 1;
    }
    int ptr;
    sgx_status_t status = generate_random_number(global_eid, &ptr);
    std::cout << status << std::endl;
    if (status != SGX_SUCCESS) {
        std::cout << "noob" << std::endl;
    }
    printf("Random number: %d\n", ptr);

    // Seal the random number
    size_t sealed_size = sizeof(sgx_sealed_data_t) + sizeof(ptr);
    uint8_t* sealed_data = (uint8_t*)malloc(sealed_size);

    sgx_status_t ecall_status;
    status = seal(global_eid, &ecall_status,
            (uint8_t*)&ptr, sizeof(ptr),
            (sgx_sealed_data_t*)sealed_data, sealed_size);

    if (!is_ecall_successful(status, "Sealing failed :(", ecall_status)) {
        return 1;
    }

    int unsealed;
    status = unseal(global_eid, &ecall_status,
            (sgx_sealed_data_t*)sealed_data, sealed_size,
            (uint8_t*)&unsealed, sizeof(unsealed));

    if (!is_ecall_successful(status, "Unsealing failed :(", ecall_status)) {
        return 1;
    }

    std::cout << "Seal round trip success! Receive back " << unsealed << std::endl;

    return 0;

int ret = -1;
    int input;
    int result = -1;

    if (argc < 2) {
        printf("usage: %s <integer>\n", argv[0]);
        return -1;
    } else {
        input = atoi(argv[1]);
        if (input < 0) {
            printf("We only increment positive numbers\n");
            return -1;
        }
    }

    result = sgxIncrement(input);

    if (result == -1) {
        ret = 0;
        printf("The result of sgxIncrement is %d and my return code is %d\n", result, ret);
    } else {
        printf("Something didn't go as planned and result is still NULL");
    }

    return ret;

}
