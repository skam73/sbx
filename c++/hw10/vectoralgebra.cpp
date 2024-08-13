#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // Include this header for STL support
#include <string>
#include <vector> // Include vector header

// Функции для сложения, вычитания и скалярного произведения векторов
std::vector<double> add(const std::vector<double>& v1, const std::vector<double>& v2) {
    std::vector<double> result(v1.size());
    for (int i = 0; i < v1.size(); ++i) {
        result[i] = v1[i] + v2[i];
    }
    return result;
}

std::vector<double> subtract(const std::vector<double>& v1, const std::vector<double>& v2) {
    std::vector<double> result(v1.size());
    for (int i = 0; i < v1.size(); ++i) {
        result[i] = v1[i] - v2[i];
    }
    return result;
}

double scalarProduct(const std::vector<double>& v1, const std::vector<double>& v2) {
    double result = 0.0;
    for (int i = 0; i < v1.size(); ++i) {
        result += v1[i] * v2[i];
    }
    return result;
}

// Класс для работы с трехмерными векторами
class Vector3D {
public:
    Vector3D() {}
    Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

    // Методы для вычисления длины вектора и нормализации
    double length() const {
        return sqrt(x * x + y * y + z * z);
    }

    void normalize() {
        double len = length();
        if (len != 0.0) {
            x /= len;
            y /= len;
            z /= len;
        }
    }

private:
    double x, y, z;
};

PYBIND11_MODULE(vectoralgebra, m) {
    m.def("add", &add, "Add two vectors");
    m.def("subtract", &subtract, "Subtract two vectors");
    m.def("scalarProduct", &scalarProduct, "Calculate the scalar product of two vectors");

    pybind11::class_<Vector3D>(m, "Vector3D")
        .def(pybind11::init<>())
        .def(pybind11::init<double, double, double>())
        .def("length", &Vector3D::length, "Return the length of the vector")
        .def("normalize", &Vector3D::normalize, "Normalize the vector");
}
