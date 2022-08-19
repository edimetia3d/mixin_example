//
// License: MIT
//

#ifndef CPP_GEO_H
#define CPP_GEO_H
#include <string>
#include <cassert>

using Graph = std::string;

/**
 * Any type defines a method of `Graph Draw()` is a ConceptGeo.
 */
class ConceptGeo {
};

class TriangleC { // TriangleC DOES NOT inherit from ConceptGeo, it is a Geo conceptually
public:
  Graph Draw() {
    return "Triangle";
  }
};

/**
 * Any type inherits from `IGeo` is a Geo.
 */
class IGeo {
public:
  virtual Graph Draw() = 0;
};

class TriangleI : public IGeo {
public:
  Graph Draw() override {
    return "Triangle";
  }
};

#endif //CPP_GEO_H
