#include <cstddef>
#include <deque>
#include <iostream>
#include <vector>

#include "macros.h"

/*
 * Creates a pool(list) of allocated memory of given type T
*/
template<typename T>
class MemPool {
public:
  explicit MemPool(std::size_t size)
    :store_(size, {T(), true}) {}

  template<typename... Args>
  T* allocate(Args... args) noexcept {
    auto obj_block = &(store_[next_free_index_]);
    ASSERT(obj_block->is_free, "allocate- expected free block at index: " + std::to_string(next_free_index_));
    T* ret = &(obj_block->obj);
    ret = new(ret) T(args...);
    obj_block->is_free = false;
    updateNextFreeIndex();
    return ret;
  }

  auto deallocate(const T* elem) noexcept {
    const auto elem_index = (reinterpret_cast<const ObjectBlock*>(elem) - &store_[0]);
    ASSERT(elem_index >= 0 && static_cast<std::size_t>(elem_index) < store_.size(), "Element is not in memory pool");
    ASSERT(!store_[elem_index].is_free, "deallocate- expected free block at index: " + std::to_string(elem_index));
    store_[elem_index].is_free = true;
  }

private:
  auto updateNextFreeIndex() noexcept {
    const auto initial_free_index = next_free_index_;
    for (auto i = 0; i < initial_free_index; i++) {
      if (UNLIKELY(store_[i].is_free)) {
        next_free_index_ = i;
        return;
      }
    }

    for (auto i = initial_free_index; i < store_.size(); i++) {
      if (UNLIKELY(store_[i].is_free)) {
        next_free_index_ = i;
        return;
      }
    }

    store_.push_back({T(), true});
    next_free_index_ = store_.size() - 1;
    return;
  }

  struct ObjectBlock {
    T obj;
    bool is_free;
  };

  std::deque<ObjectBlock> store_;

  std::size_t next_free_index_ = 0;
};
