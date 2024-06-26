#include <iostream>
#include <string>
#include <stdexcept>

namespace hw
{
    class Car
    {
    private:
        inline static int _count = 0;

    protected:
        std::string _trademark;
        int _cylinders;
        int _power;

    public:
        Car() : _trademark("noname"), _cylinders(4), _power(96) { _count++; }
        Car(std::string trademark, int cylinders, int power) : _trademark(trademark), _cylinders(cylinders), _power(power) { _count++; }
        Car(const Car &other) : _trademark(other._trademark), _cylinders(other._cylinders), _power(other._power) { _count++; }

        virtual ~Car() { _count--; }

        std::string getTrademark() const { return _trademark; }
        void setTrademark(std::string trademark) { _trademark = trademark; }

        int getCylinders() const { return _cylinders; }
        void setCylinders(int cylinders)
        {
            if (cylinders <= 0)
            {
                throw std::invalid_argument("0 or negative");
            }
            _cylinders = cylinders;
        }

        int getPower() const { return _power; }
        void setPower(int power)
        {
            if (power <= 0)
            {
                throw std::invalid_argument("0 or negative");
            }
            _power = power;
        }

        Car &operator=(const Car &other)
        {
            if (this != &other)
            {
                _trademark = other._trademark;
                _cylinders = other._cylinders;
                _power = other._power;
            }
            return *this;
        }

        friend std::ostream &operator<<(std::ostream &out, const Car &car)
        {
            out << "trademark = " << car._trademark << std::endl;
            out << "cylinders = " << car._cylinders << std::endl;
            out << "power = " << car._power << std::endl;
            return out;
        }

        friend std::istream &operator>>(std::istream &in, Car &car)
        {
            in >> car._trademark >> car._cylinders >> car._power;
            return in;
        }

        friend int count();
    };

    int count()
    {
        return Car::_count;
    }

    class Lorry : public Car
    {
    private:
        int _lifting;

    public:
        Lorry() : Car(), _lifting(10) {}
        Lorry(std::string trademark, int cylinders, int power, int lifting) : 
            Car(trademark,cylinders, power) ,_lifting(lifting){ }
        Lorry(Lorry& other):Car(other), _lifting(other._lifting){}


        int getLifting() const { return _lifting; }
        void setLifting(int lifting)
        {
            if (lifting <= 0)
            {
                throw std::invalid_argument("0 or negative");
            }
            _lifting = lifting;
        }

        Lorry &operator=(const Lorry &other)
        {
            if (this != &other)
            {
                Car::operator=(other);
                _lifting = other._lifting;
            }
            return *this;
        }

        friend std::ostream &operator<<(std::ostream &out, const Lorry &lorry)
        {
            out << static_cast<const Car &>(lorry);
            out << "lifting = " << lorry._lifting << std::endl;
            return out;
        }

        friend std::istream &operator>>(std::istream &in, Lorry &lorry)
        {
            in >> static_cast<Car &>(lorry);
            in >> lorry._lifting;
            return in;
        }
    };
}

// using namespace hw;

int main()
{
    try
    {
        std::cout << "All(begin) = " << hw::count() << std::endl << std::endl;;

        hw::Car car1("BMW", 6, 300);
        hw::Lorry lorry1("Volvo", 8, 400, 5000);

        std::cout << car1 << std::endl;
        std::cout << lorry1 << std::endl;

        std::cout << "All(end) = " << hw::count() << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}