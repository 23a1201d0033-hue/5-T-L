#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>
using namespace std;

//Set gia may
const double GIA_LOAI_1 = 8000;  
const double GIA_LOAI_2 = 10000; 
const double GIA_LOAI_3 = 15000; 

// Ham lua chon
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

string getCurrentTime() {
    time_t now = time(0);
    char* dt = ctime(&now);
    return string(dt);
}

bool nhapSoNguyen(const string &thongBao, int &giaTri) {
    cout << thongBao;
    cin >> giaTri;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Sai dinh dang so nguyen!\n";
        return false;
    }
    return true;
}

bool nhapSoThuc(const string &thongBao, double &giaTri) {
    cout << thongBao;
    cin >> giaTri;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Sai dinh dang so!\n";
        return false;
    }
    return true;
}

//Lop nguoi dung
class NguoiDung {
protected:
    string username;
    string password;
    string hoTen;
    string sdt;

public:
    NguoiDung(string username = "", string password = "", string hoTen = "", string sdt = "") {
        this->username = username;
        this->password = password;
        this->hoTen = hoTen;
        this->sdt = sdt;
    }

    virtual ~NguoiDung() {}

    string getUsername() { return this->username; }
    string getPassword() { return this->password; }
    string getHoTen() { return this->hoTen; }
    string getSdt() { return this->sdt; }

    void setPassword(string password) { this->password = password; }
    void setHoTen(string hoTen) { this->hoTen = hoTen; }
    void setSdt(string sdt) { this->sdt = sdt; }

    virtual void hienThiThongTin() {
        cout << "Username: " << username << endl;
        cout << "Ho ten: " << hoTen << endl;
        cout << "SDT: " << sdt << endl;
    }
};

//lop Tai khoan
class TaiKhoan : public NguoiDung {
private:
    double soTien;
    double gioChoi;
    bool biKhoa;
    vector<string> lichSuGiaoDich;

public:
    TaiKhoan(string u = "", string p = "", string hoTen = "", string sdt = "") 
        : NguoiDung(u, p, hoTen, sdt) {
        this->soTien = 0;
        this->gioChoi = 0;
        this->biKhoa = false;
    }

    ~TaiKhoan() {}

    double getSoTien() { return this->soTien; }
    double getGioChoi() { return this->gioChoi; }
    bool getTrangThaiKhoa() { return this->biKhoa; }

    void setSoTien(double soTien) { this->soTien = soTien; }
    void setGioChoi(double gioChoi) { this->gioChoi = gioChoi; }

    void themLichSu(string giaoDich) {
        lichSuGiaoDich.push_back(giaoDich);
    }

    void xemLichSu() {
        cout << "\n=== LICH SU GIAO DICH ===\n";
        if (lichSuGiaoDich.empty()) {
            cout << "Chua co giao dich nao!\n";
            return;
        }
        for (int i = 0; i < lichSuGiaoDich.size(); i++) {
            cout << i + 1 << ". " << lichSuGiaoDich[i] << endl;
        }
    }

    void napTien() {
        cout << "\n=== NAP TIEN ===\n";
        cout << "1. 10.000 VND\n2. 20.000 VND\n3. 50.000 VND\n";
        cout << "4. 100.000 VND\n5. Nhap so tien khac\n";
        cout << "0. Tro ve\n";
        
        int chon = nhapLuaChon(0, 5);
        if (chon == 0) {
            cout << "Da tro ve menu user.\n";
            return;
        }

        double tien = 0;

        switch (chon) {
            case 1: tien = 10000; break;
            case 2: tien = 20000; break;
            case 3: tien = 50000; break;
            case 4: tien = 100000; break;
            case 5:
                cout << "Nhap so tien: ";
                cin >> tien;
                break;
        }

        if (tien > 0) {
            this->soTien += tien;

            string lichSu = "Nap " + to_string((int)tien) + " VND - So du: " + to_string((int)soTien);
            themLichSu(lichSu);
            
            cout << "Nap thanh cong! So du hien tai: " << soTien << " VND\n";
        } else {
            cout << "So tien khong hop le!\n";
        }
    }

