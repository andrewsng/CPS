#ifndef UAF372_CPS_COMPOUNDSHAPE_H
#define UAF372_CPS_COMPOUNDSHAPE_H

#include "Shape.hpp"

class CompoundShapes : public Shape {
    
protected:

    [[nodiscard]] virtual std::vector<std::shared_ptr<Shape>> getShapes() const = 0;
    [[nodiscard]] virtual std::string moveToStartPosition() const = 0;
    [[nodiscard]] virtual std::string moveHalfwayForShape(const std::shared_ptr<Shape> &shape) const = 0;
    
public:

    virtual ~CompoundShapes() = default;

	[[nodiscard]] std::string ToPostScript() const override;

};

class LayeredShapes : public CompoundShapes {

private:

    double _width;
    double _height;
    std::vector<std::shared_ptr<Shape>> _shapeList;

    [[nodiscard]] virtual std::vector<std::shared_ptr<Shape>> getShapes() const override { return _shapeList; }
    [[nodiscard]] std::string moveToStartPosition() const override;
    [[nodiscard]] std::string moveHalfwayForShape(const std::shared_ptr<Shape> &shape) const override;
	
public:

	[[nodiscard]] double Width() const override { return _width; }
	[[nodiscard]] double Height() const override { return _height; }
	LayeredShapes(std::initializer_list<std::shared_ptr<Shape>> list);

};

std::shared_ptr<LayeredShapes> Layered(std::initializer_list<std::shared_ptr<Shape>> list);

#endif