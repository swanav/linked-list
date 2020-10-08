add_executable(test_linked_list test_linked_list.c)
target_link_libraries(test_linked_list LinkedList)

# ====================== TEST CASES ====================
add_test(NAME test_linked_list COMMAND test_linked_list)
# ---------------------- TEST CASES --------------------
