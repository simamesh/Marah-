

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

class LandTransportmittel : public Transportmittel {
private:
    int radzahl;

public:
    LandTransportmittel(double h, double b, int r);
    void fahren(double km);
    void schieben(double km);
    int getRadzahl() const;
};

class WasserTransportmittel : public Transportmittel {
private:
    double bruttoregistertonnen;

public:
    WasserTransportmittel(double h, double b, double brt);
    void anlegen(const std::string& Anlegehafen);
    void ablegen(const std::string& Ablegehafen);
    double getBruttoregistertonnen() const;
};

