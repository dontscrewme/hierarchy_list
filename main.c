#include "hierarchy_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_set_parent_valid() {
  LIST_HEAD(parent_head);
  struct parent *p = set_parent(&parent_head, "key1", "value1");
  assert(p != NULL);
  assert(strcmp(p->key, "key1") == 0);
  assert(strcmp(p->value, "value1") == 0);
  unset_parents(&parent_head); // Clean up memory
}

void test_set_parent_null_key() {
  LIST_HEAD(parent_head);
  struct parent *p = set_parent(&parent_head, NULL, "value1");
  assert(p == NULL);
}

void test_set_parent_null_value() {
  LIST_HEAD(parent_head);
  struct parent *p = set_parent(&parent_head, "key1", NULL);
  assert(p == NULL);
}

void test_find_parent() {
  LIST_HEAD(parent_head);
  set_parent(&parent_head, "key1", "value1");
  struct parent *p = find_parent(&parent_head, "key1", "value1");
  assert(p != NULL);
  unset_parents(&parent_head); // Clean up memory
}

void test_find_nonexisting_parent() {
  LIST_HEAD(parent_head);
  struct parent *p = find_parent(&parent_head, "nonexistent_key", "value");
  assert(p == NULL);
}

void test_set_child_valid() {
  LIST_HEAD(parent_head);
  struct parent *p = set_parent(&parent_head, "key1", "value1");
  struct child *c = set_child(p, "key2", "value2");
  assert(c != NULL);
  assert(strcmp(c->key, "key2") == 0);
  assert(strcmp(c->value, "value2") == 0);
  unset_parents(&parent_head); // Clean up memory
}

void test_set_child_null_key() {
  LIST_HEAD(parent_head);
  struct parent *p = set_parent(&parent_head, "key1", "value1");
  struct child *c = set_child(p, NULL, "value2");
  assert(c == NULL);
  unset_parents(&parent_head); // Clean up memory
}

void test_set_child_null_value() {
  LIST_HEAD(parent_head);
  struct parent *p = set_parent(&parent_head, "key1", "value1");
  struct child *c = set_child(p, "key2", NULL);
  assert(c == NULL);
  unset_parents(&parent_head); // Clean up memory
}

void test_find_child() {
  LIST_HEAD(parent_head);
  struct parent *p = set_parent(&parent_head, "key1", "value1");
  set_child(p, "key2", "value2");
  struct child *c = find_child(p, "key2", "value2");
  assert(c != NULL);
  unset_parents(&parent_head); // Clean up memory
}

void test_find_nonexisting_child() {
  LIST_HEAD(parent_head);
  struct parent *p = set_parent(&parent_head, "key1", "value1");
  struct child *c = find_child(p, "nonexistent_key", "value");
  assert(c == NULL);
  unset_parents(&parent_head); // Clean up memory
}

void test_num_of_children() {
  LIST_HEAD(parent_head);
  struct parent *p = set_parent(&parent_head, "key1", "value1");
  set_child(p, "key2", "value2");
  set_child(p, "key3", "value3");
  unsigned int count;
  int result = getNumOfChildren(p, &count);
  assert(result == 0);
  assert(count == 2);
  unset_parents(&parent_head); // Clean up memory
}

void test_unset_parent() {
  LIST_HEAD(parent_head);
  set_parent(&parent_head, "key1", "value1");
  set_parent(&parent_head, "key2", "value2");

  // Unset "key1" parent (tail)
  unset_parent(&parent_head, "key1", "value1");

  // Verify "key1" parent is removed and "key2" remains
  struct parent *p1 = find_parent(&parent_head, "key1", "value1");
  struct parent *p2 = find_parent(&parent_head, "key2", "value2");

  assert(p1 == NULL);
  assert(p2 != NULL);

  unset_parents(&parent_head); // Clean up memory

  set_parent(&parent_head, "key1", "value1");
  set_parent(&parent_head, "key2", "value2");

  // Unset "key2" parent (head)
  unset_parent(&parent_head, "key2", "value2");

  p1 = find_parent(&parent_head, "key1", "value1");
  p2 = find_parent(&parent_head, "key2", "value2");

  assert(p1 != NULL);
  assert(p2 == NULL);

  unset_parents(&parent_head); // Clean up memory
}

