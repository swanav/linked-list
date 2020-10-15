add_executable(test_linked_list test_linked_list.cpp)
target_link_libraries(test_linked_list LinkedList gtest_main)

# ====================== TEST CASES ====================
include(GoogleTest)
gtest_discover_tests(test_linked_list TEST_PREFIX LinkedList:)
# ---------------------- TEST CASES --------------------
