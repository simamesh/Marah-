#include "transportmittel.h"
#include <iostream>


Transportmittel::Transportmittel(double h, double b) : hoehe(h), breite(b) {}


double Transportmittel::getHoehe() const {
    return hoehe;
}

double Transportmittel::getBreite() const {
    return breite;
}

// 
void Transportmittel::bewegen(const std::string& richtung) {
    std::cout << "In Richtung " << richtung << " bewegen." << std::endl;
}


int main() {
    
    Transportmittel tm(3.5, 2.0);
    tm.bewegen("Norden");
    std::cout << "Höhe: " << tm.getHoehe() << " m, Breite: " << tm.getBreite() << " m" << std::endl;
    
   

    return 0;
}

