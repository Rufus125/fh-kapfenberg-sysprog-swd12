#ifndef THERMOMETER_H
#define THERMOMETER_H

#include <string>
#include <exception>

class ThermometerException : public std::exception
{
public:
    ThermometerException(const std::string& msg) : _msg(msg) {}
    virtual ~ThermometerException() throw() {}
    virtual const char* what() const throw()
    {
        return _msg.c_str();
    }
private:
    const std::string _msg;
};

class Thermometer
{
public:
    virtual ~Thermometer() {}
    virtual double get_temperature() const = 0;
};

#endif
