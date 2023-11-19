#include "events.h"
#include "swayipc.h"

// clang-format off
// clang-format sorts the includes in alphabetical order, however setjmp.h must
// be included before cmocka.h
#include <errno.h>
#include <fcntl.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cmocka.h>
// clang-format on

#define LEN 2048
char data[LEN];

static void test_swayipc_get_version(void** state)
{
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_version(data, LEN), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_get_outputs(void** state)
{
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_outputs(data, LEN), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_close(void** state)
{
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_open(void** state)
{
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_get_workspaces(void** state)
{
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_workspaces(data, LEN), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_get_tree(void** state)
{
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_tree(data, LEN), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_get_bar_config(void** state)
{
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_bar_config(data, LEN), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_get_binding_modes(void** state)
{
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_binding_modes(data, LEN), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_get_config(void** state)
{
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_config(data, LEN), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_get_inputs(void** state)
{
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_inputs(data, LEN), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_get_marks(void** state)
{
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_marks(data, LEN), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_get_seats(void** state)
{
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_get_seats(data, LEN), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_swayipc_subscribe(void** state)
{
    enum event_type events[] = {SWAY_EVENT_WORKSPACE, SWAY_EVENT_INPUT,
                                SWAY_EVENT_MODE};
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_subscribe(events, 3), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

static void test_event_queue_init(void** state)
{
    event_queue_s* queue = event_queue_init();

    assert_non_null(queue);
    assert_int_equal(queue->head, 0);
    assert_int_equal(queue->tail, 0);
    assert_int_equal(queue->size, 0);

    event_queue_destroy(queue);
}

static void test_event_queue_push(void** state)
{
    event_queue_s* queue = event_queue_init();
    assert_int_equal(event_queue_push(queue, SWAY_EVENT_WINDOW), 0);

    assert_int_equal(queue->head, 0);
    assert_int_equal(queue->tail, 1);
    assert_int_equal(queue->size, 1);

    event_queue_destroy(queue);
}

static void test_event_queue_pop(void** state)
{
    event_queue_s*  queue = event_queue_init();
    enum event_type event;

    event_queue_push(queue, SWAY_EVENT_WINDOW);
    assert_int_equal(event_queue_pop(queue, &event), 0);
    assert_int_equal(event, SWAY_EVENT_WINDOW);
    assert_int_equal(queue->size, 0);

    event_queue_destroy(queue);
}

static void test_event_queue_is_empty(void** state)
{
    event_queue_s* queue = event_queue_init();
    assert_true(event_queue_is_empty(queue));

    event_queue_push(queue, SWAY_EVENT_WINDOW);
    assert_false(event_queue_is_empty(queue));

    event_queue_destroy(queue);
}

static void test_event_queue_is_full(void** state)
{
    event_queue_s* queue = event_queue_init();
    assert_false(event_queue_is_full(queue));

    for (int i = 0; i < EVENT_QUEUE_SIZE; ++i) {
        event_queue_push(queue, SWAY_EVENT_WINDOW);
    }

    assert_true(event_queue_is_full(queue));
    event_queue_destroy(queue);
}

int main(void)
{
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
        cmocka_unit_test(test_swayipc_subscribe),
        cmocka_unit_test(test_event_queue_init),
        cmocka_unit_test(test_event_queue_push),
        cmocka_unit_test(test_event_queue_pop),
        cmocka_unit_test(test_event_queue_is_empty),
        cmocka_unit_test(test_event_queue_is_full),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
