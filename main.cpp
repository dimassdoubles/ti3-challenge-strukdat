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


bool is_sama(Player *p, string nama_player) {
    if (p->nama_player == nama_player) {
        return true;
    }
    return false;
}


bool cek_striker(List *l, string nama_player) {
    // cout << "cek_striker: ";
    Role *striker = l->head;
    Player *cursor = striker->pemain_pertama;

    if (!is_no_player(striker)) {
        if (cursor->nama_player == nama_player) {
            // cout << nama_player << " ada di role striker" << endl;
            return false;
        }
        while (cursor->next != NULL) {
            cursor = cursor->next;
            if (cursor->nama_player == nama_player) {
                // cout << nama_player << " ada di role striker" << endl;
                return false;
            }

        }
    }

    // cout << nama_player << " tidak ada di role striker" << endl;
    return true;
}


bool cek_midfielder(List *l, string nama_player) {
    Role *midfielder = (l->head)->next;
    Player *cursor = midfielder->pemain_pertama;

    if (!is_no_player(midfielder)) {
        if (cursor->nama_player == nama_player) {
            return false;
        }
        while (cursor->next != NULL) {
            cursor = cursor->next;
            if (cursor->nama_player == nama_player) {
                return false;
            }

        }
    }

    return true;
}


bool cek_defender(List *l, string nama_player) {
    Role *defender = ((l->head)->next)->next;
    Player *cursor = defender->pemain_pertama;

    if (!is_no_player(defender)) {
        if (cursor->nama_player == nama_player) {
            return false;
        }
        while (cursor->next != NULL) {
            cursor = cursor->next;

            if (cursor->nama_player == nama_player) {
                return false;
            }

        }
    }

    return true;
}


bool cek_goalkeeper(List *l, string nama_player) {
    Role *goalkeeper = (((l->head)->next)->next)->next;
    Player *cursor = goalkeeper->pemain_pertama;

    if (!is_no_player(goalkeeper)) {
        if (cursor->nama_player == nama_player) {
            return false;
        }
        while (cursor->next != NULL) {
            cursor = cursor->next;
            if (cursor->nama_player == nama_player) {
                return false;
            }

        }
    }

    return true;
}


bool is_player_ada(List *l, string nama) {
    bool player_tidak_ada = cek_striker(l, nama) && cek_midfielder(l, nama) && cek_defender(l, nama) && cek_goalkeeper(l, nama);
    if (player_tidak_ada) {
        cout << "player tidak ada" << endl;
        return false;
    }
    cout << "player ada" << endl;
    return true;
}


void alokasi_player(string nama) {
    Player *temp = new Player;
    temp->nama_player = nama;

    new_player = temp;
}


void tambah_striker(List *l) {
    string nama;
    Role *striker = l->head;

    if (is_role_full(striker)) {
        cout << "Maaf, role Striker sudah penuh." << endl;
    } else {    
        cout << "Masukan nama player : "; cin >> nama;
        if (is_player_ada(l, nama)) {
            cout << "Maaf, " << nama << " sudah terdaftar di list pemain." << endl;
        } else {
            alokasi_player(nama);
            if (is_no_player(striker)) {
                striker->pemain_pertama = new_player;
            } else {
                Player *cursor = striker->pemain_pertama;
                while (cursor->next != NULL) {
                    cursor = cursor->next;
                }
                cursor->next = new_player;
            }

            cout << nama << " berhasil ditambahkan ke Striker" << endl;
            striker->isi ++;
        }
    }


}


void tambah_midfielder(List *l) {
    string nama;
    Role *midfielder = (l->head)->next;

    if (is_role_full(midfielder)) {
        cout << "Maaf, role Midfielder sudah penuh." << endl;
    } else {
        cout << "Masukan nama player : "; cin >> nama;
        if (is_player_ada(l, nama)) {
            cout << "Maaf, " << nama << " sudah terdaftar di list pemain." << endl;
        } else {
            alokasi_player(nama);
            if (is_no_player(midfielder)) {
                midfielder->pemain_pertama = new_player;
            } else {
                Player *cursor = midfielder->pemain_pertama;
                while (cursor->next != NULL) {
                    cursor = cursor->next;
                }
                cursor->next = new_player;
            }

            cout << nama << " berhasil ditambahkan ke Midfielder" << endl;
            midfielder->isi ++;
        }
    }
}


