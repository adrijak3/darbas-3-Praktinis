#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
struct patiekalas
{
    string pavadinimas;
    double kaina;
};
void getData(patiekalas sarasas[], int &kiekis);
void showMenu(patiekalas sarasas[], int kiekis);
void spausdinimas(patiekalas sarasas[], int kiekiai[], int kiekis);

int main() {
    patiekalas sarasas[20];
    int kiekis = 0;
    int kiekiai[20] = {0};
    getData(sarasas, kiekis);

    while (true) {
        cout << "\nKa norite daryti?" << endl;
        cout << "1 - Rinktis patiekala" << endl;
        cout << "2 - Baigti ir gauti saskaita" << endl;
        cout << "Pasirinkimas: ";

        int veiksmas;
        cin >> veiksmas;

        if (veiksmas == 2) {
            break;
        }

        switch (veiksmas) {
            case 1:
                showMenu(sarasas, kiekis);
                int nr, n;
                cout << "irasykite patiekalo numeri: ";
                cin >> nr;
                if (nr > 0 && nr <= kiekis) {
                    cout << "Kiek porciji norite? ";
                    cin >> n;
                    kiekiai[nr - 1] += n;
                    cout << "Uzsakyta!" << endl;
                } else {
                    cout << "Tokio patiekalo nera:(" << endl;
                }
                break;

            default:
                cout << "Klaida" << endl;
                break;
        }
    }

    spausdinimas(sarasas, kiekiai, kiekis);

    return 0;
}

void getData(patiekalas sarasas[], int &kiekis) {
    ifstream fd("menu.txt");
    if (!fd) {
        cout << "Nera meniu" << endl;
        return;
    }

    kiekis = 0;
    string pav;
    double k;

    while (true) {
        if (!getline(fd, pav)) break;
        if (pav == "") break;

        fd >> k;
        fd.ignore(1000, '\n');

        sarasas[kiekis].pavadinimas = pav;
        sarasas[kiekis].kaina = k;
        kiekis++;
    }

    fd.close();
}
void showMenu(patiekalas sarasas[], int kiekis) {
    cout << "\nSiandienos meniu:" << endl;
    for (int i = 0; i < kiekis; i++) {
        cout << i + 1 << ". " << sarasas[i].pavadinimas << " - " << fixed << setprecision(2) << sarasas[i].kaina << "eur" << endl;
    }
}

void spausdinimas(patiekalas sarasas[], int kiekiai[], int kiekis) {
    ofstream fr("kvitas.txt");
    double suma = 0;

    cout << "\n--- SASKAITA ---" << endl;
    fr << "--- SASKAITA ---" << endl;

    for (int i = 0; i < kiekis; i++) {
        if (kiekiai[i] > 0) {
            double tarpine = kiekiai[i] * sarasas[i].kaina;
            suma += tarpine;
            cout << kiekiai[i] << " vnt. " << sarasas[i].pavadinimas << " : " << fixed << setprecision(2) << tarpine << " Eur" << endl;
            fr << kiekiai[i] << " vnt. " << sarasas[i].pavadinimas << " : " << fixed << setprecision(2) << tarpine << " Eur" << endl;
        }
    }

    double pvm = suma * 0.21;
    double viso = suma + pvm;

    cout << "\nMokesciai: " << pvm << " Eur" << endl;
    cout << "Iš viso: " << viso << " Eur" << endl;

    fr << "\nMokesciai: " << pvm << " Eur" << endl;
    fr << "Is viso: " << viso << " Eur" << endl;

    fr.close();
    cout << "\nSkanaus!" << endl;
}
