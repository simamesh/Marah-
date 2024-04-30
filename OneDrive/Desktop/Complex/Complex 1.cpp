#include <iostream>
#include "Complex.h"

Complex::Complex(double re, double im) : realteil(re), imaginaerteil(im) {}

double Complex::getRealteil() const {
    return realteil;
}

void Complex::setRealteil(double re) {
    realteil = re;
}

double Complex::getImaginaerteil() const {
    return imaginaerteil;
}

void Complex::setImaginaerteil(double im) {
    imaginaerteil = im;
}

Complex Complex::operator+(const Complex& andereZahl) const {
    double sumReal = realteil + andereZahl.realteil;
    double sumImag = imaginaerteil + andereZahl.imaginaerteil;
    return Complex(sumReal, sumImag);
}

Complex Complex::operator-(const Complex& andereZahl) const {
    double diffReal = realteil - andereZahl.realteil;
    double diffImag = imaginaerteil - andereZahl.imaginaerteil;
    return Complex(diffReal, diffImag);

}
  std::ostream& operator<<(std::ostream& os, const Complex& complex) {
    os << complex.realteil;
    if (complex.imaginaerteil >= 0.0)
        os << " + " << complex.imaginaerteil << "i";
    else
        os << " - " << -complex.imaginaerteil << "i";
    return os;
}

  std::istream& operator>>(std::istream& is, Complex& complex) {
   
    is >> complex.realteil >> complex.imaginaerteil;
    return is;
}






int main() {
    
        

        
  


 }