void tambah_defender(List *l) {
    string nama;
    Role *defender = ((l->head)->next)->next;

    if (is_role_full(defender)) {
        cout << "Maaf, role Defender sudah penuh." << endl;
    } else {
        cout << "Masukan nama player : "; cin >> nama;
        if (is_player_ada(l, nama)) {
            cout << "Maaf, " << nama << " sudah terdaftar di list pemain." << endl;
        } else {
            alokasi_player(nama);
            if (is_no_player(defender)) {
                defender->pemain_pertama = new_player;
            } else {
                Player *cursor = defender->pemain_pertama;
                while (cursor->next != NULL) {
                    cursor = cursor->next;
                }
                cursor->next = new_player;
            }

            cout << nama << " berhasil ditambahkan ke Defender" << endl;
            defender->isi ++;
        }
    }
}


void hapus_striker(List *l) {
    string nama;
    Role *striker = l->head;

    if (is_no_player(striker)) {
        cout << "Role Striker kosong" << endl;
    } else {
        cout << "Masukan nama player: "; cin >> nama;
        Player *cursor = striker->pemain_pertama;
        Player *before;
        Player *after;
        Player *deleted = new Player;
        deleted = nullptr;
        if (cursor->nama_player == nama) {
            deleted = cursor;
        } else {
            while (cursor->next != NULL) {
                before = cursor;
                cursor = cursor->next;
                after = cursor->next;
                if (cursor->nama_player == nama) {
                    deleted = cursor;
                    before->next = after;
                }
            }
        }

        if (deleted == NULL) {
            cout << nama << " tidak ada di role Striker" << endl;
        } else {
            delete deleted;
            cout << nama << " berhasil dihapus" << endl;
            striker->isi --;
        }
    }
}


void hapus_midfielder(List *l) {
    string nama;
    Role *midfielder = (l->head)->next;

    if (is_no_player(midfielder)) {
        cout << "Role Midfielder kosong" << endl;
    } else {
        cout << "Masukan nama player: "; cin >> nama;
        Player *cursor = midfielder->pemain_pertama;
        Player *before;
        Player *after;
        Player *deleted = new Player;
        deleted = nullptr;
        if (cursor->nama_player == nama) {
            deleted = cursor;
        } else {
            while (cursor->next != NULL) {
                before = cursor;
                cursor = cursor->next;
                after = cursor->next;
                if (cursor->nama_player == nama) {
                    deleted = cursor;
                    before->next = after;
                    break;
                }
            }
        }

        if (deleted == NULL) {
            cout << nama << " tidak ada di role Midfielder" << endl;
        } else {
            delete deleted;
            cout << nama << " berhasil dihapus" << endl;
            midfielder->isi --;
        }
    }
}


void hapus_defender(List *l) {
    string nama;
    Role *defender = ((l->head)->next)->next;

    if (is_no_player(defender)) {
        cout << "Role Defender kosong" << endl;
    } else {
        cout << "Masukan nama player: "; cin >> nama;
        Player *cursor = defender->pemain_pertama;
        Player *before;
        Player *after;
        Player *deleted = new Player;
        deleted = nullptr;
        if (cursor->nama_player == nama) {
            deleted = cursor;
        } else {
            while (cursor->next != NULL) {
                before = cursor;
                cursor = cursor->next;
                after = cursor->next;
                if (cursor->nama_player == nama) {
                    deleted = cursor;
                    before->next = after;
                    break;
                }
            }
        }

        if (deleted == NULL) {
            cout << nama << " tidak ada di role Midfielder" << endl;
        } else {
            delete deleted;
            cout << nama << " berhasil dihapus" << endl;
            defender->isi --;
        }
    }
}


