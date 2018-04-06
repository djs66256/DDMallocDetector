//
//  DDMallocDetector.hpp
//  DDMallocDetector
//
//  Created by daniel on 2018/3/31.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#ifndef DDMallocDetector_hpp
#define DDMallocDetector_hpp

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

    void malloc_detector_attach_zone(bool default_zone);
    void malloc_detector_start();
    void malloc_detector_stop();
    bool malloc_detector_is_running();
    void malloc_detector_show_inspector();
    
#ifdef __cplusplus
} // extern "C"
#endif

#endif /* DDMallocDetector_hpp */
