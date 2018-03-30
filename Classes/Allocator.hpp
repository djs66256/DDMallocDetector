//
//  Allocator.hpp
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/28.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#ifndef Allocator_hpp
#define Allocator_hpp

#include <stdio.h>
#include <new>
#include <memory>
#include <cassert>
#include <mach/mach.h>

namespace MD {
    
    template <class _Tp>
    class VMAllocator : public std::allocator<_Tp> {
    public:
        typedef typename std::allocator<_Tp>::pointer pointer;
        typedef typename std::allocator<_Tp>::size_type size_type;
        
        pointer allocate(size_type __n, std::allocator<void>::const_pointer = 0)
        {
            size_type n = round_page(__n * sizeof(_Tp));
            vm_address_t addr;
            kern_return_t rt = vm_allocate(mach_task_self(), &addr, n, VM_FLAGS_ANYWHERE);
            if (rt != KERN_SUCCESS) {
                throw std::bad_alloc();
            }
            vm_protect(mach_task_self(), addr, n, true, VM_PROT_READ|VM_PROT_WRITE);
            return reinterpret_cast<pointer>(addr);
        }
        void deallocate(pointer __p, size_type __n) noexcept
        {
            size_type n = round_page(__n);
            kern_return_t rt = vm_deallocate(mach_task_self(), reinterpret_cast<vm_address_t>(__p), n);
            if (rt != KERN_SUCCESS) {
                
            }
        }
    };
}

#endif /* Allocator_hpp */
