#ifndef SHARED_POINTERS_HPP
#define SHARED_POINTERS_HPP

#include <memory>

template <typename T> using sptr = std::shared_ptr<T>;
#define MKSH(T) std::make_shared<T>
#define CAST(T) std::dynamic_pointer_cast<T>

#endif
