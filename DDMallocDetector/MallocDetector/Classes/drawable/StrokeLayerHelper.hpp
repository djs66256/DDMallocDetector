//
//  StrokeLayer.hpp
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/29.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#ifndef StrokeLayerHelper_hpp
#define StrokeLayerHelper_hpp

namespace MD {
    template<class _T>
    struct ValueRange {
        _T min;
        _T max;
        
        ValueRange() = default;
        ValueRange(const ValueRange&) = default;
        ValueRange(_T min, _T max) : min(min), max(max) {}
        ValueRange(_T&& min, _T&& max) : min(min), max(max) {}
        ValueRange(std::initializer_list<_T> l) : min(*l.begin()), max(*(l.begin() + 1)) {}
    };
    typedef ValueRange<Float> FloatRange;
    
    template<class _V>
    struct AvarageLocation final {
    public:
        AvarageLocation(Rect& r, FloatRange& x, FloatRange& y, std::size_t count)
        : r_(r), x_(r.left()),
          yHeight_(y.max - y.min), count_(count),
          deltaX_(count > 1 ? r.width()/(count-1) : 0) {
              
          }
        
        Float x(_V& v) {
            Float r = x_;
            x_ += deltaX_;
            return r;
        }
        Float y(_V& v) {
            return r_.bottom() - (Float(v) / yHeight_ * r_.size.height);
        }
    private:
        Rect& r_;
        Float yHeight_;
        Float deltaX_;
        std::size_t count_;
        Float x_ = 0;
    };
    
    // x以真实值位置排布
    template<class _V = std::pair<class _T1, class _T2>>
    struct PairLocation final {
    public:
        PairLocation(Rect& r, FloatRange& x, FloatRange& y, std::size_t count)
        : r_(r), yHeight_(y.max - y.min), xWidth_(x.max - x.min), xRange_(x), yRange_(y) {}
        
        Float x(_V& v) {
            return (Float(v.first) - xRange_.min) * r_.width() / xWidth_ + r_.left();
        }
        Float y(_V& v) {
            return r_.bottom() - (Float(v.second) - yRange_.min) * r_.height() / yHeight_;
        }
        
    private:
        Rect& r_;
        Float yHeight_;
        Float xWidth_;
        FloatRange xRange_;
        FloatRange yRange_;
    };
    
    // x以线性排布
    template<class _V = std::pair<class _T1, class _T2>>
    struct PairLinearLocation final {
    public:
        PairLinearLocation(Rect& r, FloatRange& x, FloatRange& y, std::size_t count)
        : r_(r), yHeight_(y.max - y.min), yRange_(y), x_(r.left()), deltaX_(count > 1 ? r.width()/(count-1) : 0) {}
        
        Float x(_V& v) {
            Float r = x_;
            x_ += deltaX_;
            return r;
        }
        Float y(_V& v) {
            return r_.bottom() - (Float(v.second) - yRange_.min) * r_.height() / yHeight_;
        }
        
    private:
        Rect& r_;
        Float yHeight_;
        FloatRange yRange_;
        Float x_ = 0;
        Float deltaX_;
    };
}

#endif // StrokeLayerHelper_hpp
