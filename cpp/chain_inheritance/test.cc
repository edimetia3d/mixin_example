//
// License: MIT
//
#include <iostream>
#include "geo.h"
#include "chain_inherit_mixins.h"
#include "geo_adapter.h"

class IronTriangleI : public TriangleI {
public:
  Graph Draw() override {
    return std::string("ironI ") + TriangleI::Draw();
  }
  int call_super_draw_count_ = 0; // must be defined, so it could be mixed with SuperDrawMixin
};

class IronTriangleC : public TriangleC {
public:
  Graph Draw() {
    return std::string("ironC ") + TriangleC::Draw();
  }
  int call_super_draw_count_ = 0; // must be defined, so it could be mixed with SuperDrawMixin
};

void Dump(const Graph &graph) {
  std::cout << graph << std::endl;
}

int main() {
  using MixedIronTriangleI = SuperDrawMixin<LoggingMixin<IronTriangleI>>;
  Dump("=============0");
  MixedIronTriangleI irontriangle_i;
  Dump(irontriangle_i.SuperDraw());

  using MixedIronTriangleC = SuperDrawMixin<LoggingMixin<IronTriangleC>>;
  Dump("=============1");
  // Also work for concept
  MixedIronTriangleC irontriangle_c;
  Dump(irontriangle_c.SuperDraw());

  Dump("=============2");
  // IronTriangleC is NOT an IGeo, so it must be adapted to IGeo to be used as an IGeo
  InterfaceAdapter<MixedIronTriangleC> irontriangle_c_adapted;
  IGeo *geos[2] = {&irontriangle_i, &irontriangle_c_adapted};
  for (auto p : geos) {
    Dump(p->Draw());
  }

  Dump("=============3");
  // If we have a llvm style dyn_cast, adapt both to ConceptGeo would also be fine.
  ConceptAdapter<MixedIronTriangleI> irontriangle_i_adapted_to_cgeo;
  ConceptAdapter<MixedIronTriangleC> irontriangle_c_adapted_to_cgeo;
  ConceptGeo *c_geos[2] = {&irontriangle_i_adapted_to_cgeo, &irontriangle_c_adapted_to_cgeo};
  Dump(static_cast<ConceptAdapter<MixedIronTriangleI> *>(c_geos[0])->Draw());  // better be the llvm dyn_cast
  Dump(static_cast<ConceptAdapter<MixedIronTriangleC> *>(c_geos[1])->Draw()); // better be the llvm dyn_cast
}
