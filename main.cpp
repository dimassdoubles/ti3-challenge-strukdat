#include <iostream>
using namespace std;

// konstanta nama setiap Role
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
    Player *next = nullptr;
};


Player *new_player = new Player;


struct Role {
    int kapasitas = 0;
    int isi = 0;
    string nama_role;

    Role *next = nullptr;
    
    Player *pemain_pertama = nullptr;
};


struct List {
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


bool is_no_player(Role *r) {
    if (r->pemain_pertama == NULL) {
        return true;
    } 
    return false;
}


bool is_role_full(Role *r) {
    if (r->isi >= r->kapasitas) {
        return true;
    }
    return false;
}


Role* pilih_role(List *l, string nama_role) {
    if (nama_role == STRIKER) {
        return l->head;
    } else if (nama_role == MIDFIELDER) {
        return (l->head)->next;
    } else if (nama_role == DEFENDER) {
        return ((l->head)->next)->next;
    } else if (nama_role == GOALKEEPER) {
        return (((l->head)->next)->next)->next;
    } else {
        return nullptr; 
    }
}


bool player_ada_di_role_v1(List *l, string nama_role, string nama_player) {
    Role *role = pilih_role(l, nama_role);
    Player *cursor = role->pemain_pertama;
    if (!is_no_player(role)) {
        if (cursor->nama_player == nama_player) {
            return true;
        }

        while (cursor->next != NULL) {
            cursor = cursor->next;
            if (cursor->nama_player == nama_player) {
                return true;
            }
        }
    }
    return false;
}


bool is_player_sudah_ada(List *l, string nama) {
    bool player_ada = player_ada_di_role_v1(l, STRIKER, nama) || player_ada_di_role_v1(l, MIDFIELDER, nama) || player_ada_di_role_v1(l, DEFENDER, nama) || player_ada_di_role_v1(l, GOALKEEPER, nama);
    if (player_ada) {
        return true;
    }
    return false;
}


void alokasi_player_baru(string nama) {
    Player *temp = new Player;
    temp->nama_player = nama;

    new_player = temp;
}


void tambah_player(List *l, string nama_role) {
    Role *role = pilih_role(l, nama_role);
    Player *cursor = role->pemain_pertama;
    string nama_player;

    if (is_role_full(role)) {
        cout << "Maaf, role " << nama_role << " sudah penuh" << endl;
    } else {
        cout << "Masukan nama player: "; cin >> nama_player;
        if (is_player_sudah_ada(l, nama_player)) {
            cout << "Maaf, " << nama_player << " sudah terdaftar di list pemain" << endl;
        } else {
            alokasi_player_baru(nama_player);
            new_player->role = nama_role;
            if (is_no_player(role)) {
                role->pemain_pertama = new_player;
            } else {
                while (cursor->next != NULL) {
                    cursor = cursor->next;
                }
                cursor->next = new_player; 
            }

            cout << nama_player << " berhasil ditambahkan ke " << nama_role << endl;
            role->isi ++;
        }
    }
}


void tambah_striker(List *l) {
    tambah_player(l, STRIKER);
}


void tambah_midfielder(List *l) {
    tambah_player(l, MIDFIELDER);
}


void tambah_defender(List *l) {
    tambah_player(l, DEFENDER);
}


void hapus_player_v1(List *l, string nama_role) {
    Role *role = pilih_role(l, nama_role);
    Player *cursor = role->pemain_pertama;
    Player *before;
    Player *after;
    Player *deleted = new Player;
    deleted = nullptr;
    string nama_player;

    if (is_no_player(role)) {
        cout << "Role " << nama_role << " kosong" << endl;
    } else {
        cout << "Masukan nama player: "; cin >> nama_player;
        if (cursor->nama_player == nama_player) {
            role->pemain_pertama = cursor->next;
            deleted = cursor;
        } else {
            while (cursor->next != NULL) {
                before = cursor;
                cursor = cursor->next;
                after = cursor->next;
                if (cursor->nama_player == nama_player) {
                    before->next = after;
                    deleted = cursor;
                    break;
                }
            }

            if (deleted == NULL) {
                cout << nama_player << " tidak ada di role " << nama_role << endl;
            } else {
                delete deleted;
                cout << nama_player << " berhasil dihapus" << endl;
                role->isi --;
            }
        }
    }
}


void hapus_striker(List *l) {
    hapus_player_v1(l, STRIKER);
}


void hapus_midfielder(List *l) {
    hapus_player_v1(l, MIDFIELDER);
}


void hapus_defender(List *l) {
    hapus_player_v1(l, DEFENDER);
}


void subtitusi_player(List *l, string nama_role) {
    Role *role = pilih_role(l, nama_role);
    Player *cursor = role->pemain_pertama;
    Player *before = nullptr;
    Player *deleted = new Player;
    deleted = nullptr;
    Player *after;
    bool is_pemain_pertama_diganti = false;
    string nama_diganti;
    string nama_pengganti;

    cout << "Masukan nama player yang ingin diganti: "; cin >> nama_diganti;
    if (is_no_player(role)) {
        cout << "Role " << nama_role << " kosong" << endl;
    } else {
        if (cursor->nama_player == nama_diganti) {
            is_pemain_pertama_diganti = true;
            after = cursor->next;
            deleted = cursor;
        } else {
            while (cursor->next != NULL) {
                before = cursor;
                cursor = cursor->next;
                after = cursor->next;
                if (cursor->nama_player == nama_diganti) {
                    deleted = cursor;
                    break;
                }
            }
        }

        if (deleted == NULL) {
            cout << "Maaf, " << nama_diganti << " tidak ada di role " << nama_role << endl;
        } else {
            cout << "Masukan nama player pengganti: "; cin >> nama_pengganti;
            if (is_player_sudah_ada(l, nama_pengganti)) {
                cout << "Maaf, " << nama_pengganti << " sudah ada di list pemain" << endl;
            } else {
                alokasi_player_baru(nama_pengganti);
                new_player->role = nama_role;
                if (is_pemain_pertama_diganti) {
                    new_player->next = after;
                    role->pemain_pertama = new_player;
                } else {
                    before->next = new_player;
                    new_player->next = after;
                }

                delete deleted;
            }
        }
    }
}


void subtitusi_striker(List *l) {
    subtitusi_player(l, STRIKER);
}


void subtitusi_midfielder(List* l) {
    subtitusi_player(l, MIDFIELDER);
}


void subtitusi_defender(List *l) {
    subtitusi_player(l, DEFENDER);
}


void tampil_role_v1(List*l, string nama_role) {
    Role *role = pilih_role(l, nama_role);
    Player *cursor = role->pemain_pertama;
    int i = 1;

    if (is_no_player(role)) {
        cout << "Role " << nama_role << " kosong" << endl;
    } else {
        cout << "Daftar pemain di role " << nama_role << ": " << endl;
        cout << i << ". " << cursor->nama_player << endl;
        while (cursor->next != NULL) {
            cursor = cursor->next;
            i ++;
            cout << i << ". " << cursor->nama_player << endl;
        }
    }
}


void tampil_striker(List *l) {
    tampil_role_v1(l, STRIKER);
}


void tampil_midfielder(List *l) {
    tampil_role_v1(l, MIDFIELDER);
}


void tampil_defender(List *l) {
    tampil_role_v1(l, DEFENDER);
}


int tampil_role_v2(Role *r, int urutan_mulai) {
    Player *cursor = r->pemain_pertama;
    if (!is_no_player(r)) {
        cout << urutan_mulai << ". " << cursor->nama_player << " (" << cursor->role << ")" << endl;
        while (cursor->next != NULL) {
            cursor = cursor->next;
            urutan_mulai ++;
            cout << urutan_mulai << ". " << cursor->nama_player << " (" << cursor->role << ")" << endl;
        }
    }

    return urutan_mulai;
}


void tampil_pemain(List *l) {
    int i = 1;
    Role *striker = l->head;
    Role *midfielder = (l->head)->next;
    Role *defender = ((l->head)->next)->next;
    Role *goalkeeper = (((l->head)->next)->next)->next;

    bool is_empty = is_no_player(striker) && is_no_player(midfielder) && is_no_player(defender) && is_no_player(goalkeeper);

    if (is_empty) {
        cout << "Belum ada pemain di list pemain" << endl;
    } else {
        cout << "Daftar nama-nama pemain: " << endl;
        i = tampil_role_v2(striker, i) + 1;
        i = tampil_role_v2(midfielder, i) + 1;
        i = tampil_role_v2(defender, i) + 1;
        i = tampil_role_v2(goalkeeper, i) + 1;
    }
}


void hapus_player(Player *p) {
    Player *deleted = new Player;
    deleted = p;
    delete deleted;
}


void hapus_role(Role *r) {
    Player *cursor = r->pemain_pertama;
    Player *deleted = cursor;
    if (!is_no_player(r)) {
        while (cursor->next != NULL) {
            cursor = cursor->next;
            hapus_player(deleted);
            deleted = cursor;
        }
        hapus_player(deleted);
    }
    r->pemain_pertama = nullptr;
}


void hapus_pemain(List *l) {
    Role *striker = l->head;
    Role *midfielder  = (l->head)->next;
    Role *defender = ((l->head)->next)->next;
    Role *goalkeeper = (((l->head)->next)->next)->next;

    hapus_role(striker);
    hapus_role(midfielder);
    hapus_role(defender);
    hapus_role(goalkeeper);
    
    cout << "Semua pemain sudah dihapus" << endl;
}


bool player_ada_di_role_v2(Role *r, string nama) {
    Player *cursor = r->pemain_pertama;
    if (!is_no_player(r)) {
        if (cursor->nama_player == nama) {
            cout << "Pemain ditemukan, " << cursor->nama_player << " ada di Role " << cursor->role << endl;
            return true;
        }
        while (cursor->next != NULL) {
            cursor = cursor->next;
            if (cursor->nama_player == nama) {
                cout << "Pemain ditemukan, " << cursor->nama_player << " ada di Role " << cursor->role << endl;
                return true;
            }
        }
    }
    return false;
}


void cari_pemain(List *l) {
    Role *striker = pilih_role(l, STRIKER);
    Role *midfielder = pilih_role(l, MIDFIELDER);
    Role *defender = pilih_role(l, DEFENDER);
    Role *goalkeeper = pilih_role(l, GOALKEEPER);
    string nama_player;

    cout << "Masukan nama player: "; cin >> nama_player;

    if (player_ada_di_role_v2(striker, nama_player)) {

    } else if (player_ada_di_role_v2(midfielder, nama_player)) {

    } else if (player_ada_di_role_v2(defender, nama_player)) {

    } else if (player_ada_di_role_v2(goalkeeper, nama_player)) {

    } else {
        cout << nama_player << " tidak ditemukan di role manapun" << endl;
    }
    
}


int main() {
    List strategi1;
    int formasi[3] = {4, 2, 2};
    buat_formasi(&strategi1, formasi);
    cetak_role(&strategi1);

    tambah_striker(&strategi1);
    tambah_midfielder(&strategi1);
    tambah_defender(&strategi1);

    tampil_pemain(&strategi1);
    cari_pemain(&strategi1);
    
    return 0;
}
