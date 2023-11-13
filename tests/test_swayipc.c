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

#define LEN 2048
char data[LEN];

static void test_swayipc_get_version(void **state) {
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_version(data, LEN), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_get_outputs(void **state) {
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_outputs(data, LEN), 0);
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

static void test_swayipc_get_workspaces(void **state){
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_workspaces(data, LEN), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_get_tree(void **state){
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_tree(data, LEN), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_get_bar_config(void **state){
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_bar_config(data, LEN), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_get_binding_modes(void **state){
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_binding_modes(data, LEN), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_get_config(void **state){
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_config(data, LEN), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_get_inputs(void **state){
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_inputs(data, LEN), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_get_marks(void **state){
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_marks(data, LEN), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_get_seats(void **state){
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_seats(data, LEN), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

int main(void){
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_swayipc_open),
        cmocka_unit_test(test_swayipc_close),
        cmocka_unit_test(test_swayipc_get_version),
        cmocka_unit_test(test_swayipc_get_outputs),
        cmocka_unit_test(test_swayipc_get_workspaces),
        cmocka_unit_test(test_swayipc_get_tree),
        cmocka_unit_test(test_swayipc_get_bar_config),
        cmocka_unit_test(test_swayipc_get_binding_modes),
        cmocka_unit_test(test_swayipc_get_config),
        cmocka_unit_test(test_swayipc_get_inputs),
        cmocka_unit_test(test_swayipc_get_marks),
        cmocka_unit_test(test_swayipc_get_seats),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
