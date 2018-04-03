//
//  DDMallocDetector.cpp
//  DDMallocDetector
//
//  Created by daniel on 2018/3/31.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#include "MallocDetector.h"
#include "MemoryDetector.hpp"
#import "MDInspectorWindow.h"

void malloc_detector_attach_zone(bool default_zone) {
    auto d = MD::MemoryDetector::GetInstance();
    if (default_zone) {
        d->DetectorDefaultZone();
    }
    else {
        d->DetectorAllZones();
    }
}

void malloc_detector_start() {
    auto d = MD::MemoryDetector::GetInstance();
    d->ClearPool();
    d->Start();
}

void malloc_detector_stop() {
    MD::MemoryDetector::GetInstance()->Stop();
}

bool malloc_detector_is_running() {
    return MD::MemoryDetector::GetInstance()->Running();
}


void malloc_detector_show_inspector() {
    [MDInspectorWindow enable];
}
