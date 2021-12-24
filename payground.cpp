#include <iostream>
using namespace std;

bool nama_belum_ada(string list_nama_pemain[12], string nama) {
    for (int i = 0; i<12; i++) {
        if (nama == list_nama_pemain[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    string list_nama_pemain[12];
    list_nama_pemain[0] = "dimas";
    list_nama_pemain[1] = "saputro";

    if (nama_belum_ada(list_nama_pemain, "dimas")) {
        cout << "Nama Belum Ada Di List" << endl;
    } else {
        cout << "Nama Sudah Ada Di List" << endl;
    }
    
    return 0;
}