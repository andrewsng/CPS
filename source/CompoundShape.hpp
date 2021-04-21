#ifndef UAF372_CPS_COMPOUNDSHAPE_H
#define UAF372_CPS_COMPOUNDSHAPE_H

#include "Shape.hpp"

class CompoundShapes : public Shape {

private:

    std::vector<std::shared_ptr<Shape>> _shapeList;
    
protected:

    [[nodiscard]] std::vector<std::shared_ptr<Shape>> getShapes() const { return _shapeList; }
    [[nodiscard]] virtual std::string moveToStartPosition() const = 0;
    [[nodiscard]] virtual std::string moveHalfwayForShape(const std::shared_ptr<Shape> &shape) const = 0;
    
public:

    CompoundShapes::CompoundShapes(std::initializer_list<std::shared_ptr<Shape>> list)
        : _shapeList(list)
    {}

    virtual ~CompoundShapes() = default;

	[[nodiscard]] std::string ToPostScript() const override;

};

class LayeredShapes : public CompoundShapes {

private:

    double _width;
    double _height;

    [[nodiscard]] std::string moveToStartPosition() const override;
    [[nodiscard]] std::string moveHalfwayForShape(const std::shared_ptr<Shape> &shape) const override;
	
public:

	[[nodiscard]] double Width() const override { return _width; }
	[[nodiscard]] double Height() const override { return _height; }
	LayeredShapes(std::initializer_list<std::shared_ptr<Shape>> list);

};

class VerticalShapes : public CompoundShapes {

private:

	double _width;
	double _height;

    [[nodiscard]] std::string moveToStartPosition() const override;
    [[nodiscard]] std::string moveHalfwayForShape(const std::shared_ptr<Shape> &shape) const override;

public:

	[[nodiscard]] double Width() const override { return _width; }
	[[nodiscard]] double Height() const override { return _height; }
	VerticalShapes(std::initializer_list<std::shared_ptr<Shape>> list);

};

std::shared_ptr<LayeredShapes> Layered(std::initializer_list<std::shared_ptr<Shape>> list);

std::shared_ptr<VerticalShapes> Vertical(std::initializer_list<std::shared_ptr<Shape>> list);

#endif