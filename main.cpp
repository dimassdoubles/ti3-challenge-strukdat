#include <iostream>
using namespace std;

// konstanta nama setiap Role`
string STRIKER = "Striker";
string MIDFIELDER = "Midfielder";
string DEFENDER = "Defender";
string GOALKEEPER = "Goalkeeper";

struct Player {
    string role;
    string nama_player;
    
    // player baru akan selalu ditambahkan ke bagian belakang
    // maka, setiap Player baru yang dibuat
    // setelahnya tidak ada lagi Player lain
    // oleh karena itu kita buat null pointer (next)
    // tidak menunjuk ke manapun 
    Player *next;
};

struct Role {
    int kapasitas = 0;
    int isi = 0;
    string nama_role;

    // karena insert belakang
    Role *next = nullptr;
    
    // kondisi awal Role yang baru dibuat
    // adalah belum memiliki list pemain
    // karena tidak ada pemain yang ada di Role tersebut
    // kita membuat null pointer (pemain_pertama)
    // tidak menunjuk ke manapun
    Player *pemain_pertama = nullptr;

};


struct List {
    // kondisi awal List yang baru dibuat
    // adalah belum memiliki list Role
    // karena tidak ada Role yang ada di List
    // maka pointer head tidak menunjuk kemanapun
    Role *head = nullptr;
};

void tambah_role(List *l, string nama, int kapasitas) {
    bool is_empty = l->head == NULL;
    Role *temp =  new Role;
    temp->nama_role = nama;
    temp->kapasitas = kapasitas;
    Role *cursor = new Role;
    if (is_empty) {
        l->head = temp;
    } else {
        cursor = l->head;
        while (cursor->next != NULL) {
            cursor = cursor->next;
        }
        cursor->next = temp;
    }
}

void cetak_role(List* l) {
    Role *cursor = new Role;
    cursor = l->head;
    if (cursor != NULL) {
        // cout << cursor->nama_role << endl;
        while (cursor->next != NULL) {
            cout << cursor->nama_role << " --> ";
            cursor = cursor->next;
        }
        cout << cursor->nama_role << endl;
    }
}

void buat_formasi(List *l, int kapasitas[3]) {
    tambah_role(l, STRIKER, kapasitas[0]);
    tambah_role(l, MIDFIELDER, kapasitas[1]);
    tambah_role(l, DEFENDER, kapasitas[2]);

    // kapasitas goalkeeper selalu 1
    tambah_role(l, GOALKEEPER, 1);
}


int main() {
    List strategi1;
    int formasi[3] = {4, 3, 3};
    buat_formasi(&strategi1, formasi);
    cetak_role(&strategi1);

    return 0;
}
