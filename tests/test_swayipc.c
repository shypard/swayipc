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
    enum event_type events[] = {SWAY_EVENT_MODE, SWAY_EVENT_INPUT,
                                SWAY_EVENT_WORKSPACE};
    assert_int_equal(swayipc_init(), 0);
    assert_int_equal(swayipc_subscribe(events, 3), 0);
    assert_int_equal(swayipc_shutdown(), 0);
}

event_s* create_sample_event(enum event_type type, void* data, size_t size)
{
    event_s* event = malloc(sizeof(event_s));
    event->type    = type;
    event->data    = data;
    event->size    = size;
    return event;
}

static void test_event_queue_init(void** state)
{
    event_queue_s* queue = event_queue_init();

    assert_non_null(queue);
    assert_int_equal(queue->head, 0);
    assert_int_equal(queue->tail, 0);
    assert_int_equal(queue->size, 0);
    assert_int_equal(event_queue_destroy(queue), 0);
}

static void test_event_queue_push(void** state)
{
    event_queue_s* queue        = event_queue_init();
    event_s*       sample_event = create_sample_event(SWAY_EVENT_MODE, NULL, 0);
    assert_int_equal(event_queue_push(queue, sample_event), 0);

    assert_int_equal(queue->head, 0);
    assert_int_equal(queue->tail, 1);
    assert_int_equal(queue->size, 1);
    assert_int_equal(event_queue_destroy(queue), 0);
}

static void test_event_queue_pop(void** state)
{
    event_queue_s* queue        = event_queue_init();
    event_s*       sample_event = create_sample_event(SWAY_EVENT_MODE, NULL, 0);

    // add new event to queue
    assert_int_equal(event_queue_push(queue, sample_event), 0);
    assert_int_equal(queue->size, 1);

    // get last event from event_queue
    event_s* popped_event = event_queue_pop(queue);

    assert_int_equal(popped_event->type, SWAY_EVENT_MODE);
    assert_int_equal(queue->size, 0);

    assert_int_equal(event_queue_destroy(queue), 0);
}

static void test_event_queue_is_empty(void** state)
{
    event_queue_s* queue = event_queue_init();

    assert_true(event_queue_is_empty(queue));

    event_s* sample_event = create_sample_event(SWAY_EVENT_MODE, NULL, 0);
    event_queue_push(queue, sample_event);
    assert_false(event_queue_is_empty(queue));

    assert_int_equal(event_queue_destroy(queue), 0);
}

static void test_event_queue_is_full(void** state)
{
    event_queue_s* queue = event_queue_init();

    assert_false(event_queue_is_full(queue));

    for (int i = 0; i < EVENT_QUEUE_SIZE; ++i) {
        event_s* sample_event = create_sample_event(SWAY_EVENT_MODE, NULL, 0);
        event_queue_push(queue, sample_event);
    }

    assert_true(event_queue_is_full(queue));
    assert_int_equal(event_queue_destroy(queue), 0);
}

static void test_event_queue_destroy(void** state)
{
    event_queue_s* queue        = event_queue_init();
    event_s*       sample_event = create_sample_event(SWAY_EVENT_MODE, NULL, 0);
    event_queue_push(queue, sample_event);

    assert_int_equal(event_queue_destroy(queue), 0);
}

static void test_swayipc_get_event(void** state)
{
    event_s*       sample_event = create_sample_event(SWAY_EVENT_MODE, NULL, 0);
    event_queue_s* queue        = event_queue_init();

    // add new event to queue
    assert_int_equal(event_queue_push(queue, sample_event), 0);

    // get last event from event_queue
    event_s* event = swayipc_get_event();
    assert_non_null(event);
    assert_int_equal(event->type, SWAY_EVENT_MODE);
    assert_int_equal(swayipc_shutdown(), 0);
}

int main(void)
{
    const struct CMUnitTest swayipc_tests[] = {
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
        cmocka_unit_test(test_swayipc_get_event),
    };

    const struct CMUnitTest event_queue_tests[] = {
        cmocka_unit_test(test_event_queue_init),
        cmocka_unit_test(test_event_queue_push),
        cmocka_unit_test(test_event_queue_pop),
        cmocka_unit_test(test_event_queue_is_empty),
        cmocka_unit_test(test_event_queue_is_full),
        cmocka_unit_test(test_event_queue_destroy),
    };

    return cmocka_run_group_tests(swayipc_tests, NULL, NULL) ||
           cmocka_run_group_tests(event_queue_tests, NULL, NULL);
}