    void doiMatKhau() {
        cout << "\n=== DOI MAT KHAU ===\n";
        cout << "1. Tiep tuc doi mat khau\n";
        cout << "0. Tro ve\n";

        int luaChon = nhapLuaChon(0, 1);
        if (luaChon == 0) {
            cout << "Da tro ve.\n";
            return;
        }

        string oldPass, newPass;
        cout << "Nhap mat khau cu: ";
        cin >> oldPass;

        if (oldPass == this->password) {
            cout << "Nhap mat khau moi: ";
            cin >> newPass;
            this->password = newPass;
            themLichSu("Doi mat khau thanh cong");
            cout << "Doi mat khau thanh cong!\n";
        } else {
            cout << "Sai mat khau!\n";
        }
    }

    void khoaTaiKhoan() {
        this->biKhoa = true;
    }

    void moKhoaTaiKhoan() {
        this->biKhoa = false;
    }

    void hienThi() {
        cout << "\n=== THONG TIN TAI KHOAN ===\n";
        cout << "Username: " << this->username << endl;
        cout << "Ho ten: " << this->hoTen << endl;
        cout << "SDT: " << this->sdt << endl;
        cout << "So tien: " << fixed << setprecision(0) << this->soTien << " VND\n";
        cout << "Gio choi: " << fixed << setprecision(1) << this->gioChoi << " gio\n";
        cout << "Trang thai: " << (biKhoa ? "Bi khoa" : "Hoat dong") << endl;
    }

    void hienThiThongTin() override {
        hienThi();
    }
};

//lop dich vu
class DichVu {
private:
    string maDV;
    string ten;
    double gia;
    int soLuong;

public:
    DichVu(string maDV = "", string ten = "", double gia = 0, int soLuong = 100) {
        this->maDV = maDV;
        this->ten = ten;
        this->gia = gia;
        this->soLuong = soLuong;
    }

    string getMaDV() { return this->maDV; }
    string getTen() { return this->ten; }
    double getGia() { return this->gia; }
    int getSoLuong() { return this->soLuong; }

    void setGia(double gia) { this->gia = gia; }
    void setSoLuong(int soLuong) { this->soLuong = soLuong; }

    void giamSoLuong() { if (soLuong > 0) soLuong--; }
    void tangSoLuong() { soLuong++; }

    void hienThi() {
        cout << left << setw(10) << maDV 
             << setw(20) << ten 
             << setw(15) << gia 
             << setw(10) << soLuong << endl;
    }
};

//Lop May
enum class TrangThaiMay { Trong, DangChoi, BaoTri };

class May {
private:
    int id;
    TrangThaiMay trangThai;
    string tenMay;
    double giaTheoGio;

public:
    May(int id = 0, string tenMay = "", double giaTheoGio = 5000) {
        this->id = id;
        this->tenMay = tenMay;
        this->giaTheoGio = giaTheoGio;
        this->trangThai = TrangThaiMay::Trong;
    }

    int getId() { return this->id; }
    TrangThaiMay getTrangThai() { return this->trangThai; }
    string getTenMay() { return this->tenMay; }
    double getGiaTheoGio() { return this->giaTheoGio; }

    void setTrangThai(TrangThaiMay tt) { this->trangThai = tt; }
    void setGiaTheoGio(double gia) { this->giaTheoGio = gia; }

    string getTrangThaiString() {
        switch (trangThai) {
            case TrangThaiMay::Trong: return "Trong";
            case TrangThaiMay::DangChoi: return "Dang choi";
            case TrangThaiMay::BaoTri: return "Bao tri";
        }
        return "Unknown";
    }

    void batMay() {
        if (trangThai == TrangThaiMay::Trong) {
            trangThai = TrangThaiMay::DangChoi;
            cout << "May " << id << " (" << tenMay << ") DA BAT\n";
        } else if (trangThai == TrangThaiMay::BaoTri) {
            cout << "May dang bao tri, khong the bat!\n";
        } else {
            cout << "May dang duoc su dung!\n";
        }
    }

    void tatMay() {
        trangThai = TrangThaiMay::Trong;
        cout << "May " << id << " DA TAT\n";
    }

    void datBaoTri() {
        trangThai = TrangThaiMay::BaoTri;
        cout << "May " << id << " da duoc dat che do bao tri!\n";
    }

    void hienThi() {
        cout << left << setw(5) << id 
             << setw(15) << tenMay 
             << setw(15) << getTrangThaiString() 
             << setw(10) << giaTheoGio << endl;
    }
};

