from chained_mixins import super_draw_mixin, logging_mixin
from geo import Triangle


class IronTriangle(Triangle):
    def draw(self):
        return "iron " + Triangle.draw(self)


if __name__ == "__main__":
    MixedIronTriangle0 = logging_mixin(super_draw_mixin(IronTriangle))
    mixed0 = MixedIronTriangle0()  # dynamic mixed

    # because the python support MRO, and our mixins uses super(), we
    # can also mixin the mixins by creating a new class that inherits (Mix0,Mix1,...,Target)
    SuperDrawMixin = super_draw_mixin(object)
    LoggingMixin = logging_mixin(object)


    class MixedIronTriangle1(SuperDrawMixin, LoggingMixin, IronTriangle):
        def draw(self):
            # We are also able to update draw, as long as we call super().draw()
            # super().draw() must be called to active the MRO call
            return "static " + super().draw()


    mixed1 = MixedIronTriangle1()  # static mixed

    mixed_objs = [mixed0, mixed1]
    for o in mixed_objs:
        print("======================")
        print(o.super_draw())
