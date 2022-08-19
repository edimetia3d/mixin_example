from geo import Triangle
from multi_inherit_mixins import SuperDrawMixin, DrawWithPrintMixin


class IronTriangle(SuperDrawMixin, DrawWithPrintMixin, Triangle):
    def draw(self):
        return "iron " + Triangle.draw(self)


if __name__ == "__main__":
    obj = IronTriangle()
    obj.super_draw()
    obj.draw_and_print()
