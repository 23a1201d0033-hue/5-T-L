#include <iostream>
#include <vector>
using namespace std;

// ===== HÀM NHẬP LỰA CHỌN =====
int nhapLuaChon(int min, int max) {
    int chon;
    while (true) {
        cout << "Chon: ";
        cin >> chon;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Sai dinh dang! Nhap lai!\n";
            continue;
        }

        if (chon >= min && chon <= max)
            return chon;

        cout << "Sai lua chon! Nhap lai!\n";
    }
}

// ================== LỚP CƠ SỞ ==================
class NguoiDung {
protected:
    string username;
    string password;

public:
    NguoiDung(string username = "", string password = "") {
        this->username = username;
        this->password = password;
    }

    virtual ~NguoiDung() {}

    string getUsername() { return this->username; }
    string getPassword() { return this->password; }

    void setPassword(string password) {
        this->password = password;
    }
};

// ================== TÀI KHOẢN ==================
class TaiKhoan : public NguoiDung {
private:
    double soTien;
    double gioChoi;
    bool biKhoa;

public:
    TaiKhoan(string u = "", string p = "") : NguoiDung(u, p) {
        this->soTien = 0;
        this->gioChoi = 0;
        this->biKhoa = false;
    }

    ~TaiKhoan() {}

    double getSoTien() { return this->soTien; }
    void setSoTien(double soTien) {
        this->soTien = soTien;
    }

    bool getTrangThaiKhoa() {
        return this->biKhoa;
    }

    void napTien() {
        cout << "\n=== NAP TIEN ===\n";
        cout << "1. 10k\n2. 20k\n3. 50k\n";
        int chon = nhapLuaChon(1, 3);

        double tien = (chon == 1) ? 10000 :
                      (chon == 2) ? 20000 : 50000;

        this->soTien += tien;
        this->gioChoi += tien / 5000;

        cout << "Nap thanh cong!\n";
    }

    void doiMatKhau() {
        string oldPass, newPass;
        cout << "Nhap mat khau cu: ";
        cin >> oldPass;

        if (oldPass == this->password) {
            cout << "Nhap mat khau moi: ";
            cin >> newPass;
            this->password = newPass;
            cout << "Doi thanh cong!\n";
        } else {
            cout << "Sai mat khau!\n";
        }
    }

    void khoaTaiKhoan() {
        this->biKhoa = true;
        cout << "Tai khoan da bi khoa!\n";
    }

    void hienThi() {
        cout << "User: " << this->username
             << " | Tien: " << this->soTien
             << " | Gio: " << this->gioChoi << endl;
    }
};

// ================== DỊCH VỤ ==================
class DichVu {
private:
    string ten;
    double gia;

public:
    DichVu(string ten = "", double gia = 0) {
        this->ten = ten;
        this->gia = gia;
    }

    string getTen() { return this->ten; }
    double getGia() { return this->gia; }
};

// ================== MÁY ==================
class May {
private:
    int id;
    bool trangThai;

public:
    May(int id = 0) {
        this->id = id;
        this->trangThai = false;
    }

    void batMay() {
        this->trangThai = true;
        cout << "May " << this->id << " DA BAT\n";
    }

    void tatMay() {
        this->trangThai = false;
        cout << "May " << this->id << " DA TAT\n";
    }
};

// ================== SERVER ==================
class Server {
private:
    vector<TaiKhoan*> dsTK;
    vector<DichVu> dsDV;
    vector<May> dsMay;

public:
    Server() {
        for (int i = 1; i <= 5; i++)
            dsMay.push_back(May(i));

        dsDV.push_back(DichVu("Mi tom", 10000));
        dsDV.push_back(DichVu("Nuoc ngot", 5000));
    }

    // 🔥 Destructor giải phóng bộ nhớ
    ~Server() {
        for (int i = 0; i < dsTK.size(); i++) {
            delete dsTK[i];
        }
    }

    // ===== TẠO TK =====
    void taoTK() {
        string u, p;
        cout << "Nhap username: ";
        cin >> u;
        cout << "Nhap password: ";
        cin >> p;

        dsTK.push_back(new TaiKhoan(u, p));
        cout << "Tao thanh cong!\n";
    }

