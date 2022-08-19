"""
This is a suck Geometry lib, it only contains an abstract IGeo and a Triangle.
"""
Graph = str


class IGeo:
    """An abstract base class for geometric objects."""

    def draw(self):
        raise NotImplementedError()


class Triangle(IGeo):
    """Triangle."""

    def draw(self) -> Graph:
        return "Triangle"
