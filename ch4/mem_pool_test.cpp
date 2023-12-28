#include <gtest/gtest.h>
#include <vector>

#include "mem_pool.h"

template class MemPool<int>;

TEST(mem_pool, general_test) {
  MemPool<int> mem_pool = MemPool<int>(3);
  auto ret = mem_pool.allocate(1);
  EXPECT_EQ(*ret, 1);
  mem_pool.deallocate(ret);
}

TEST(mem_pool, full_memory_test) {
  MemPool<int> mem_pool = MemPool<int>(6);
  std::vector<int*> alloc_list;

  for (auto i = 0; i < 6; ++i) {
    auto ret = mem_pool.allocate(i);
    EXPECT_EQ(*ret, i);
    alloc_list.push_back(ret);
  }

  for (auto i = 0; i < 6; ++i) {
    mem_pool.deallocate(alloc_list[i]);
  }
}

TEST(mem_pool, one_less_than_full_test) {
  MemPool<int> mem_pool = MemPool<int>(6);
  std::vector<int*> alloc_list;

  for (auto i = 0; i < 5; ++i) {
    auto ret = mem_pool.allocate(i);
    EXPECT_EQ(*ret, i);
    alloc_list.push_back(ret);
  }

  for (auto i = 0; i < 5; ++i) {
    mem_pool.deallocate(alloc_list[i]);
  }
}

TEST(mem_pool, extra_memory_test) {
  MemPool<int> mem_pool = MemPool<int>(6);
  std::vector<int*> alloc_list;

  for (auto i = 0; i < 7; ++i) {
    auto ret = mem_pool.allocate(i);
    EXPECT_EQ(*ret, i);
    alloc_list.push_back(ret);
  }

  for (auto i = 0; i < 7; ++i) {
    mem_pool.deallocate(alloc_list[i]);
  }
}
