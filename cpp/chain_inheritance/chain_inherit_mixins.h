//
// License: MIT
//

/**
 * Chain style inheritance is most powerful and flexible way to implement mixins.
 */

#ifndef CPP_MIXINS_H
#define CPP_MIXINS_H
#include <stdio.h>

#include "geo.h"

/**
 * Enhance method `Draw` by mixin
 */
template<class TargetT>
class LoggingMixin : public TargetT {
public:
  Graph Draw() {
    printf("Enter %p \n", this);
    auto ret = TargetT::Draw(); // MUST use TargetT::Draw() to avoid endless recursion when Draw is a virtual function
    printf("Exit %p \n", this);
    return ret;
  }
};

/**
 * Add a new method `SuperDraw`
 */
template<class TargetT>
class SuperDrawMixin : public TargetT {
public:
  Graph SuperDraw() {
    this->call_super_draw_count_++;
    return std::string("super ") + static_cast<TargetT *>(this)->Draw();
  }
};

#endif //CPP_MIXINS_H
