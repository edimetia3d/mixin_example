"""
Contains mixins should be used in multi-inheritance.
"""


class SuperDrawMixin:
    """This mixin will add a new method super_draw"""

    def super_draw(self):
        self._call_super_draw_count = getattr(self, "_call_super_draw_count", 0) + 1
        return "super " + self.draw()


class DrawWithPrintMixin:
    """This mixin will add a new method draw_and_print"""

    def draw_and_print(self):
        ret = self.draw()
        print(f"{ret} | {getattr(self, '_call_super_draw_count', 0)}")
        return ret
