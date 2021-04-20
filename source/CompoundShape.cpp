#include "CompoundShape.hpp"

[[nodiscard]] std::string CompoundShape::moveToStartPosition()
{
    return std::string{};
}

[[nodiscard]] std::string CompoundShape::moveHalfwayForShape(const std::shared_ptr<Shape> &shape)
{
    return std::string{};
}

[[nodiscard]] std::string CompoundShape::ToPostScript() const
{
    std::string output{"gsave\n"};
    
    output += moveToStartPosition();
    for (const auto &shape : _shapeList)
    {
        output += moveHalfwayForShape(shape);
        output += shape->ToPostScript();
        output += moveHalfwayForShape(shape);
        output += "\n";
    }

    output += "grestore\n";

    return output;
}