//Lop Hoa don
class HoaDon {
private:
    string maHD;
    string username;
    double tongTien;
    string ngayLap;
    vector<pair<string, double>> chiTiet;

public:
    HoaDon(string maHD = "", string username = "") {
        this->maHD = maHD;
        this->username = username;
        this->tongTien = 0;
        this->ngayLap = getCurrentTime();
    }

    void themChiTiet(string tenDV, double gia) {
        chiTiet.push_back({tenDV, gia});
        tongTien += gia;
    }

    void hienThi() {
        cout << "\n=== HOA DON ===\n";
        cout << "Ma HD: " << maHD << endl;
        cout << "Khach hang: " << username << endl;
        cout << "Ngay lap: " << ngayLap << endl;
        cout << "-------------------\n";
        for (auto &ct : chiTiet) {
            cout << ct.first << ": " << ct.second << " VND\n";
        }
        cout << "-------------------\n";
        cout << "Tong cong: " << tongTien << " VND\n";
    }

    double getTongTien() { return tongTien; }
};

//lop Server
class Server {
private:
    vector<TaiKhoan*> dsTK;
    vector<DichVu> dsDV;
    vector<May> dsMay;
    vector<HoaDon> dsHoaDon;
    int soMayDangChoi;

public:
    Server() {
        soMayDangChoi = 0;
        khoiTaoTaiKhoanDemo();
        khoiTaoMay();
        khoiTaoDichVu();
    }

    void khoiTaoTaiKhoanDemo() {
        TaiKhoan *demo = new TaiKhoan("demo", "demo123", "Tai Khoan Demo", "0900000000");
        demo->setSoTien(20000);
        demo->themLichSu("Khoi tao tai khoan demo - So du: 20000 VND");
        dsTK.push_back(demo);
    }

    void khoiTaoMay() {
        dsMay.push_back(May(1, "PC Gaming 1", GIA_LOAI_1));
        dsMay.push_back(May(2, "PC Gaming 2", GIA_LOAI_1));
        dsMay.push_back(May(3, "PC Gaming 3", GIA_LOAI_1));
        dsMay.push_back(May(4, "PC Van Phong 1", GIA_LOAI_2));
        dsMay.push_back(May(5, "PC Van Phong 2", GIA_LOAI_2));
        dsMay.push_back(May(6, "PC Van Phong 3", GIA_LOAI_2));
        dsMay.push_back(May(7, "VIP Room 1", GIA_LOAI_3));
        dsMay.push_back(May(8, "VIP Room 2", GIA_LOAI_3));
    }

    void khoiTaoDichVu() {
        dsDV.push_back(DichVu("DV001", "Mi tom", 10000, 50));
        dsDV.push_back(DichVu("DV002", "Nuoc ngot", 5000, 100));
        dsDV.push_back(DichVu("DV003", "Cafe", 15000, 30));
        dsDV.push_back(DichVu("DV004", "Banh my", 8000, 20));
        dsDV.push_back(DichVu("DV005", "Tra sua", 20000, 25));
        dsDV.push_back(DichVu("DV006", "Khoai tay", 15000, 30));
    }

    ~Server() {
        for (int i = 0; i < dsTK.size(); i++) {
            delete dsTK[i];
        }
    }

    //ham tao tai khoan
    void taoTK() {
        string u, p, hoTen, sdt;
        cout << "\n=== TAO TAI KHOAN ===\n";
        cout << "Nhap username: ";
        cin >> u;

        //check user
        for (auto tk : dsTK) {
            if (tk->getUsername() == u) {
                cout << "Username da ton tai!\n";
                return;
            }
        }

        cout << "Nhap password: ";
        cin >> p;
        cout << "Nhap ho ten: ";
        cin.ignore();
        getline(cin, hoTen);
        cout << "Nhap SDT: ";
        cin >> sdt;

        dsTK.push_back(new TaiKhoan(u, p, hoTen, sdt));
        cout << "Tao tai khoan thanh cong!\n";
    }

    //Ham dang nhap
    int dangNhap() {
        string u, p;

        cout << "\n=== DANG NHAP ===\n";
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
                cout << "Dang nhap thanh cong! Xin chao " << dsTK[index]->getHoTen() << "!\n";
                return index;
            }

