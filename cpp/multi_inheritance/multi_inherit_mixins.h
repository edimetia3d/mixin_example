//
// License: MIT
//

/**
 * Multi-inheritance mixin can only be used to add new methods to existing classes.
 */

#ifndef UNTITLED_CPP_MULTI_INHERIT_MIXINS_H
#define UNTITLED_CPP_MULTI_INHERIT_MIXINS_H

/**
 * Add a new method `SuperDraw`
 */
template<class DerivedT>
class SuperDrawMixin {
public:
  Graph SuperDraw() {
    static_cast<DerivedT *>(this)->call_super_draw_count_++;
    return std::string("super ") + static_cast<DerivedT *>(this)->Draw();
  }
private:
  SuperDrawMixin() = default;
  friend DerivedT; // Only DerivedT can access SuperDrawMixin
};

/**
 * Add a new method `DrawAndPrint`
 */
template<class DerivedT>
class DrawWithPrintMixin {
public:
  Graph DrawAndPrint() {
    auto ret = static_cast<DerivedT *>(this)->Draw();
    std::cout << ret << " | super_draw_count: " << static_cast<DerivedT *>(this)->call_super_draw_count_ << std::endl;
    return ret;
  }
private:
  DrawWithPrintMixin() = default;
  friend DerivedT; // Only DerivedT can access DrawWithPrintMixin
};

#endif //UNTITLED_CPP_MULTI_INHERIT_MIXINS_H
