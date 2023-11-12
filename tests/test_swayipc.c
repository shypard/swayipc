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

static void test_swayipc_get_workspaces(void **state){
    char data[256];
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_workspaces(data), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_get_tree(void **state){
    char data[256];
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_tree(data), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_get_bar_config(void **state){
    char data[256];
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_bar_config(data), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_get_binding_modes(void **state){
    char data[256];
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_binding_modes(data), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_get_config(void **state){
    char data[256];
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_config(data), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_get_inputs(void **state){
    char data[256];
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_inputs(data), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_get_marks(void **state){
    char data[256];
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_marks(data), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_get_seats(void **state){
    char data[256];
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_seats(data), 0);
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