            cout << "Sai mat khau!\n";
        }

        dsTK[index]->khoaTaiKhoan();
        cout << "Tai khoan bi khoa vi nhap sai qua 3 lan!\n";
        return -1;
    }

    //ham su dung dich vu
    void suDungDV(int idx) {
        if (dsDV.empty()) {
            cout << "Danh sach dich vu dang rong!\n";
            return;
        }

        cout << "\n=== DICH VU ===\n";
        cout << left << setw(10) << "Ma DV" 
             << setw(20) << "Ten" 
             << setw(15) << "Gia" 
             << setw(10) << "So luong" << endl;
        cout << string(55, '-') << endl;
        
        for (int i = 0; i < dsDV.size(); i++) {
            cout << i + 1 << ". ";
            dsDV[i].hienThi();
        }

        cout << "0. Tro ve\n";
        int chon = nhapLuaChon(0, dsDV.size());
        if (chon == 0) {
            cout << "Da tro ve.\n";
            return;
        }

        DichVu &dichVu = dsDV[chon - 1];

        if (dichVu.getSoLuong() <= 0) {
            cout << dichVu.getTen() << " da het hang!\n";
            return;
        }

        double gia = dichVu.getGia();

        if (dsTK[idx]->getSoTien() >= gia) {
            dsTK[idx]->setSoTien(dsTK[idx]->getSoTien() - gia);
            dichVu.giamSoLuong();
            
            string lichSu = "Mua " + dichVu.getTen() + " - " + to_string((int)gia) + " VND";
            dsTK[idx]->themLichSu(lichSu);
            
            cout << "Da mua " << dichVu.getTen() << " thanh cong!\n";
            cout << "So du con lai: " << dsTK[idx]->getSoTien() << " VND\n";
        } else {
            cout << "Khong du tien! Vui long nap them tien.\n";
        }
    }

    void menuChonMayUser(int idx) {
        int chon;
        do {
            cout << "\n=== MENU CHON MAY USER ===\n";
            cout << "1. Xem danh sach may\n";
            cout << "2. Chon may de choi\n";
            cout << "0. Tro ve\n";

            chon = nhapLuaChon(0, 2);

            switch (chon) {
                case 1:
                    hienThiDanhSachMay();
                    break;
                case 2: {
                    if (dsTK[idx]->getSoTien() <= 0) {
                        cout << "So du bang 0, vui long nap tien truoc khi chon may!\n";
                        break;
                    }

                    hienThiDanhSachMay();
                    cout << "\nNhap ID may can choi (0 de tro ve): ";

                    int id;
                    cin >> id;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Sai dinh dang ID!\n";
                        break;
                    }

                    if (id == 0) {
                        cout << "Da tro ve menu chon may.\n";
                        break;
                    }

                    bool timThay = false;
                    for (auto &may : dsMay) {
                        if (may.getId() == id) {
                            timThay = true;

                            if (may.getTrangThai() != TrangThaiMay::Trong) {
                                may.batMay();
                                break;
                            }

                            may.batMay();
                            double gioCoTheChoi = dsTK[idx]->getSoTien() / may.getGiaTheoGio();
                            dsTK[idx]->setGioChoi(gioCoTheChoi);

                            string lichSu = "Chon may " + may.getTenMay() + " - Gio choi du kien: " + to_string(gioCoTheChoi);
                            dsTK[idx]->themLichSu(lichSu);

                            cout << "Ban da chon " << may.getTenMay() << ".\n";
                            cout << "Voi so du hien tai, ban co the choi khoang "
                                 << fixed << setprecision(1) << gioCoTheChoi << " gio.\n";
                            break;
                        }
                    }

                    if (!timThay) {
                        cout << "Khong tim thay may!\n";
                    }
                    break;
                }
            }

        } while (chon != 0);
    }

    //ham quan li may
    void quanLyMay() {
        int chon;
        do {
            cout << "\n=== QUAN LY MAY ===\n";
            cout << "1. Xem danh sach may\n";
            cout << "2. Bat may\n";
            cout << "3. Tat may\n";
            cout << "4. Dat bao tri\n";
            cout << "5. Them may moi\n";
            cout << "6. Cai dat gia may\n";
            cout << "0. Tro ve\n";

            chon = nhapLuaChon(0, 6);

            switch (chon) {
                case 1: hienThiDanhSachMay(); break;
                case 2: batMay(); break;
                case 3: tatMay(); break;
                case 4: datBaoTriMay(); break;
                case 5: themMay(); break;
                case 6: caiDatGiaMay(); break;
            }
        } while (chon != 0);
    }

    void hienThiDanhSachMay() {
        cout << "\n=== DANH SACH MAY ===\n";
        cout << left << setw(5) << "ID" 
             << setw(15) << "Ten may" 
             << setw(15) << "Trang thai" 
             << setw(10) << "Gia/gio" << endl;
        cout << string(45, '-') << endl;
        
        int trong = 0, dangChoi = 0, baoTri = 0;
        
        for (auto &may : dsMay) {
            may.hienThi();
            if (may.getTrangThai() == TrangThaiMay::Trong) trong++;
            else if (may.getTrangThai() == TrangThaiMay::DangChoi) dangChoi++;
            else baoTri++;
        }
        
        cout << string(45, '-') << endl;
        cout << "Tong: " << dsMay.size() << " may | ";
        cout << "Trong: " << trong << " | ";
        cout << "Dang choi: " << dangChoi << " | ";
        cout << "Bao tri: " << baoTri << endl;
    }

    void batMay() {
        hienThiDanhSachMay();
        int id;
        if (!nhapSoNguyen("\nNhap ID may can bat: ", id)) {
            return;
        }

        if (id <= 0) {
            cout << "ID may phai lon hon 0!\n";
            return;
        }

        for (auto &may : dsMay) {
            if (may.getId() == id) {
                may.batMay();
                return;
            }
        }
        cout << "Khong tim thay may!\n";
    }

    void tatMay() {
        hienThiDanhSachMay();
        int id;
        if (!nhapSoNguyen("\nNhap ID may can tat: ", id)) {
            return;
        }

        if (id <= 0) {
            cout << "ID may phai lon hon 0!\n";
            return;
        }

        for (auto &may : dsMay) {
            if (may.getId() == id) {
                may.tatMay();
                return;
            }
        }
        cout << "Khong tim thay may!\n";
    }

    void datBaoTriMay() {
        hienThiDanhSachMay();
        int id;
        if (!nhapSoNguyen("\nNhap ID may can dat bao tri: ", id)) {
            return;
        }

        if (id <= 0) {
            cout << "ID may phai lon hon 0!\n";
            return;
        }

        for (auto &may : dsMay) {
            if (may.getId() == id) {
                if (may.getTrangThai() == TrangThaiMay::DangChoi) {
                    cout << "May dang choi, hay tat may truoc khi dat bao tri!\n";
                    return;
                }

                if (may.getTrangThai() == TrangThaiMay::BaoTri) {
                    cout << "May da o che do bao tri!\n";
                    return;
                }

                may.datBaoTri();
                return;
            }
        }
        cout << "Khong tim thay may!\n";
    }

    void themMay() {
        int id;
        string ten;
        double gia;
        
        if (!nhapSoNguyen("Nhap ID may: ", id)) {
            return;
        }

        if (id <= 0) {
            cout << "ID may phai lon hon 0!\n";
            return;
        }

        for (auto &may : dsMay) {
            if (may.getId() == id) {
                cout << "ID may da ton tai!\n";
                return;
            }
        }

        cout << "Nhap ten may: ";
        cin.ignore(1000, '\n');
        getline(cin, ten);

        if (ten.empty()) {
            cout << "Ten may khong duoc rong!\n";
            return;
        }

        if (!nhapSoThuc("Nhap gia theo gio: ", gia)) {
            return;
        }

        if (gia <= 0) {
            cout << "Gia may phai lon hon 0!\n";
            return;
        }

        dsMay.push_back(May(id, ten, gia));
        cout << "Them may thanh cong!\n";
    }

    void caiDatGiaMay() {
        hienThiDanhSachMay();
        int id;
        if (!nhapSoNguyen("\nNhap ID may: ", id)) {
            return;
        }

        if (id <= 0) {
            cout << "ID may phai lon hon 0!\n";
            return;
        }

        for (auto &may : dsMay) {
            if (may.getId() == id) {
                double gia;
                if (!nhapSoThuc("Nhap gia moi: ", gia)) {
                    return;
                }

                if (gia <= 0) {
                    cout << "Gia may phai lon hon 0!\n";
                    return;
                }

                may.setGiaTheoGio(gia);
                cout << "Cap nhat gia thanh cong!\n";
                return;
            }
        }
        cout << "Khong tim thay may!\n";
    }

    //ham quan li dich vu
    void quanLyDichVu() {
        int chon;
        do {
            cout << "\n=== QUAN LY DICH VU ===\n";
            cout << "1. Xem danh sach dich vu\n";
            cout << "2. Them dich vu\n";
            cout << "3. Cap nhat gia dich vu\n";
            cout << "4. Xoa dich vu\n";
            cout << "0. Tro ve\n";

            chon = nhapLuaChon(0, 4);

            switch (chon) {
                case 1: hienThiDanhSachDV(); break;
                case 2: themDichVu(); break;
                case 3: capNhatGiaDV(); break;
                case 4: xoaDichVu(); break;
            }
        } while (chon != 0);
    }

    void hienThiDanhSachDV() {
        cout << "\n=== DANH SACH DICH VU ===\n";
        cout << left << setw(10) << "Ma DV" 
             << setw(20) << "Ten" 
             << setw(15) << "Gia" 
             << setw(10) << "So luong" << endl;
        cout << string(55, '-') << endl;
        
        for (int i = 0; i < dsDV.size(); i++) {
            cout << i + 1 << ". ";
            dsDV[i].hienThi();
        }
    }

    void themDichVu() {
        string ma, ten;
        double gia;
        int sl;

        cout << "Nhap ma dich vu: ";
        cin >> ma;

        for (auto &dv : dsDV) {
            if (dv.getMaDV() == ma) {
                cout << "Ma dich vu da ton tai!\n";
                return;
            }
        }

        cout << "Nhap ten dich vu: ";
        cin.ignore(1000, '\n');
        getline(cin, ten);

        if (ten.empty()) {
            cout << "Ten dich vu khong duoc rong!\n";
            return;
        }

        if (!nhapSoThuc("Nhap gia: ", gia)) {
            return;
        }

        if (gia <= 0) {
            cout << "Gia dich vu phai lon hon 0!\n";
            return;
        }

        if (!nhapSoNguyen("Nhap so luong: ", sl)) {
            return;
        }

        if (sl < 0) {
            cout << "So luong khong duoc am!\n";
            return;
        }

        dsDV.push_back(DichVu(ma, ten, gia, sl));
        cout << "Them dich vu thanh cong!\n";
    }

    void capNhatGiaDV() {
        if (dsDV.empty()) {
            cout << "Danh sach dich vu dang rong!\n";
            return;
        }

        hienThiDanhSachDV();
        cout << "\nNhap so thu tu dich vu: ";
        int chon = nhapLuaChon(1, dsDV.size());
        
        double gia;
        if (!nhapSoThuc("Nhap gia moi: ", gia)) {
            return;
        }

        if (gia <= 0) {
            cout << "Gia dich vu phai lon hon 0!\n";
            return;
        }
        
        dsDV[chon - 1].setGia(gia);
        cout << "Cap nhat gia thanh cong!\n";
    }

    void xoaDichVu() {
        if (dsDV.empty()) {
            cout << "Danh sach dich vu dang rong!\n";
            return;
        }

        hienThiDanhSachDV();
        cout << "\nNhap so thu tu dich vu can xoa: ";
        int chon = nhapLuaChon(1, dsDV.size());
        
        dsDV.erase(dsDV.begin() + chon - 1);
        cout << "Xoa dich vu thanh cong!\n";
    }

    bool xacThucAdmin() {
        const string ADMIN_USER = "admin";
        const string ADMIN_PASS = "admin123";

        string user, pass;
        cout << "\n=== DANG NHAP ADMIN ===\n";

        for (int lan = 1; lan <= 3; lan++) {
            cout << "Username admin: ";
            cin >> user;
            cout << "Password admin: ";
            cin >> pass;

            if (user == ADMIN_USER && pass == ADMIN_PASS) {
                cout << "Dang nhap admin thanh cong!\n";
                return true;
            }

            cout << "Sai thong tin admin (" << lan << "/3)!\n";
        }

        cout << "Tu choi truy cap menu admin!\n";
        return false;
    }

    //Ham quan li tai khoan - ADMIN -
    void quanLyTaiKhoan() {
        int chon;
        do {
            cout << "\n=== QUAN LY TAI KHOAN ===\n";
            cout << "1. Tao tai khoan\n";
            cout << "2. Xem danh sach tai khoan\n";
            cout << "3. Nap tien cho tai khoan\n";
            cout << "4. Khoa tai khoan\n";
            cout << "5. Mo khoa tai khoan\n";
            cout << "6. Xoa tai khoan\n";
            cout << "7. Xem lich su giao dich\n";
            cout << "0. Tro ve\n";

            chon = nhapLuaChon(0, 7);

            switch (chon) {
                case 1: taoTK(); break;
                case 2: hienThiDSTK(); break;
                case 3: napTienTaiKhoan(); break;
                case 4: khoaTK(); break;
                case 5: moKhoaTK(); break;
                case 6: xoaTK(); break;
                case 7: xemLichSuGiaoDich(); break;
            }
        } while (chon != 0);
    }

    void hienThiDSTK() {
        cout << "\n=== DANH SACH TAI KHOAN ===\n";
        cout << left << setw(15) << "Username" 
             << setw(20) << "Ho ten" 
             << setw(15) << "So tien" 
             << setw(12) << "Trang thai" << endl;
        cout << string(62, '-') << endl;
        
        for (auto tk : dsTK) {
            cout << left << setw(15) << tk->getUsername() 
                 << setw(20) << tk->getHoTen() 
                 << setw(15) << tk->getSoTien() 
                 << setw(12) << (tk->getTrangThaiKhoa() ? "Bi khoa" : "Hoat dong") << endl;
        }
    }

    void khoaTK() {
        string u;
        cout << "Nhap username can khoa: ";
        cin >> u;

        for (auto tk : dsTK) {
            if (tk->getUsername() == u) {
                tk->khoaTaiKhoan();
                cout << "Tai khoan da bi khoa!\n";
                return;
            }
        }
        cout << "Khong tim thay!\n";
    }

    void moKhoaTK() {
        string u;
        cout << "Nhap username can mo khoa: ";
        cin >> u;

        for (auto tk : dsTK) {
            if (tk->getUsername() == u) {
                tk->moKhoaTaiKhoan();
                cout << "Tai khoan da duoc mo khoa!\n";
                return;
            }
        }
        cout << "Khong tim thay!\n";
    }

    void xoaTK() {
        string u;
        cout << "Nhap username can xoa: ";
        cin >> u;

        for (int i = 0; i < dsTK.size(); i++) {
            if (dsTK[i]->getUsername() == u) {
                delete dsTK[i];
                dsTK.erase(dsTK.begin() + i);
                cout << "Xoa tai khoan thanh cong!\n";
                return;
            }
        }
        cout << "Khong tim thay!\n";
    }

    void napTienTaiKhoan() {
        if (dsTK.empty()) {
            cout << "Chua co tai khoan nao de nap tien!\n";
            return;
        }

        string u;
        cout << "Nhap username can nap tien: ";
        cin >> u;

        for (auto tk : dsTK) {
            if (tk->getUsername() == u) {
                cout << "\n=== NAP TIEN CHO " << tk->getUsername() << " ===\n";
                cout << "1. 10.000 VND\n";
                cout << "2. 20.000 VND\n";
                cout << "3. 50.000 VND\n";
                cout << "4. 100.000 VND\n";
                cout << "5. Nhap so tien khac\n";
                cout << "0. Tro ve\n";

                int chon = nhapLuaChon(0, 5);
                if (chon == 0) {
                    cout << "Da tro ve.\n";
                    return;
                }

                double tien = 0;
                switch (chon) {
                    case 1: tien = 10000; break;
                    case 2: tien = 20000; break;
                    case 3: tien = 50000; break;
                    case 4: tien = 100000; break;
                    case 5:
                        if (!nhapSoThuc("Nhap so tien: ", tien)) {
                            return;
                        }
                        break;
                }

                if (tien <= 0) {
                    cout << "So tien khong hop le!\n";
                    return;
                }

                tk->setSoTien(tk->getSoTien() + tien);
                string lichSu = "Admin nap " + to_string((int)tien) + " VND - So du: " + to_string((int)tk->getSoTien());
                tk->themLichSu(lichSu);

                cout << "Nap tien thanh cong cho " << tk->getUsername() << "!\n";
                cout << "So du hien tai: " << tk->getSoTien() << " VND\n";
                return;
            }
        }

        cout << "Khong tim thay!\n";
    }

    void xemLichSuGiaoDich() {
        string u;
        cout << "Nhap username: ";
        cin >> u;

        for (auto tk : dsTK) {
            if (tk->getUsername() == u) {
                tk->xemLichSu();
                return;
            }
        }
        cout << "Khong tim thay!\n";
    }

    //ham thong ke
    void thongKe() {
        cout << "\n=== THONG KE ===\n";
        
        double tongTien = 0;
        int soTKHoatDong = 0;
        int soTKBiKhoa = 0;
        int mayDangChoi = 0;

        for (auto tk : dsTK) {
            tongTien += tk->getSoTien();
            if (tk->getTrangThaiKhoa()) soTKBiKhoa++;
            else soTKHoatDong++;
        }

        for (auto may : dsMay) {
            if (may.getTrangThai() == TrangThaiMay::DangChoi) mayDangChoi++;
        }

        cout << "Tong so tai khoan: " << dsTK.size() << endl;
        cout << "Tai khoan hoat dong: " << soTKHoatDong << endl;
        cout << "Tai khoan bi khoa: " << soTKBiKhoa << endl;
        cout << "Tong so tien trong he thong: " << tongTien << " VND\n";
        cout << "Tong so may: " << dsMay.size() << endl;
        cout << "May dang choi: " << mayDangChoi << endl;
    }

    //Menu cua user
    void menuUser(int idx) {
        int chon;
        do {
            cout << "\n=== MENU USER ===\n";
            cout << "1. Nap tien\n";
            cout << "2. Mua dich vu\n";
            cout << "3. Doi mat khau\n";
            cout << "4. Chon may\n";
            cout << "5. Xem thong tin\n";
            cout << "6. Xem lich su\n";
            cout << "0. Dang xuat\n";

            chon = nhapLuaChon(0, 6);

            switch (chon) {
                case 1: dsTK[idx]->napTien(); break;
                case 2: suDungDV(idx); break;
                case 3: dsTK[idx]->doiMatKhau(); break;
                case 4: menuChonMayUser(idx); break;
                case 5: dsTK[idx]->hienThi(); break;
                case 6: dsTK[idx]->xemLichSu(); break;
            }

        } while (chon != 0);
    }

    //Menu cua admin
    void menuAdmin() {
        int chon;
        do {
            cout << "\n=== MENU QUAN LY (ADMIN) ===\n";
            cout << "1. Quan ly tai khoan\n";
            cout << "2. Quan ly may\n";
            cout << "3. Quan ly dich vu\n";
            cout << "4. Thong ke\n";
            cout << "0. Thoat\n";

            chon = nhapLuaChon(0, 4);

            switch (chon) {
                case 1: quanLyTaiKhoan(); break;
                case 2: quanLyMay(); break;
                case 3: quanLyDichVu(); break;
                case 4: thongKe(); break;
            }

        } while (chon != 0);
    }

    //Main menu
    void menu() {
        int chon;
        do {
            cout << "\n========== CHAO MUNG BAN DEN VOI QUAN NET BINH NGUYEN VO TAN ==========";
            cout << "\n========== MENU ==========\n";
            cout << "1. Tao tai khoan\n";
            cout << "2. Dang nhap\n";
            cout << "3. Quan ly (Admin)\n";
            cout << "0. Thoat\n";

            chon = nhapLuaChon(0, 3);

            switch (chon) {
                case 1: taoTK(); break;
                case 2: {
                    int idx = dangNhap();
                    if (idx != -1)
                        menuUser(idx);
                    break;
                }
                case 3:
                    if (xacThucAdmin())
                        menuAdmin();
                    break;
            }

        } while (chon != 0);
        
        cout << "Tam biet! Hen gap lai!\n";
    }
};

//Ham main
int main() {
    Server s;
    s.menu();
    return 0;
}