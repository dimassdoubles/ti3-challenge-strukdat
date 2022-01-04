#include <iostream>
using namespace std;

// Konstanta nama setiap role
const string STRIKER = "Striker";
const string MIDFIELDER = "Midfielder";
const string DEFENDER = "Defender";
const string GOALKEEPER = "Goalkeeper";


struct Player {
    string role;
    string nama_player;
    
    Player *prev;
    Player *next = nullptr;
};


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


Player *new_player;


void tambah_role(List *l, string nama, int kapasitas) {
    bool is_empty = l->head == NULL;
    Role *temp =  new Role;
    temp->nama_role = nama;
    temp->kapasitas = kapasitas;
    Role *cursor;
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


void input_formasi(List *l) {
    int kapasitas[3];
    int kuota_pemain = 10;
    int striker;
    int midfielder;
    int defender;
    cout << "Sisa kuota = 10, Masukan jumlah Striker    : "; cin >> striker;
    kuota_pemain -= striker;
    cout << "Sisa kuota =  " << kuota_pemain << ", Masukan jumlah Midfielder : "; cin >> midfielder;
    kuota_pemain -= midfielder;
    cout << "Sisa kuota =  " << kuota_pemain << ", Masukan jumlah Defender   : "; cin >> defender;

    kapasitas[0] = striker;
    kapasitas[1] = midfielder;
    kapasitas[2] = defender;

    buat_formasi(l, kapasitas);
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
    }
    return nullptr; 
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


bool player_ada_di_role_v2(Role *r, string nama_player) {
    Player *cursor = r->pemain_pertama;
    if (!is_no_player(r)) {
        if (cursor->nama_player == nama_player) {
            cout << "Pemain ditemukan, " << cursor->nama_player << " ada di Role " << cursor->role << endl;
            return true;
        }
        while (cursor->next != NULL) {
            cursor = cursor->next;
            if (cursor->nama_player == nama_player) {
                cout << "Pemain ditemukan, " << cursor->nama_player << " ada di Role " << cursor->role << endl;
                return true;
            }
        }
    }
    return false;
}


bool is_player_sudah_ada(List *l, string nama_player) {
    bool player_ada = player_ada_di_role_v1(l, STRIKER, nama_player) || player_ada_di_role_v1(l, MIDFIELDER, nama_player) || player_ada_di_role_v1(l, DEFENDER, nama_player) || player_ada_di_role_v1(l, GOALKEEPER, nama_player);
    if (player_ada) {
        return true;
    }
    return false;
}


void alokasi_player_baru(string nama_player) {
    Player *temp = new Player;
    temp->nama_player = nama_player;

    new_player = temp;
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
                new_player->prev = nullptr;
                role->pemain_pertama = new_player;
            } else {
                while (cursor->next != NULL) {
                    cursor = cursor->next;
                }
                new_player->prev = cursor;
                cursor->next = new_player; 
            }

            cout << nama_player << " berhasil ditambahkan ke " << nama_role << endl;
            role->isi ++;
        }
    }
}


