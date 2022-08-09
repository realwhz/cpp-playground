#pragma once

#include <new>

template<typename T>
class allocator {
public:
    allocator(size_t size): size_{size}
    {
        memory = static_cast<char *>(malloc(size_ * sizeof(T)));
        used = static_cast<bool *>(malloc(size_ * sizeof(bool)));
        for (auto i = 0; i < size_; ++i) {
            used[i] = false;
        }
    }

    ~allocator()
    {
        free(memory);
    }

    template<typename... Args>
    T* allocate(Args... args)
    {
        bool found = false;
        size_t i = 0;
        for (i = 0; i < size_; ++i) {
            if (!used[i]) {
                used[i] = true;
                found = true;
                break;
            }
        }

        if (!found)
            return nullptr;

        T *ptr = reinterpret_cast<T*>(&memory[i * sizeof(T)]);
        return new (ptr) T{args...};
    }

    void deallocate(T *p)
    {
        if (!p)
            return;

        p->~T();
        for (auto i = 0; i < size_; ++i) {
            if (reinterpret_cast<T*>(&memory[i * sizeof(T)]) == p)
                used[i] = false;
        }
    }

private:
    size_t size_;
    alignas(T*) char *memory;
    bool *used;
};