void test_unset_child() {
  LIST_HEAD(parent_head);
  struct parent *p = set_parent(&parent_head, "key1", "value1");
  set_child(p, "key2", "value2");
  unset_child(p, "key2", "value2");
  struct child *c = find_child(p, "key2", "value2");
  assert(c == NULL);
  unset_parents(&parent_head); // Clean up memory
}

void test_unset_nonexisting_parent() {
    LIST_HEAD(parent_head);
    set_parent(&parent_head, "key1", "value1");

    // Attempt to unset a non-existing parent
    unset_parent(&parent_head, "nonexistent_key", "nonexistent_value");

    // Verify "key1" parent still exists
    struct parent *p = find_parent(&parent_head, "key1", "value1");
    assert(p != NULL);

    unset_parents(&parent_head);  // Clean up memory
}

void test_unset_nonexisting_child() {
    LIST_HEAD(parent_head);
    struct parent *p = set_parent(&parent_head, "key1", "value1");
    set_child(p, "key2", "value2");

    // Attempt to unset a non-existing child
    unset_child(p, "nonexistent_key", "nonexistent_value");

    // Verify existing child still exists
    struct child *c = find_child(p, "key2", "value2");
    assert(c != NULL);

    unset_parents(&parent_head);  // Clean up memory
}

void test_unset_parents_and_children() {
  LIST_HEAD(parent_head);
  struct parent *p = set_parent(&parent_head, "key1", "value1");
  set_child(p, "key2", "value2");
  unset_parents(&parent_head);
  assert(list_empty(&parent_head));
}

void test_print_parent() {
  LIST_HEAD(parent_head);
  set_parent(&parent_head, "key1", "value1");
  print_parents(&parent_head);
  unset_parents(&parent_head); // Clean up memory
}

void test_print_parents() {
  LIST_HEAD(parent_head);
  set_parent(&parent_head, "key1", "value1");
  set_parent(&parent_head, "key2", "value2");
  print_parents(&parent_head);
  unset_parents(&parent_head); // Clean up memory
}

void test_print_child() {
  LIST_HEAD(parent_head);
  struct parent *p = set_parent(&parent_head, "key1", "value1");
  set_child(p, "key2", "value2");
  print_children(p);
  unset_parents(&parent_head); // Clean up memory
}

void test_print_children() {
  LIST_HEAD(parent_head);
  struct parent *p = set_parent(&parent_head, "key1", "value1");
  set_child(p, "key2", "value2");
  set_child(p, "key3", "value3");
  print_children(p);
  unset_parents(&parent_head); // Clean up memory
}

void test_print_all() {
    LIST_HEAD(parent_head);
    struct parent *p1 = set_parent(&parent_head, "p1", "v1");
    struct parent *p2 = set_parent(&parent_head, "p2", "p2");
    set_child(p1, "child1", "child_value1");
    set_child(p2, "child2", "child_value2");

    // Print all parents and children
    print_all(&parent_head);

    unset_parents(&parent_head);  // Clean up memory
}


int main() {
  test_set_parent_valid();
  test_set_parent_null_key();
  test_set_parent_null_value();

  test_find_parent();
  test_find_nonexisting_parent();

  test_set_child_valid();
  test_set_child_null_key();
  test_set_child_null_value();

  test_find_child();
  test_find_nonexisting_child();

  test_num_of_children();

  test_unset_parent();
  test_unset_child();
  test_unset_nonexisting_parent();
  test_unset_nonexisting_child();
  test_unset_parents_and_children();
  
  test_print_parent();
  test_print_parents();
  test_print_child();
  test_print_children();
  test_print_all();

  printf("All tests passed successfully.\n");
  return 0;
}
