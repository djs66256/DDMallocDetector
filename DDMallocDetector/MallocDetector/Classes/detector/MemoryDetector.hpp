//
//  MemoryDetector.hpp
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/27.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#ifndef MemoryDetector_hpp
#define MemoryDetector_hpp

#include <stdio.h>
#include <mutex>
#include <atomic>
#include "MallocPool.hpp"
#include "MallocWrapZone.hpp"

namespace MD {
    class MemoryDetector {
    public:
        class Observer {
        public:
            virtual void OnDataOverflow() = 0;
        };
        class ProtectException : public std::exception {
        public:
            const char* what() const noexcept override {
                return "Detector is running in protect mode now!";
            }
        };
        
        static MemoryDetector *GetInstance();
        
        static constexpr int64_t MAX_DATA_COUNT = 1024 * 1024 * 10;
        
        MemoryDetector();
        
        // Editting malloc_zones is not thread safe, must done at program start!
        void DetectorAllZones() noexcept;
        void DetectorDefaultZone() noexcept;
        
        void Start() { setEnabled(true); }
        void Stop() { setEnabled(false); }
        bool Running() { return isEnabled(); }
        
        MallocPool& pool() noexcept {
            return pool_;
        }
        
        MallocWrapZones& wrap_zones() noexcept {
            return wrap_zones_;
        }
        
        void AddSyscallCount() {
            if (isEnabled()) {
                syscall_count_.fetch_add(1, std::memory_order_relaxed);
            }
        }
        
        int64_t syscall_count() {
            return syscall_count_.load();
        }
        
        void ClearPool() {
            if (!Running()) {
                pool_.ClearAll();
            }
            else {
                throw ProtectException();
            }
            syscall_count_.store(0);
        }
        
        bool isEnabled() noexcept {
            bool enable = enable_.load(std::memory_order_relaxed);
            return enable;
        }
        
        int64_t max_data_count() noexcept {
            return max_data_count_;
        }
        
        void set_max_data_count(int64_t c) {
            if (!Running()) {
                max_data_count_ = c;
            }
            else {
                throw ProtectException();
            }
        }
        
        void DataOverflowNotifaction() {
            Stop();
            std::lock_guard<std::mutex> l(ob_lock_);
            std::for_each(observers_.begin(), observers_.end(), [](Observer* ob) {
                ob->OnDataOverflow();
            });
        }
        
        void addObserver(Observer* ob) {
            std::lock_guard<std::mutex> l(ob_lock_);
            observers_.emplace_back(ob);
        }
        
        void removeObserver(Observer* ob) {
            std::lock_guard<std::mutex> l(ob_lock_);
            auto idx = std::find(observers_.begin(), observers_.end(), ob);
            if (idx != observers_.end()) {
                observers_.erase(idx);
            }
        }
        
    private:
        
        void setEnabled(bool enable) {
            enable_.store(enable, std::memory_order_relaxed);
        }
        
    private:
        std::atomic<bool> enable_;
        std::atomic<int64_t> syscall_count_;
        int64_t max_data_count_;
        std::mutex lock_;
        MallocPool pool_;
        MallocWrapZones wrap_zones_;
        
        std::mutex ob_lock_;
        std::vector<Observer*> observers_;
    };
}

#endif /* MemoryDetector_hpp */
