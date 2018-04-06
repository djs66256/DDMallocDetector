//
//  MallocStorage.hpp
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/28.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#ifndef MallocStorage_hpp
#define MallocStorage_hpp

#include <stdio.h>
#include <string>
#include <chrono>
#include <vector>
#include <mutex>
#include <strstream>
#include "Allocator.hpp"
#include "MallocMemory.hpp"
#include "MallocCollectorHelper.hpp"

namespace MD {
    
    template<class _Tp, class _Allocator = VMAllocator<_Tp> >
    class Storage {
    public:
        Storage(pthread_t pid) : pid_(pid), start_time_(std::chrono::system_clock::now()) {store_.reserve(128);}
        
        static void* operator new(std::size_t size) noexcept {
            std::size_t n = round_page(size);
            vm_address_t addr;
            vm_allocate(mach_task_self(), &addr, n, VM_FLAGS_ANYWHERE);
            return reinterpret_cast<void *>(addr);
        }
        
        static void operator delete(void *ptr, std::size_t size) noexcept {
            reinterpret_cast<Storage *>(ptr)->~Storage();
            std::size_t n = round_page(size);
            vm_deallocate(mach_task_self(), reinterpret_cast<vm_address_t>(ptr), n);
        }
        static void operator delete(void *ptr) noexcept {
            reinterpret_cast<Storage *>(ptr)->~Storage();
            std::size_t n = round_page(sizeof(Storage));
            vm_deallocate(mach_task_self(), reinterpret_cast<vm_address_t>(ptr), n);
        }
        
        void end() {
            end_time_ = std::chrono::system_clock::now();
        }
        
        std::size_t collect(_Tp&& item) {
            std::lock_guard<std::mutex> l(lock_);
            store_.emplace_back(std::move(item));
            return store_.size();
        }
        const std::vector<_Tp, _Allocator>& data() const {
            return store_;
        }
        
        void setMainThread() { main_thread_ = true; }
        void setName(char *name) {
            VMAllocator<char> allocator;
            name_ =  allocator.allocate(strlen(name) + 1);
            strcpy(name_, name);
        }
        std::string name() {
            std::string name;
            if (strlen(name_) == 0) {
                if (main_thread_) {
                    std::strstream s;
                    s << "Main(" << pid_ << ")";
                    s >> name;
                }
                else {
                    char buf[128] = {0};
                    int rc = pthread_getname_np(pid_, buf, sizeof(buf));
                    if (rc == 0 && strlen(buf) > 0) {
                        VMAllocator<char> allocator;
                        std::string thread_name(buf, allocator);
                        name = std::move(thread_name);
                    }
                    else {
                        std::strstream s;
                        s << "pid(" << pid_ << ")";
                        s >> name;
                    }
                }
            }
            return name;
        }
        
        void clear() {
            std::lock_guard<std::mutex> l(lock_);
            store_.clear();
        }
        
        ~Storage() {
            if (name_) {
                VMAllocator<char> allocator;
                allocator.deallocate(name_, strlen(name_) + 1);
                name_ = NULL;
            }
        }
        
    private:
        pthread_t pid_;
        bool main_thread_;
        char *name_;
        std::mutex lock_;
        std::vector<_Tp, _Allocator> store_;
        std::chrono::time_point<std::chrono::system_clock> start_time_;
        std::chrono::time_point<std::chrono::system_clock> end_time_;
        //            std::size_t min_index_ = 0;
        //            std::size_t max_index_ = 0;
        
        Storage(Storage<_Tp, _Allocator>&) = delete;
        Storage<_Tp, _Allocator>& operator = (Storage<_Tp, _Allocator>&) = delete;
    };
}

#endif /* MallocStorage_hpp */
