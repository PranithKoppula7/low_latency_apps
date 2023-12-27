cc_library(
  name = "macros",
  hdrs = ["macros.h"],
  includes = ["./"],
)

cc_library(
  name = "mem_pool",
  hdrs = ["mem_pool.h"],
  includes = ["./"],
  deps = [
    ":macros",
  ],
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
