#include "CompoundShape.hpp"
#include <algorithm>

[[nodiscard]] std::string CompoundShapes::ToPostScript() const
{
    std::string output{"gsave\n"};
    
    output += moveToStartPosition();
    for (const auto &shape : getShapes())
    {
        output += moveHalfwayForShape(shape);
        output += shape->ToPostScript();
        output += moveHalfwayForShape(shape);
        output += "\n";
    }

    output += "grestore\n";

    return output;
}

LayeredShapes::LayeredShapes(std::initializer_list<std::shared_ptr<Shape>> list) : _shapeList(list) 
{
	_width = std::max(list, [](auto& a, auto& b) {	return a->Width() < b->Width();	})->Width();
	_height = std::max(list, [](auto& a, auto& b) {	return a->Height() < b->Height(); })->Height();
}

[[nodiscard]] std::string LayeredShapes::moveToStartPosition() const
{
    return std::string{};
}

[[nodiscard]] std::string LayeredShapes::moveHalfwayForShape(const std::shared_ptr<Shape> &shape) const
{
    return std::string{};
}

std::shared_ptr<LayeredShapes> Layered(std::initializer_list<std::shared_ptr<Shape>> list)
{
	return std::make_shared<LayeredShapes>(list);
}

