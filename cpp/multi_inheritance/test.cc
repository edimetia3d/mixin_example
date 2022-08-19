//
// License: MIT
//
#include <iostream>
#include "geo.h"
#include "multi_inherit_mixins.h"
#include "geo_adapter.h"

class IronTriangleI : public SuperDrawMixin<IronTriangleI>,
                      public DrawWithPrintMixin<IronTriangleI>,
                      public TriangleI {
public:
  Graph Draw() override {
    return std::string("ironI ") + TriangleI::Draw();
  }

  int call_super_draw_count_ = 0; // must be defined, so it could be mixed with SuperDrawMixin
};

// Because we are using virtual functions, GoldIronTriangleI will also get mixins work correctly.
class GoldIronTriangleI : public IronTriangleI {
public:
  Graph Draw() override {
    return std::string("gold ") + IronTriangleI::Draw();
  }
};

class IronTriangleC : public SuperDrawMixin<IronTriangleC>,
                      public DrawWithPrintMixin<IronTriangleC>,
                      public TriangleC {
public:
  Graph Draw() {
    return std::string("ironC ") + TriangleC::Draw();
  }

  int call_super_draw_count_ = 0; // must be defined, so it could be mixed with SuperDrawMixin
};

// GoldIronTriangleC WILL NOT work correctly, because the function call to Draw() is not virtual, and had been resolved statically
// in IronTriangleC's definition
class GoldIronTriangleC : public IronTriangleC {
public:
  Graph Draw() {
    return std::string("gold ") + IronTriangleC::Draw();
  }
};

void Dump(const Graph &graph) {
  std::cout << graph << std::endl;
}

int main() {
  Dump("=============0");
  GoldIronTriangleI goldirontriangle_i;
  Dump(goldirontriangle_i.SuperDraw());
  goldirontriangle_i.DrawAndPrint();
  Dump("=============1");
  // this will not work as expected, "gold" will not be printed
  GoldIronTriangleC goldirontriangle_c;
  Dump(goldirontriangle_c.SuperDraw());
  goldirontriangle_c.DrawAndPrint();

  Dump("=============2");
  // IronTriangleC is NOT an IGeo, so it must be adapted to IGeo to be used as an IGeo
  InterfaceAdapter<IronTriangleC> irontriangle_c_adapted_to_igeo;
  IGeo *i_geos[2] = {&goldirontriangle_i, &irontriangle_c_adapted_to_igeo};
  for (auto p : i_geos) {
    Dump(p->Draw());
  }

  Dump("=============3");
  // If we have a llvm style dyn_cast, we can adapt both class to ConceptGeo, this will also be fine.
  ConceptAdapter<GoldIronTriangleI> goldirontriangle_i_adapted_to_cgeo;
  ConceptAdapter<IronTriangleC> irontriangle_c_adapted_to_cgeo;
  ConceptGeo *c_geos[2] = {&goldirontriangle_i_adapted_to_cgeo, &irontriangle_c_adapted_to_cgeo};
  Dump(static_cast<ConceptAdapter<GoldIronTriangleI> *>(c_geos[0])->Draw());  // better be the llvm dyn_cast
  Dump(static_cast<ConceptAdapter<IronTriangleC> *>(c_geos[1])->Draw()); // better be the llvm dyn_cast
}