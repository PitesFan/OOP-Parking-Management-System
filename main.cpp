#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class Vehicul {
protected:
    string tip;
    string numarInmatriculare;
    int oraIntrare;
    int minutIntrare;
    int oraIesire;
    int minutIesire;
    int minutDiferenta;
    int oraDiferenta;

public:
    Vehicul(string t, string nr, int oraOut, int minOut, int oraIn, int minIn) {
        tip = t;
        numarInmatriculare = nr;
        oraIesire = oraOut;
        minutIesire = minOut;
        oraIntrare = oraIn;
        minutIntrare = minIn;
    }

    virtual ~Vehicul() {
        cout<<"Distruge obiectul: "<<tip<<endl;
    }

    void parkingTime() {
        int mOut = minutIesire;
        int oraOut = oraIesire;
        if (minutIntrare > mOut) {
            --oraOut;
            mOut += 60;
        }
        minutDiferenta = mOut - minutIntrare;
        oraDiferenta = oraOut - oraIntrare;
    }

    virtual int tarif() {
        int tarif = 0;
        return tarif;
    }

    void getData() {
        cout << "Tip: " << tip << endl << "Numar inmatriculare: " << numarInmatriculare << endl << "Ora intrare: ora "
                << oraIntrare <<
                " si " << minutIntrare << " minute" << endl << "Ora iesire: ora " << oraIesire << " si " << minutIesire
                << " minute" << endl << "Timp parcare: " <<
                oraDiferenta << " ore " << minutDiferenta << " minute" << endl;
    }
};

class Masina : public Vehicul {
public:
    Masina(string t, string nr, int oraOut, int minOut, int oraIn, int minIn) : Vehicul(
        t, nr, oraOut, minOut, oraIn, minIn) {
    }

    ~Masina () override {
        cout<<"Distruge obiectul: "<<tip<<endl;
    }

    int tarif() override {
        int tarif = 0;
        int pretOra = 5;

        if (minutDiferenta > 0) {
            tarif = (pretOra * minutDiferenta) / 60;
        }

        tarif += oraDiferenta * pretOra;
        return tarif;
    }
};

class Motocicleta : public Vehicul {
public:
    Motocicleta(string t, string nr, int oraOut, int minOut, int oraIn,
                int minIn) : Vehicul(t, nr, oraOut, minOut, oraIn, minIn) {
    }

    ~Motocicleta() override{
        cout<<"Distruge obiectul: "<<tip<<endl;
    }

    int tarif() override {
        int tarif = 0;
        int pretOra = 3;

        if (minutDiferenta > 0) {
            tarif = (pretOra * minutDiferenta) / 60;
        }

        tarif += oraDiferenta * pretOra;

        return tarif;
    }
};

class Camion : public Vehicul {
public:
    Camion(string t, string nr, int oraOut, int minOut, int oraIn,
           int minIn) : Vehicul(t, nr, oraOut, minOut, oraIn, minIn) {
    }

    ~Camion() override{
        cout<<"Distruge obiectul: "<<tip<<endl;
    }

    int tarif() override {
        int tarif = 0;
        int pretOra = 10;

        if (minutDiferenta > 0) {
            tarif = (pretOra * minutDiferenta) / 60;
        }

        tarif += oraDiferenta * pretOra;

        return tarif;
    }
};

class Bicicleta : public Vehicul {
public:
    Bicicleta(string t, string nr, int oraOut, int minOut, int oraIn,
              int minIn) : Vehicul(t, nr, oraOut, minOut, oraIn, minIn) {
    }

    ~Bicicleta() override{
        cout<<"Distruge obiectul: "<<tip<<endl;
    }

    int tarif() override {
        int tarif = 0;
        int pretOra = 2;

        if (minutDiferenta > 0) {
            tarif = (pretOra * minutDiferenta) / 60;
        }

        tarif += oraDiferenta * pretOra;
        tarif -= 4;

        if (oraDiferenta < 2) {
            tarif = 0;
        }

        return tarif;
    }
};

int main() {
    Vehicul *vehicule[10];
    string tip;
    string numarInmatriculare;
    int oraIntrare;
    int minutIntrare;
    int oraIesire;
    int minutIesire;

    ifstream fin("database.txt");
    int n;
    fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> tip;
        fin >> numarInmatriculare;
        fin >> oraIntrare;
        fin >> minutIntrare;
        fin >> oraIesire;
        fin >> minutIesire;

        if (tip == "Masina") {
            vehicule[i] = new Masina(tip, numarInmatriculare, oraIesire, minutIesire, oraIntrare, minutIntrare);
        }

        if (tip == "Motocicleta") {
            vehicule[i] = new Motocicleta(tip, numarInmatriculare, oraIesire, minutIesire, oraIntrare, minutIntrare);
        }

        if (tip == "Camion") {
            vehicule[i] = new Camion(tip, numarInmatriculare, oraIesire, minutIesire, oraIntrare, minutIntrare);
        }

        if (tip == "Bicicleta") {
            vehicule[i] = new Bicicleta(tip, numarInmatriculare, oraIesire, minutIesire, oraIntrare, minutIntrare);
        }
        vehicule[i]->parkingTime();
    }
    fin.close();

    for (int i = 0; i < n; i++) {
        vehicule[i]->getData();
        cout << "Tarif: " << vehicule[i]->tarif() << endl;
    }

    for (int i = 0; i < n; ++i) {
        delete vehicule[i];
    }

    return 0;
}
