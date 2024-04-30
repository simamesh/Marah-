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


    friend std::ostream& operator<<(std::ostream& os, const Complex& complex);
    friend std::istream& operator>>(std::istream& is, Complex& complex);

    



};
