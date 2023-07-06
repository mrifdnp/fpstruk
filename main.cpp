#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // Untuk system()
#include <queue>   // Untuk queue

using namespace std;

struct Computer {
    int id;
    bool active;
    int timeRemaining;
};

const int MAX_COMPUTERS = 10;

class Warnet {
private:
    queue<Computer> computerQueue; // Queue untuk menyimpan komputer yang aktif
    Computer computers[MAX_COMPUTERS];
    int numComputers;
public:
    Warnet() {
        numComputers = 0;
    }

    void addComputer(int id) {
        if (numComputers >= MAX_COMPUTERS) {
            cout << "Warnet sudah penuh!" << endl;
            return;
        }

        computers[numComputers].id = id;
        computers[numComputers].active = false;
        computers[numComputers].timeRemaining = 0;
        numComputers++;

        cout << "Komputer " << id << " berhasil ditambahkan." << endl;
    }

    void activateOrDeactivateComputer(int id, int time) {
        int index = findComputer(id);
        if (index == -1) {
            cout << "Komputer " << id << " tidak ditemukan." << endl;
            return;
        }

        if (time < 0) {
            cout << "Waktu tidak valid." << endl;
            return;
        }

        if (time == 0) {
            computers[index].active = false;
            computers[index].timeRemaining = 0;
            cout << "Komputer " << id << " dinonaktifkan." << endl;
        } else {
            if (computers[index].active) {
                cout << "Komputer " << id << " sudah aktif." << endl;
                return;
            }

            computers[index].active = true;
            computers[index].timeRemaining = time;

            // Tambahkan komputer ke dalam queue
            computerQueue.push(computers[index]);

            cout << "Komputer " << id << " berhasil diaktifkan untuk " << time << " menit." << endl;
        }
    }

    void tick() {
        if (!computerQueue.empty()) {
            Computer currentComputer = computerQueue.front();
            computerQueue.pop();

            if (currentComputer.active && currentComputer.timeRemaining > 0) {
                cout << "Komputer " << currentComputer.id << ": " << currentComputer.timeRemaining << " menit tersisa." << endl;
                currentComputer.timeRemaining--;
                if (currentComputer.timeRemaining > 0) {
                    computerQueue.push(currentComputer);
                } else {
                    currentComputer.active = false;
                    cout << "Komputer " << currentComputer.id << " dinonaktifkan karena waktu habis." << endl;
                }
            }
        }
    }

    void printStatus() {
        for (int i = 0; i < numComputers; i++) {
            cout << "Komputer " << computers[i].id << ": ";
            if (computers[i].active) {
                cout << "Aktif";
            } else {
                cout << "Non-aktif";
            }
            cout << endl;
        }
    }

    void printBill() {
        ofstream billFile;
        billFile.open("bill.txt"); // Membuka file bill.txt untuk penulisan

        if (!billFile) {
            cout << "Gagal membuka file bill.txt." << endl;
            return;
       ```
        }

        billFile << "========== Bill Warnet ==========" << endl;

        while (!computerQueue.empty()) {
            Computer currentComputer = computerQueue.front();
            computerQueue.pop();

            int playTime = currentComputer.timeRemaining;

            billFile << "Komputer " << currentComputer.id << ": " << playTime << " menit" << endl;
        }

        billFile.close(); // Menutup file bill.txt
        cout << "Bill berhasil dicetak ke dalam file bill.txt" << endl;
    }

private:
    int findComputer(int id) {
        for (int i = 0; i < numComputers; i++) {
            if (computers[i].id == id) {
                return i;
            }
        }
        return -1;
    }
};

int main() {
    Warnet warnet;
    int choice;
    int id, time;

    do {
        system("cls"); // Hapus layar pada setiap iterasi menu
        cout << "======== Menu ========" << endl;
        cout << "1. Tambah Komputer" << endl;
        cout << "2. Aktifkan/Nonaktifkan Komputer" << endl;
        cout << "3. Lihat Waktu" << endl;
        cout << "4. Cek Status Komputer" << endl;
        cout << "5. Cetak Bill" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Masukkan ID komputer: ";
                cin >> id;
                warnet.addComputer(id);
                break;
            case 2:
                cout << "Masukkan ID komputer: ";
                cin >> id;
                cout << "Masukkan waktu (dalam menit, 0 untuk menonaktifkan): ";
                cin >> time;
                warnet.activateOrDeactivateComputer(id, time);
                break;
            case 3:
                warnet.tick();
                break;
            case 4:
                warnet.printStatus();
                break;
            case 5:
                warnet.printBill();
                break;
            case 0:
                cout << "Keluar." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
        cout << endl;

        system("pause"); // Jeda sebelum melanjutkan

    } while (choice != 0);

    return 0;
}

