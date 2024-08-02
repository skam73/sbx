#include <iostream>
#include <memory>
#include <cmath>

class Vector3D{
    private:
    
    std::unique_ptr<double[]> coords;

    public:
    
    Vector3D():
    coords(new double[3]{0.0, 0.0, 0.0}){}

    //Конструктор перемещения
    Vector3D(Vector3D&& other) noexcept :
    coords(std::move(other.coords)){}

    //Оператор присваивания перемещением
    Vector3D& operator=(Vector3D&& other) noexcept{
        if(this != &other){
            coords = std::move(other.coords);
        }
        return *this;
    }

    //Деструктор(небходим для умных указателей)
    ~Vector3D() = default;

    static void Normalize(std::shared_ptr<Vector3D> vec){
        double magnitude = std::sqrt(vec->coords[0]*vec->coords[0] 
                                    + vec->coords[1]*vec->coords[1]
                                    + vec->coords[2]*vec->coords[2]);

        vec->coords[0] /= magnitude;
        vec->coords[1] /= magnitude;
        vec->coords[2] /= magnitude;
    }

};

int main(){

    Vector3D vec1;
    Vector3D vec2 = std::move(vec1);

    std::unique_ptr<Vector3D> unVec = std::make_unique<Vector3D>();
    std::shared_ptr<Vector3D> shVec = std::make_shared<Vector3D>();

    Vector3D::Normalize(shVec);

    return 0;
}