#ifndef UAF372_CPS_COMPOUNDSHAPE_H
#define UAF372_CPS_COMPOUNDSHAPE_H

#include "Shape.hpp"

class CompoundShape : public Shape {
    
private:

    double _width;
    double _height;
    std::vector<std::shared_ptr<Shape>> _shapeList;
    
protected:

    [[nodiscard]] virtual std::string moveToStartPosition();
    [[nodiscard]] virtual std::string moveHalfwayForShape(const std::shared_ptr<Shape> &shape);
    
public:

    virtual ~CompoundShape() = default;

	[[nodiscard]] virtual double Width() const = 0;
	[[nodiscard]] virtual double Height() const = 0;
	[[nodiscard]] std::string ToPostScript() const override;

};

#endif