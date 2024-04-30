

#include <iostream>
#include <string>

class Transportmittel {
private:
    double hoehe;
    double breite;

public:
    // Allgemeiner Konstruktor
    Transportmittel(double h, double b);

    // Getter-Methoden
    double getHoehe() const;
    double getBreite() const;

    // Methode zum Bewegen
    void bewegen(const std::string& richtung);
};