    // ===== ĐĂNG NHẬP =====
    int dangNhap() {
        string u, p;

        cout << "Username: ";
        cin >> u;

        int index = -1;

        for (int i = 0; i < dsTK.size(); i++) {
            if (dsTK[i]->getUsername() == u) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Tai khoan khong ton tai!\n";
            return -1;
        }

        if (dsTK[index]->getTrangThaiKhoa()) {
            cout << "Tai khoan da bi khoa!\n";
            return -1;
        }

        for (int lan = 1; lan <= 3; lan++) {
            cout << "Nhap password (" << lan << "/3): ";
            cin >> p;

            if (p == dsTK[index]->getPassword()) {
                cout << "Dang nhap thanh cong!\n";
                return index;
            }

            cout << "Sai mat khau!\n";
        }

        dsTK[index]->khoaTaiKhoan();
        cout << "Tai khoan bi khoa!\n";
        return -1;
    }

    // ===== DỊCH VỤ =====
    void suDungDV(int idx) {
        cout << "\n=== DICH VU ===\n";
        for (int i = 0; i < dsDV.size(); i++) {
            cout << i + 1 << ". " << dsDV[i].getTen()
                 << " - " << dsDV[i].getGia() << endl;
        }

        int chon = nhapLuaChon(1, dsDV.size());
        double gia = dsDV[chon - 1].getGia();

        if (dsTK[idx]->getSoTien() >= gia) {
            dsTK[idx]->setSoTien(dsTK[idx]->getSoTien() - gia);
            cout << "Da mua " << dsDV[chon - 1].getTen() << endl;
        } else {
            cout << "Khong du tien!\n";
        }
    }

    // ===== KHÓA TK =====
    void khoaTK() {
        string u;
        cout << "Nhap username can khoa: ";
        cin >> u;

        for (int i = 0; i < dsTK.size(); i++) {
            if (dsTK[i]->getUsername() == u) {
                dsTK[i]->khoaTaiKhoan();
                return;
            }
        }

        cout << "Khong tim thay!\n";
    }

    // ===== MÁY =====
    void quanLyMay() {
        cout << "1. Bat may\n2. Tat may\n";
        int chon = nhapLuaChon(1, 2);

        cout << "Nhap ID may: ";
        int id;
        cin >> id;

        if (id >= 1 && id <= dsMay.size()) {
            if (chon == 1)
                dsMay[id - 1].batMay();
            else
                dsMay[id - 1].tatMay();
        }
    }

    // ===== MENU USER =====
    void menuUser(int idx) {
        int chon;
        do {
            cout << "\n=== MENU USER ===\n";
            cout << "1. Nap tien\n";
            cout << "2. Dich vu\n";
            cout << "3. Doi mat khau\n";
            cout << "4. Xem thong tin\n";
            cout << "0. Dang xuat\n";

            chon = nhapLuaChon(0, 4);

            switch (chon) {
                case 1: dsTK[idx]->napTien(); break;
                case 2: suDungDV(idx); break;
                case 3: dsTK[idx]->doiMatKhau(); break;
                case 4: dsTK[idx]->hienThi(); break;
            }

        } while (chon != 0);
    }

    // ===== MENU CHÍNH =====
    void menu() {
        int chon;
        do {
            cout << "\n===== QUAN NET =====\n";
            cout << "1. Tao tai khoan\n";
            cout << "2. Dang nhap\n";
            cout << "3. Quan ly may\n";
            cout << "4. Khoa tai khoan\n";
            cout << "0. Thoat\n";

            chon = nhapLuaChon(0, 4);

            switch (chon) {
                case 1: taoTK(); break;
                case 2: {
                    int idx = dangNhap();
                    if (idx != -1)
                        menuUser(idx);
                    break;
                }
                case 3: quanLyMay(); break;
                case 4: khoaTK(); break;
            }

        } while (chon != 0);
    }
};

// ======== MAIN ============
int main() {
    Server s;
    s.menu();
    return 0;
}
