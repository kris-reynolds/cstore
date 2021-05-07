#include "cstore/vector.h"
#include "unity.h"
#include <stdlib.h>

typedef struct foo_t {
    int bar;
} foo;

CREATE_VECTOR_FUNCS(foo);
CREATE_VECTOR_FUNCS(uint32_t);

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}


void initialize_a_vector(void) {
    // Arrange
    vector v = new_heap_vector(sizeof(foo));

    // Assert
    TEST_ASSERT_TRUE(v.resource != NULL);
    TEST_ASSERT_EQUAL_UINT32(v.element_size, sizeof(foo));
    TEST_ASSERT_EQUAL_UINT32(v.capacity, 10);
    TEST_ASSERT_EQUAL_UINT32(v.size, 0);
    TEST_ASSERT_TRUE(v.internal_memory);

    // Capacity checks at initialization
    TEST_ASSERT_TRUE(vector_empty(&v));
    TEST_ASSERT_EQUAL_UINT32(vector_capacity(&v), 10);

    vector_delete(&v);
}


void access_data_in_empty_vector() {
    // Arrange
    vector v = new_heap_vector_foo();

    // Act
    foo* at1 = vector_at_foo(&v, 1);
    foo* front = vector_front_foo(&v);
    foo* back = vector_back_foo(&v);

    // Assert
    TEST_ASSERT_FALSE(at1);
    TEST_ASSERT_FALSE(front);
    TEST_ASSERT_FALSE(back);
    vector_delete(&v);
}


void add_elements_to_vector() {
    // Arrange
    vector v = new_heap_vector_foo();

    // Act
    for(int i = 0; i < 10; ++i) {
        foo f = { .bar = i };
        vector_push_back(&v, &f);
    }

    // Assert
    TEST_ASSERT_EQUAL_UINT32(v.size, 10);
    TEST_ASSERT_EQUAL_UINT32(v.capacity, 10);

    for(int i = 0; i < 10; ++i) {
        foo* f = vector_at(&v, i);
        TEST_ASSERT_EQUAL(f->bar, i);
    }

    vector_delete(&v);
}

void add_elements_to_vector_populate_return() {
    // Arrange
    vector v = new_heap_vector_foo();

    // Act
    for(int i = 0; i < 10; ++i) {
        foo* f = vector_push_back(&v, NULL);
        f->bar = i;
    }

    // Assert
    TEST_ASSERT_EQUAL_UINT32(v.size, 10);
    TEST_ASSERT_EQUAL_UINT32(v.capacity, 10);

    for(int i = 0; i < 10; ++i) {
        foo* f = vector_at(&v, i);
        TEST_ASSERT_EQUAL(f->bar, i);
    }
    vector_delete(&v);
}

void vector_resizes_when_needed() {
    // Arrange
    vector v = new_heap_vector_foo();

    // Act
    for(int i = 0; i < 11; ++i) {
        foo f = { .bar = i };
        vector_push_back(&v, &f);
    }

    // Assert
    TEST_ASSERT_EQUAL_UINT32(11, v.size);
    TEST_ASSERT_EQUAL_UINT32(20, v.capacity);
    TEST_ASSERT_EQUAL_UINT32(0, vector_front_foo(&v)->bar);
    TEST_ASSERT_EQUAL_UINT32(10, vector_back_foo(&v)->bar);

    for(int i = 0; i < 11; ++i) {
        foo* f = vector_at(&v, i);
        TEST_ASSERT_EQUAL(f->bar, i);
    }

    vector_delete(&v);
}


// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(initialize_a_vector);
    RUN_TEST(access_data_in_empty_vector);
    RUN_TEST(add_elements_to_vector);
    RUN_TEST(add_elements_to_vector_populate_return);
    RUN_TEST(vector_resizes_when_needed);
    return UNITY_END();
}
