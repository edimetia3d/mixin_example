//
// License: MIT
//

#ifndef CPP_UTILS_H
#define CPP_UTILS_H
#include <memory>
#include "geo.h"

template<class SourceT>
class ConceptAdapter : public SourceT, public ConceptGeo {
public:
  Graph Draw() {
    return SourceT::Draw();
  }
};

template<class SourceT>
class InterfaceAdapter : public SourceT, public IGeo {
public:
  Graph Draw() override {
    return SourceT::Draw();
  }
};

#endif //CPP_UTI
