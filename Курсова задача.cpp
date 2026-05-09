// Курсова задача.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// КУРСОВА РАБОТА - Йерархия "Растения"
#include <iostream>
#include <string>

using namespace std;

//  НИВО 0: АБСТРАКТЕН БАЗОВ КЛАС 
class Plant {
protected:
    string Vid;      // Атрибут 1
    int Vuzrast;     // Атрибут 2

public:
    // Конструктор по подразбиране
    Plant() : Vid("Neizvesten"), Vuzrast(0) {}

    // Инициализиращ конструктор с параметър по подразбиране
    Plant(string vid, int vuzrast = 1) : Vid(vid), Vuzrast(vuzrast) {}

    virtual ~Plant() {}

    // Чисто виртуална функция - абстрактен клас
    virtual void printInfo() const = 0;

    // Виртуални методи за полиморфизъм
    virtual void jiznenCikal() = 0;

    virtual void griji() {
        cout << "Osnovni grigi za " << Vid << endl;
    }

    // Собствени методи
    void fotosinteza() { cout << Vid << " izvurshva fotosinteza." << endl; }
    void rastene() { Vuzrast++; cout << Vid << " porasna." << endl; }
};

//  НИВО 1: ЦЪФТЯЩИ РАСТЕНИЯ 
class FloweringPlant : public Plant {
protected:
    string Cvqt;
    int MesecNaCuftetene;

public:
    FloweringPlant() : Plant(), Cvqt("Bql"), MesecNaCuftetene(5) {}
    FloweringPlant(string vid, int vazrast, string cvat, int mesec = 6)
        : Plant(vid, vazrast), Cvqt(cvat), MesecNaCuftetene(mesec) {
    }

    // Имплементираме printInfo тук, за да може да се ползва от наследниците
    void printInfo() const override {
        cout << "Vid: " << Vid << ", Vazrast: " << Vuzrast << " m., Cvat: " << Cvqt
            << ", Mesec: " << MesecNaCuftetene << endl;
    }

    void jiznenCikal() override {
        cout << Vid << " se podgotvq za cuftetene." << endl;
    }

    
    void privli4aneNaNasekomi() { cout << Vid << " privli4a pcheli." << endl; }
};

//  НИВО 2: РОЗА 
class Rose : public FloweringPlant {
protected:
    bool ImaBodli;
    double IntenzitetAromat;

public:
    Rose() : FloweringPlant(), ImaBodli(true), IntenzitetAromat(5.0) {}
    Rose(string vid, int vazrast, string cvat, int mesec, bool bodli, double aromat = 8.0)
        : FloweringPlant(vid, vazrast, cvat, mesec), ImaBodli(bodli), IntenzitetAromat(aromat) {
    }

    void printInfo() const override {
        FloweringPlant::printInfo(); // Извикваме базовата инфо
        cout << "Bodli: " << (ImaBodli ? "Da" : "Ne") << ", Aromat: " << IntenzitetAromat << endl;
    }

    void jiznenCikal() override { cout << Vid << " razcvetqva krasivo." << endl; }
    void ubojdane() { if (ImaBodli) cout << "Vnimanie! Bodli!" << endl; }
};

//  НИВО 3: ДИВА РОЗА (ШИПКА) 
class WildRose : public Rose {
private:
    int BroiShipki;

public:
    WildRose(string vid, int vazrast, int shipki = 20)
        : Rose(vid, vazrast, "Rozov", 6, true, 4.0), BroiShipki(shipki) {
    }

    void printInfo() const override {
        Rose::printInfo();
        cout << "Plodove (shipki): " << BroiShipki << endl;
    }

    void brane() { cout << "Subrane na " << BroiShipki << " shipki за chai." << endl; }
};

//  НИВО 1: НЕЦЪФТЯЩИ РАСТЕНИЯ 
class NonFloweringPlant : public Plant {
protected:
    string Habitat;
    bool ImaSpori;

public:
    NonFloweringPlant() : Plant(), Habitat("Gora"), ImaSpori(true) {}
    NonFloweringPlant(string vid, int vazrast, string habitat, bool spori = true)
        : Plant(vid, vazrast), Habitat(habitat), ImaSpori(spori) {
    }

    void printInfo() const override {
        cout << "Vid: " << Vid << ", Habitat: " << Habitat << ", Spori: " << (ImaSpori ? "Da" : "Ne") << endl;
    }

    void jiznenCikal() override { cout << Vid << " se razmnojava sus spori." << endl; }
};

//  НИВО 2: МЪХ 
class Moss : public NonFloweringPlant {
protected:
    double Debelina;
    string CvqtMux;

public:
    Moss() : NonFloweringPlant(), Debelina(1.5), CvqtMux("Zelen") {}
    Moss(string vid, int vazrast, string habitat, bool spori, double debelina, string cvqt = "Zelen")
        : NonFloweringPlant(vid, vazrast, habitat, spori), Debelina(debelina), CvqtMux(cvqt) {
    }

    void printInfo() const override {
        NonFloweringPlant::printInfo();
        cout << "Mux debelina: " << Debelina << " cm, Cvqt: " << CvqtMux << endl;
    }
};

//  НИВО 2: ПАПРАТ (Допълнителен клас) 
class Fern : public NonFloweringPlant {
private:
    int BroiLista;
public:
    Fern(string vid, int vazrast, int lista = 12)
        : NonFloweringPlant(vid, vazrast, "Vlajni gori", true), BroiLista(lista) {
    }

    void printInfo() const override {
        NonFloweringPlant::printInfo();
        cout << "Broi lista: " << BroiLista << endl;
    }
};

int main() {
    const int n = 4;
    Plant* garden[n] = {
        new Rose("Chervena Roza", 12, "Cherven", 6, true),
        new Moss("Gorski Mux", 5, "Planina", true, 2.5),
        new Fern("Paprat", 8),
        new WildRose("Shipka", 24, 50)
    };

    for (int i = 0; i < n; i++) {
        cout << "--- Obekt " << i + 1 << " ---" << endl;
        garden[i]->printInfo();
        garden[i]->fotosinteza();
        garden[i]->jiznenCikal();
        garden[i]->griji();
        cout << endl;
    }

    for (int i = 0; i < n; i++) {
        delete garden[i];
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
