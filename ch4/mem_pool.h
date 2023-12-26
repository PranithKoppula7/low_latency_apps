#include <cstddef>
#include <stdexcept>
#include <vector>

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
    if (obj_block->is_free) {
      T* ret = &(obj_block->obj);
      ret = new(ret) T(args...);
      updateNextFreeIndex();
      return ret;
    }
  }

  auto deallocate(const T* elem) noexcept {
   const auto elem_index = (reinterpret_cast<const ObjectBlock*>(elem - &store_[0]));

  }

private:
  auto updateNextFreeIndex() noexcept {
    const auto inital_free_index = next_free_index_;
    while (!store_[next_free_index_].is_free) {
      ++next_free_index_;
      if (inital_free_index == next_free_index_) {
        throw std::out_of_range("out of space");
      }
    }
  }

  struct ObjectBlock {
    T obj;
    bool is_free;
  };

  std::vector<ObjectBlock> store_;

  std::size_t next_free_index_ = 0;
};
