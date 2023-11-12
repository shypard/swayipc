#include "swayipc.h"

#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static void test_swayipc_get_version(void **state) {
    char data[256];
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_version(data), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_get_outputs(void **state) {
    char data[256];
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_outputs(data), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_close(void **state){
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_open(void **state){
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

int main(void){
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_swayipc_open),
        cmocka_unit_test(test_swayipc_close),
        cmocka_unit_test(test_swayipc_get_version),
        cmocka_unit_test(test_swayipc_get_outputs),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
