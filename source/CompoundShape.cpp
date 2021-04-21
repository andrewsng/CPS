#include "CompoundShape.hpp"
#include <algorithm>
#include <numeric>

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

LayeredShapes::LayeredShapes(std::initializer_list<std::shared_ptr<Shape>> list) : CompoundShapes(list) 
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

VerticalShapes::VerticalShapes(std::initializer_list<std::shared_ptr<Shape>> list) : CompoundShapes(list)
{
	_width = std::max(list, [](auto& a, auto& b) {	return a->Width() < b->Width();	})->Width();
	_height = std::accumulate(list.begin(), list.end(), 0.0, [](double sum, const auto& s) {return sum + s->Height(); });
}

[[nodiscard]] std::string VerticalShapes::moveToStartPosition() const
{
    return "0 " + std::to_string(-Height() / 2) + " rmoveto\n";
}

[[nodiscard]] std::string VerticalShapes::moveHalfwayForShape(const std::shared_ptr<Shape> &shape) const
{
    return "0 " + std::to_string(shape->Height() / 2) + " rmoveto\n";
}

std::shared_ptr<LayeredShapes> Layered(std::initializer_list<std::shared_ptr<Shape>> list)
{
	return std::make_shared<LayeredShapes>(list);
}

std::shared_ptr<VerticalShapes> Vertical(std::initializer_list<std::shared_ptr<Shape>> list)
{
	return std::make_shared<VerticalShapes>(list);
}