void hapus_player_v1(List *l, string nama_role) {
    Role *role = pilih_role(l, nama_role);
    Player *cursor = role->pemain_pertama;
    Player *deleted = nullptr;
    string nama_player;

    if (is_no_player(role)) {
        cout << "Role " << nama_role << " kosong" << endl;
    } else {
        cout << "Masukan nama player: "; cin >> nama_player;
        if (cursor->nama_player == nama_player) {
            (cursor->next)->prev = nullptr;
            role->pemain_pertama = cursor->next;
            deleted = cursor;
        } else {
            cursor = cursor->next;
            while (cursor->next != NULL) {
                if (cursor->nama_player == nama_player) {
                    (cursor->prev)->next = cursor->next;
                    (cursor->next)->prev = cursor->prev;
                    deleted = cursor;
                    break;
                }
                cursor = cursor->next;
            }
            if (cursor->nama_player == nama_player) {
                    (cursor->prev)->next = cursor->next;
                    deleted = cursor;
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


void hapus_player_v2(Player *p) {
    Player *deleted = p;
    delete deleted;
}


void hapus_role(Role *r) {
    Player *cursor = r->pemain_pertama;
    Player *deleted = cursor;
    if (!is_no_player(r)) {
        while (cursor->next != NULL) {
            cursor = cursor->next;
            hapus_player_v2(deleted);
            deleted = cursor;
        }
        hapus_player_v2(deleted);
    }
    r->isi = 0;
    r->pemain_pertama = nullptr;
}


void subtitusi_player(List *l, string nama_role) {
    Role *role = pilih_role(l, nama_role);
    Player *cursor = role->pemain_pertama;
    Player *deleted = nullptr;
    bool is_pemain_pertama_diganti = false;
    bool is_pemain_terakhir_diganti = false;
    string nama_diganti;
    string nama_pengganti;

    cout << "Masukan nama player yang ingin diganti: "; cin >> nama_diganti;
    if (is_no_player(role)) {
        cout << "Role " << nama_role << " kosong" << endl;
    } else {
        if (cursor->nama_player == nama_diganti) {
            is_pemain_pertama_diganti = true;
            deleted = cursor;
        } else {
            cursor = cursor->next;
            while (cursor->next != NULL) {
                if (cursor->nama_player == nama_diganti) {
                    deleted = cursor;
                    break;
                }
                cursor = cursor->next;
            }
            if (cursor->nama_player == nama_diganti) {
                    is_pemain_terakhir_diganti = true;
                    deleted = cursor;
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
                    new_player->prev = nullptr;
                    new_player->next = deleted->next;
                    (deleted->next)->prev = new_player;
                    role->pemain_pertama = new_player;
                } else if (is_pemain_terakhir_diganti) {
                    new_player->prev = deleted->prev;
                    (deleted->prev)->next = new_player;
                } else {
                    new_player->prev = deleted->prev;
                    new_player->next = deleted->next;
                    (deleted->prev)->next = new_player;
                    (deleted->next)->prev = new_player;
                }

                delete deleted;

                cout << "Berhasil mengganti " << nama_diganti << " dengan " << nama_pengganti << endl;
            }
        }
    }
}


// FUNGSI WAJIB ------------------------------------------
void tambah_striker(List *l) {
    tambah_player(l, STRIKER);
}


void tambah_midfielder(List *l) {
    tambah_player(l, MIDFIELDER);
}


void tambah_defender(List *l) {
    tambah_player(l, DEFENDER);
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


void subtitusi_striker(List *l) {
    subtitusi_player(l, STRIKER);
}


void subtitusi_midfielder(List* l) {
    subtitusi_player(l, MIDFIELDER);
}


void subtitusi_defender(List *l) {
    subtitusi_player(l, DEFENDER);
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
        tampil_role_v2(goalkeeper, i);
    }
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


void pilih_menu(List *l) {
    int pilihan;
    cout << "\nMasukan pilihan (1 - 15): "; cin >> pilihan;

    if (pilihan == 1) {
        cout << "TAMBAH STRIKER -------------" << endl;
        tambah_striker(l);
    } else if(pilihan == 2) {
        cout << "TAMBAH MIDFIELDER ----------" << endl;
        tambah_midfielder(l);
    } else if(pilihan == 3) {
        cout << "TAMBAH DEFENDER ------------" << endl;
        tambah_defender(l);
    } else if(pilihan == 4) {
        cout << "HAPUS STRIKER --------------" << endl;
        hapus_striker(l);
    } else if(pilihan == 5) {
        cout << "HAPUS MIDFIELDER -----------" << endl;
        hapus_midfielder(l);
    } else if(pilihan == 6) {
        cout << "HAPUS DEFENDER -------------" << endl;
        hapus_defender(l);
    } else if(pilihan == 7) {
        cout << "SUBTITUSI STRIKER ----------" << endl;
        subtitusi_striker(l);
    } else if(pilihan == 8) {
        cout << "SUBTITUSI MIDFIELDER -------" << endl;
        subtitusi_midfielder(l);
    } else if(pilihan == 9) {
        cout << "SUBTITUSI DEFENDER ---------" << endl;
        subtitusi_defender(l);
    } else if(pilihan == 10) {
        cout << "TAMPIL STRIKER -------------" << endl;
        tampil_striker(l);
    } else if(pilihan == 11) {
        cout << "TAMPIL MIDFIELDER ----------" << endl;
        tampil_midfielder(l);
    } else if(pilihan == 12) {
        cout << "TAMPIL DEFENDER ------------" << endl;
        tampil_defender(l);
    } else if(pilihan == 13) {
        cout << "TAMPIL PEMAIN --------------" << endl;
        tampil_pemain(l);
    } else if(pilihan == 14) {
        cout << "HAPUS PEMAIN ---------------" << endl;
        hapus_pemain(l);
    } else if(pilihan == 15) {
        cout << "CARI PEMAIN ----------------" << endl;
        cari_pemain(l);
    } else {
        cout << "Pilihan tidak valid !";
    }
}

int main() {
    List *strategi = new List;

    cout << "INPUT FORMASI --------------" << endl;
    input_formasi(strategi);
    // cetak_role(strategi);
    cout << "\nDAFTAR MENU ----------------" << endl;
    cout << " 1. Tambah Striker\n 2. Tambah Midfielder\n 3. Tambah Defender" << endl;
    cout << " 4. Hapus Striker\n 5. Hapus Midfielder\n 6. Hapus Defender" << endl;
    cout << " 7. Subtitusi Striker\n 8. Subtitusi Midfielder\n 9. Subtitusi Defender" << endl;
    cout << "10. Tampil Striker\n11. Tampil Midfielder\n12. Tampil Defender" << endl;
    cout << "13. Tampil Pemain\n14. Hapus Pemain\n15. Cari Pemain" << endl;

    while (true) {
        pilih_menu(strategi);
    }
    cout << "Program selesai" << endl;

    return 0;
}