void subtitusi_striker(List *l) {
    string nama_diganti;
    string nama_pengganti;
    Role *striker = l->head;
    Player *cursor = striker->pemain_pertama;
    Player *before;
    Player *deleted = new Player;
    deleted = nullptr;
    Player *after;
    cout << "Masukan nama player yang ingin diganti: "; cin >> nama_diganti;

    if (is_no_player(striker)) {
        cout << "Role Striker kosong" << endl;
    } else {
        if (cursor->nama_player == nama_diganti) {
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
    }

    if (deleted == NULL) {
        cout << nama_diganti << " tidak ada di role Striker" << endl;
    } else {
        cout << "Masukan nama player pengganti: "; cin >> nama_pengganti;
        if (is_player_ada(l, nama_pengganti)) {
            cout << "Maaf, player pengganti sudah terdaftar di list pemain" << endl;
        } else {
            delete deleted;
            alokasi_player(nama_pengganti);
            before->next = new_player;
            new_player->next = after;
            cout << "Berhasil mengganti " << nama_diganti << ", dengan " << nama_pengganti << endl;
        }
    }

}


void subtitusi_midfielder(List *l) {
    string nama_diganti;
    string nama_pengganti;
    Role *midfielder = (l->head)->next;
    Player *cursor = midfielder->pemain_pertama;
    Player *before;
    Player *deleted = new Player;
    deleted = nullptr;
    Player *after;
    cout << "Masukan nama player yang ingin diganti: "; cin >> nama_diganti;

    if (is_no_player(midfielder)) {
        cout << "Role Midfielder kosong" << endl;
    } else {
        if (cursor->nama_player == nama_diganti) {
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
    }

    if (deleted == NULL) {
        cout << nama_diganti << " tidak ada di role Midfielder" << endl;
    } else {
        cout << "Masukan nama player pengganti: "; cin >> nama_pengganti;
        if (is_player_ada(l, nama_pengganti)) {
            cout << "Maaf, player pengganti sudah terdaftar di list pemain" << endl;
        } else {
            delete deleted;
            alokasi_player(nama_pengganti);
            before->next = new_player;
            new_player->next = after;
            cout << "Berhasil mengganti " << nama_diganti << ", dengan " << nama_pengganti << endl;
        }
    }

}


void subtitusi_defender(List *l) {
    string nama_diganti;
    string nama_pengganti;
    Role *defender = ((l->head)->next)->next;
    Player *cursor = defender->pemain_pertama;
    Player *before;
    Player *deleted = new Player;
    deleted = nullptr;
    Player *after;
    cout << "Masukan nama player yang ingin diganti: "; cin >> nama_diganti;

    if (is_no_player(defender)) {
        cout << "Role Defender kosong" << endl;
    } else {
        if (cursor->nama_player == nama_diganti) {
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
    }

    if (deleted == NULL) {
        cout << nama_diganti << " tidak ada di role Defender" << endl;
    } else {
        cout << "Masukan nama player pengganti: "; cin >> nama_pengganti;
        if (is_player_ada(l, nama_pengganti)) {
            cout << "Maaf, player pengganti sudah terdaftar di list pemain" << endl;
        } else {
            delete deleted;
            alokasi_player(nama_pengganti);
            before->next = new_player;
            new_player->next = after;
            cout << "Berhasil mengganti " << nama_diganti << ", dengan " << nama_pengganti << endl;
        }
    }

}


void tampil_striker(List *l) {
    Role *striker = l->head;
    Player *cursor = striker->pemain_pertama;
    int i = 1;

    if (is_no_player(striker)) {
        cout << "Role Striker kosong" << endl;
    } else {
        cout << "Daftar pemain di Role Striker: " << endl;
        cout << i << ". " << cursor->nama_player << endl;
        while (cursor->next != NULL) {
            cursor = cursor->next;
            i ++;
            cout << i << ". " << cursor->nama_player << endl;
        }
    }
    
}


void tampil_midfielder(List *l) {
    Role *midfielder = (l->head)->next;
    Player *cursor = midfielder->pemain_pertama;
    int i = 1;

    if (is_no_player(midfielder)) {
        cout << "Role Midfielder kosong" << endl;
    } else {
        cout << "Daftar pemain di Role Midfielder: " << endl;
        cout << i << ". " << cursor->nama_player << endl;
        while (cursor->next != NULL) {
            cursor = cursor->next;
            i ++;
            cout << i << ". " << cursor->nama_player << endl;
        }
    }
    
}


void tampil_defender(List *l) {
    Role *defender = ((l->head)->next)->next;
    Player *cursor = defender->pemain_pertama;
    int i = 1;

    if (is_no_player(defender)) {
        cout << "Role Defender kosong" << endl;
    } else {
        cout << "Daftar pemain di Role Defender: " << endl;
        cout << i << ". " << cursor->nama_player << endl;
        while (cursor->next != NULL) {
            cursor = cursor->next;
            i ++;
            cout << i << ". " << cursor->nama_player << endl;
        }
    }
    
}

int main() {
    List strategi1;
    int formasi[3] = {10, 2, 2};
    buat_formasi(&strategi1, formasi);
    cetak_role(&strategi1);

    // test tambah_striker()
    // tambah_striker(&strategi1);
    // tambah_striker(&strategi1);
    // tambah_striker(&strategi1);

    tampil_striker(&strategi1);


    // // test tambah_midfielder()
    // tambah_midfielder(&strategi1);
    // tambah_midfielder(&strategi1);
    // tambah_midfielder(&strategi1);

    // // test tambah_defender()
    // tambah_defender(&strategi1);
    // tambah_defender(&strategi1);
    // tambah_defender(&strategi1);

    // // test hapus_striker()
    // hapus_striker(&strategi1);

    // // test hapus_midfielder()
    // hapus_midfielder(&strategi1);

    // // test hapus_defender()
    // hapus_defender(&strategi1);

    // test subtitusi_striker()
    // subtitusi_striker(&strategi1);
    
    return 0;
}
