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

LandTransportmittel::LandTransportmittel(double h, double b, int r) : Transportmittel(h, b), radzahl(r) {}

void LandTransportmittel::fahren(double km) {
    std::cout << "Fahre " << km << " km!" << std::endl;
}

void LandTransportmittel::schieben(double km) {
    std::cout << "Schiebe " << km << " km!" << std::endl;
}

int LandTransportmittel::getRadzahl() const {
    return radzahl;
}
WasserTransportmittel::WasserTransportmittel(double h, double b, double brt) : Transportmittel(h, b), bruttoregistertonnen(brt) {}

void WasserTransportmittel::anlegen(const std::string& Anlegehafen) {
    std::cout << "Lege an in " << Anlegehafen << "!" << std::endl;
}

void WasserTransportmittel::ablegen(const std::string& Ablegehafen) {
    std::cout << "Lege ab von " << Ablegehafen << "!" << std::endl;
}

double WasserTransportmittel::getBruttoregistertonnen() const {
    return bruttoregistertonnen;
}

int main() {
    
    Transportmittel tm(3.5, 2.0);
    tm.bewegen("Norden");
    std::cout << "Höhe: " << tm.getHoehe() << " m, Breite: " << tm.getBreite() << " m" << std::endl;

    LandTransportmittel ltm(4.0, 2.5, 4);
    ltm.bewegen("Osten");
    std::cout << "Höhe: " << ltm.getHoehe() << " m, Breite: " << ltm.getBreite() << " m, Radzahl: " << ltm.getRadzahl() << std::endl;
    ltm.fahren(100);
    ltm.schieben(2.5);

    WasserTransportmittel wtm(10.0, 3.2, 5000.0);
    wtm.bewegen("Süden");
    std::cout << "Höhe: " << wtm.getHoehe() << " m, Breite: " << wtm.getBreite() << " m, Bruttoregistertonnen: " << wtm.getBruttoregistertonnen() << std::endl;
    wtm.anlegen("Hamburg");
    wtm.ablegen("Rotterdam");
    
   

    return 0;
}

