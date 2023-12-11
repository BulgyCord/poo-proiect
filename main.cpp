#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

/// Declarații înainte (forward declarations) pentru clase
class Inamici;
class Proiectil;

class Jucator {
private:
    std::string nume;
    int viata;
    int scor;
    int putereAtac;

public:
    Jucator(const std::string& nume, int viata, int scor, int putereAtac)
            : nume(nume), viata(viata), scor(scor), putereAtac(putereAtac) {
    }

    void ataca(Inamici& inamic, Proiectil& proiectil);
    int getPutereAtac() const;

    friend std::ostream& operator<<(std::ostream& os, const Jucator& jucator) {
        os << "Nume: " << jucator.nume << ", Viata: " << jucator.viata << ", Scor: " << jucator.scor << ", Putere de Atac: " << jucator.putereAtac;
        return os;
    }
};

class Inamici {
private:
    std::string nume;
    int viata;

public:
    Inamici(const std::string& nume, int viata) : nume(nume), viata(viata) {
    }

    void esteLovitDe(Jucator& jucator) {
        viata -= jucator.getPutereAtac();
    }

    friend std::ostream& operator<<(std::ostream& os, const Inamici& inamic) {
        os << "Nume: " << inamic.nume << ", Viata: " << inamic.viata;
        return os;
    }
};

class Proiectil {
private:
    int viteza;

public:
    Proiectil(int viteza) : viteza(viteza) {
    }

    void trage(Jucator& jucator, Inamici& inamic) {
        inamic.esteLovitDe(jucator);
    }

    friend std::ostream& operator<<(std::ostream& os, const Proiectil& proiectil) {
        os << "Viteza proiectilului: " << proiectil.viteza;
        return os;
    }
};

// Definiții pentru funcțiile membru din Jucator
void Jucator::ataca(Inamici& inamic, Proiectil& proiectil) {
    proiectil.trage(*this, inamic);
}

int Jucator::getPutereAtac() const {
    return putereAtac;
}

int main() {
    Jucator jucator("Jucator 1", 100, 0, 20);
    Inamici inamic("Inamic 1", 50);
    Proiectil proiectil(20);

    std::cout << "Starea jucatorului: " << jucator << std::endl;
    std::cout << "Starea inamicului: " << inamic << std::endl;

    jucator.ataca(inamic, proiectil);

    std::cout << "Starea jucatorului după atac: " << jucator << std::endl;
    std::cout << "Starea inamicului după atac: " << inamic << std::endl;

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Example");

    // Creare cerc
    sf::CircleShape circle(50.f);
    circle.setFillColor(sf::Color::Green);

    // Bucla principală
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Logică jocului și desenare
        // (Aici puteți adăuga codul pentru a desena nave, gloanțe, entități inamice, etc.)

        window.clear();
        window.draw(circle);
        window.display();
    }
    return 0;
}
