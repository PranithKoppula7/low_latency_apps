cc_library(
  name = "mem_pool",
  hdrs = ["mem_pool.h"],
  includes = ["./"],
)

cc_test(
  name = "mem_pool_test",
  size = "small",
  srcs = ["mem_pool_test.cpp"],
  deps = [
    ":mem_pool",
    "@com_google_googletest//:gtest_main"
  ]
)
