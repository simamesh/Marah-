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



 }
// oder 
    Complex Complex::operator/(const Complex& andereZahl) const {
        if (andereZahl.getRealteil() == 0 && andereZahl.getImaginaerteil() == 0) {
            throw std::invalid_argument("Division durch komplexe Zahl 0");
        }
        double nenner = andereZahl.getRealteil() * andereZahl.getRealteil() + andereZahl.getImaginaerteil() * andereZahl.getImaginaerteil();
        double ergebnisReal = (realteil * andereZahl.getRealteil() + imaginaerteil * andereZahl.getImaginaerteil()) / nenner;
        double ergebnisImaginaer = (imaginaerteil * andereZahl.getRealteil() - realteil * andereZahl.getImaginaerteil()) / nenner;
        return Complex(ergebnisReal, ergebnisImaginaer);
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
    try {
        Complex z1(4.0, 2.0);
        Complex z2(0.0, 0.0);

        Complex result = z1 / z2;
        std::cout << "Ergebnis der Division: " << result << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Fehler bei der Division: " << e.what() << std::endl;

    }
    return 0;
    
        

        
  


 }
