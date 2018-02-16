#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "sgx_urts.h"
#include "sgx_utils.h"



/* Return -1 if something goes wrong */
int sgxIncrement(int input) {
    return input + 1;
}

int main(int argc, char *argv[]) {
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
