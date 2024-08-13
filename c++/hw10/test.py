import vectoralgebra

# Пример использования функций и класса
v1 = [1.0, 2.0, 3.0]
v2 = [4.0, 5.0, 6.0]

print(vectoralgebra.add(v1, v2))
print(vectoralgebra.subtract(v1, v2))
print(vectoralgebra.scalarProduct(v1, v2))

v3 = vectoralgebra.Vector3D(1.0, 2.0, 3.0)
print(v3.length())
v3.normalize()
print(v3.length())