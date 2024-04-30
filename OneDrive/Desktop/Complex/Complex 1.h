#include<iostream>
#include<Complex.h>

class Complex {
private:
    double realteil;
    double imaginaerteil;

public:
    Complex(double realteil, double imaginaerteil );
    double getRealteil() const;
    void setRealteil(double realteil);
    double getImaginaerteil() const;
    void setImaginaerteil(double imaginaerteil);

    Complex operator+(const Complex& andereZahl) const;
    Complex operator-(const Complex& andereZahl) const;

    



};
