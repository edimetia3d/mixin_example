"""
Contains mixins should be used in chain-inheritance.
"""


def super_draw_mixin(base):
    class _SuperDrawMixin(base):
        """This mixin will add a new method super_draw"""

        def super_draw(self):
            self._call_super_draw_count = getattr(self, "_call_super_draw_count", 0) + 1
            return "super " + self.draw()

    return _SuperDrawMixin


def logging_mixin(base):
    class _LoggingMixin(base):
        """
        This mixin will enhance the draw, so that a log will be created before/after draw is called
        """

        def draw(self):
            print(f"Enter {self}.draw")
            ret = super().draw()
            print(f"Exit {self}.draw")
            return ret

    return _LoggingMixin
