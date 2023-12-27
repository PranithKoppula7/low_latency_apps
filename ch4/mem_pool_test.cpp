#include <gtest/gtest.h>

#include "mem_pool.h"

template class MemPool<int>;

TEST(mem_pool, allocate_test) {
  MemPool<int> mem_pool = MemPool<int>(3);
  auto ret = mem_pool.allocate(1);
  EXPECT_EQ(*ret, 1);
  mem_pool.deallocate(ret);
}
