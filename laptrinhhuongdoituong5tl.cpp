#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

//Gia may
const double GIA_LOAI_1 = 8000;
const double GIA_LOAI_2 = 10000;
const double GIA_LOAI_3 = 15000;

// Lua chon
int LuaChon(int min, int max) {
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

        if (chon >= min && chon <= max) {
            return chon;
        }

        cout << "Sai lua chon! Nhap lai!\n";
    }
}

string HienTai() {
    time_t now = time(0);
    char *dt = ctime(&now);
    return string(dt);
}

bool SoNguyen(const string &thongBao, int &giatri) {
    cout << thongBao;
    cin >> giatri;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Sai dinh dang so nguyen!\n";
        return false;
    }

    return true;
}

bool SoThuc(const string &thongBao, double &giatri) {
    cout << thongBao;
    cin >> giatri;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Sai dinh dang so!\n";
        return false;
    }

    return true;
}

string DinhDangTien(double sotien) {
    long long giatri;
    if (sotien >= 0) {
        giatri = static_cast<long long>(sotien + 0.5);
    } else {
        giatri = static_cast<long long>(sotien - 0.5);
    }

    bool am = giatri < 0;
    if (am) {
        giatri = -giatri;
    }

    string so = to_string(giatri);
    for (int i = static_cast<int>(so.size()) - 3; i > 0; i -= 3) {
        so.insert(i, ".");
    }

    if (am) {
        so = "-" + so;
    }

    return so;
}

//Lop Nguoi Dung
class NguoiDung {
protected:
    string username;
    string password;
    string hoten;
    string sdt;

public:
    NguoiDung(string username = "", string password = "", string hoten = "", string sdt = "") {
        this->username = username;
        this->password = password;
        this->hoten = hoten;
        this->sdt = sdt;
    }

    virtual ~NguoiDung() {}

    string Username() { return this->username; }
    string Password() { return this->password; }
    string HoTen() { return this->hoten; }
    string SDT() { return this->sdt; }

    void NhapPassword(string password) { this->password = password; }
    void NhapHoTen(string hoten) { this->hoten = hoten; }
    void NhapSDT(string sdt) { this->sdt = sdt; }

    virtual void ThongTin() {
        cout << "Username: " << username << endl;
        cout << "Ho ten: " << hoten << endl;
        cout << "SDT: " << sdt << endl;
    }
};

//Lop Tai Khoan
class TaiKhoan : public NguoiDung {
private:
    double sotien;
    double giochoi;
    bool khoa;
    vector<string> lichsugiaodich;

public:
    TaiKhoan(string u = "", string p = "", string hoten = "", string sdt = "")
        : NguoiDung(u, p, hoten, sdt) {
        this->sotien = 0;
        this->giochoi = 0;
        this->khoa = false;
    }

    ~TaiKhoan() {}

    double SoTien() { return this->sotien; }
    double GioChoi() { return this->giochoi; }
    bool TrangThaiKhoa() { return this->khoa; }

    void NhapSoTien(double sotien) { this->sotien = sotien; }
    void NhapGioChoi(double giochoi) { this->giochoi = giochoi; }

    void ThemLichSu(const string &giaodich) {
        lichsugiaodich.push_back(giaodich);
    }

    void XemLichSu() {
        cout << "\n=== LICH SU GIAO DICH ===\n";
        if (lichsugiaodich.empty()) {
            cout << "Chua co giao dich nao!\n";
            return;
        }

        for (size_t i = 0; i < lichsugiaodich.size(); i++) {
            cout << i + 1 << ". " << lichsugiaodich[i] << endl;
        }
    }

    bool XuatHoaDon(const string &giaodich) {
        return giaodich.rfind("Mua ", 0) == 0 || giaodich.rfind("Chon may ", 0) == 0;
    }

    double TienGiaoDich(const string &giaodich) {
        size_t ngancach = giaodich.find(" - ");
        if (ngancach == string::npos) {
            return 0;
        }

        size_t donvi = giaodich.find(" VND", ngancach + 3);
        if (donvi == string::npos || donvi <= ngancach + 3) {
            return 0;
        }

        string tienstr = giaodich.substr(ngancach + 3, donvi - (ngancach + 3));
        try {
            return stod(tienstr);
        } catch (...) {
            return 0;
        }
    }

    void XuatHoaDonTuLichSu() {
        cout << "\n=== HOA DON SU DUNG ===\n";
        cout << "Khach hang: " << username << endl;
        cout << "Ngay lap: " << HienTai();
        cout << "-------------------\n";

        bool DuLieu = false;
        double tongtien = 0;
        int stt = 1;

        for (const auto &giaodich : lichsugiaodich) {
            if (!XuatHoaDon(giaodich)) {
                continue;
            }

            DuLieu = true;
            cout << stt++ << ". " << giaodich << endl;
            tongtien += TienGiaoDich(giaodich);
        }

        if (!DuLieu) {
            cout << "Khong co muc nao de xuat hoa don!\n";
            return;
        }

        cout << "-------------------\n";
        cout << "Tong tien dich vu: " << fixed << setprecision(0) << tongtien << " VND\n";
    }

    void MenuLichSu() {
        XemLichSu();

        int chon;
        do {
            cout << "\n=== MENU LICH SU ===\n";
            cout << "1. Xuat hoa don\n";
            cout << "0. Tro ve\n";

            chon = LuaChon(0, 1);
            if (chon == 1) {
                XuatHoaDonTuLichSu();
            }
        } while (chon != 0);
    }

    void NapTien() {
        cout << "\n=== NAP TIEN ===\n";
        cout << "1. 10.000 VND\n2. 20.000 VND\n3. 50.000 VND\n";
        cout << "4. 100.000 VND\n5. Nhap so tien khac\n";
        cout << "0. Tro ve\n";

        int chon = LuaChon(0, 5);
        if (chon == 0) {
            cout << "Da tro ve Menu.\n";
            return;
        }

        double tien = 0;

        switch (chon) {
            case 1: tien = 10000; break;
            case 2: tien = 20000; break;
            case 3: tien = 50000; break;
            case 4: tien = 100000; break;
            case 5:
                if (!SoThuc("Nhap so tien: ", tien)) {
                    return;
                }
                break;
        }

        if (tien > 0) {
            this->sotien += tien;

            string lichsu = "Nap " + to_string((int)tien) + " VND - So du: " + to_string((int)sotien) + " VND";
            ThemLichSu(lichsu);

            cout << "Nap thanh cong! So du hien tai: " << sotien << " VND\n";
        } else {
            cout << "So tien khong hop le!\n";
        }
    }

    void DoiMatKhau() {
        cout << "\n=== DOI MAT KHAU ===\n";
        cout << "1. Tiep tuc doi mat khau\n";
        cout << "0. Tro ve\n";

        int luaChon = LuaChon(0, 1);
        if (luaChon == 0) {
            cout << "Da tro ve Menu.\n";
            return;
        }

        string passcu, passmoi;
        cout << "Nhap mat khau cu: ";
        cin >> passcu;

        if (passcu == this->password) {
            cout << "Nhap mat khau moi: ";
            cin >> passmoi;
            this->password = passmoi;
            ThemLichSu("Doi mat khau thanh cong");
            cout << "Doi mat khau thanh cong!\n";
        } else {
            cout << "Sai mat khau!\n";
        }
    }

    void KhoaTaiKhoan() {
        this->khoa = true;
        ThemLichSu("Tai khoan da bi khoa");
    }

    void MoKhoaTaiKhoan() {
        this->khoa = false;
        ThemLichSu("Tai khoan da duoc mo khoa");
    }

    void HienThi() {
        cout << "\n=== THONG TIN TAI KHOAN ===\n";
        cout << "Username: " << this->username << endl;
        cout << "Ho ten: " << this->hoten << endl;
        cout << "SDT: " << this->sdt << endl;
        cout << "So tien: " << fixed << setprecision(0) << this->sotien << " VND\n";
        cout << "Gio choi: " << fixed << setprecision(1) << this->giochoi << " gio\n";
        cout << "Trang thai: " << (this->khoa ? "Bi khoa" : "Hoat dong") << endl;
    }

    void ThongTin() override {
        HienThi();
    }
};

//Lop Dich Vu
class DichVu {
private:
    string madv;
    string ten;
    double gia;
    int soluong;

public:
    DichVu(string madv = "", string ten = "", double gia = 0, int soluong = 100) {
        this->madv = madv;
        this->ten = ten;
        this->gia = gia;
        this->soluong = soluong;
    }

    string MaDV() { return this->madv; }
    string Ten() { return this->ten; }
    double Gia() { return this->gia; }
    int SoLuong() { return this->soluong; }

    void NhapGia(double gia) { this->gia = gia; }
    void NhapSoLuong(int soLuong) { this->soluong = soLuong; }

    void GiamSoLuong() {
        if (soluong > 0) {
            soluong--;
        }
    }

    void TangSoLuong() {
        soluong++;
    }

    void HienThi() {
        cout << left << setw(10) << madv
             << setw(20) << ten
             << right << setw(10) << DinhDangTien(gia)
             << "  "
             << left << setw(12) << soluong << endl;
    }
};

//Lop May
enum class TrangThaiMay { Trong, DangChoi, BaoTri };

class May {
private:
    int id;
    TrangThaiMay trangthai;
    string tenmay;
    double giatheogio;

public:
    May(int id = 0, string tenMay = "", double giaTheoGio = 5000) {
        this->id = id;
        this->tenmay = tenMay;
        this->giatheogio = giaTheoGio;
        this->trangthai = TrangThaiMay::Trong;
    }

    int ID() { return this->id; }
    TrangThaiMay TrangThai() { return this->trangthai; }
    string TenMay() { return this->tenmay; }
    double GiaTheoGio() { return this->giatheogio; }

    void NhapTrangThai(TrangThaiMay tt) { this->trangthai = tt; }
    void NhapGiaTheoGio(double gia) { this->giatheogio = gia; }

    string TrangThaiString() {
        switch (trangthai) {
            case TrangThaiMay::Trong: return "Trong";
            case TrangThaiMay::DangChoi: return "Dang choi";
            case TrangThaiMay::BaoTri: return "Bao tri";
        }
        return "Unknown";
    }

    void BatMay() {
        if (trangthai == TrangThaiMay::Trong) {
            trangthai = TrangThaiMay::DangChoi;
            cout << "May " << id << " (" << tenmay << ") DA BAT\n";
        } else if (trangthai == TrangThaiMay::BaoTri) {
            cout << "May dang bao tri, khong the bat!\n";
        } else {
            cout << "May dang duoc su dung!\n";
        }
    }

    void TatMay() {
        trangthai = TrangThaiMay::Trong;
        cout << "May " << id << " DA TAT\n";
    }

    void BaoTri() {
        trangthai    = TrangThaiMay::BaoTri;
        cout << "May " << id << " da duoc dat che do bao tri!\n";
    }

    void HienThi() {
        cout << left << setw(5) << id
             << setw(20) << tenmay
             << setw(15) << TrangThaiString()
             << right << setw(10) << DinhDangTien(giatheogio)
             << left << endl;
    }
};

//Lop Hoa Don
class HoaDon {
private:
    string mahoadon;
    string username;
    double tongtien;
    string ngaylap;
    vector<pair<string, double>> chitiet;

public:
    HoaDon(string maHD = "", string username = "") {
        this->mahoadon = maHD;
        this->username = username;
        this->tongtien = 0;
        this->ngaylap = HienTai();
    }

    void ThemChiTiet(const string &tenDV, double gia) {
        chitiet.push_back({tenDV, gia});
        tongtien += gia;
    }

    void HienThi() {
        cout << "\n=== HOA DON ===\n";
        cout << "Ma HD: " << mahoadon << endl;
        cout << "Khach hang: " << username << endl;
        cout << "Ngay lap: " << ngaylap << endl;
        cout << "-------------------\n";
        for (auto &ct : chitiet) {
            cout << ct.first << ": " << ct.second << " VND\n";
        }
        cout << "-------------------\n";
        cout << "Tong cong: " << tongtien << " VND\n";
    }

    double TongTien() { return tongtien; }
};

//Lop Server
class Server {
private:
    vector<TaiKhoan *> dstk;
    vector<DichVu> dsdv;
    vector<May> dsmay;
    vector<HoaDon> dshoadon;
    int dangdung;

public:
    Server() {
        dangdung = 0;
        KhoiTaoTaiKhoanDemo();
        KhoiTaoMay();
        KhoiTaoDichVu();
    }

    void KhoiTaoTaiKhoanDemo() {
        TaiKhoan *demo = new TaiKhoan("demo", "demo123", "Tai Khoan Demo", "0900000000");
        demo->NhapSoTien(20000);
        demo->ThemLichSu("Khoi tao tai khoan demo - So du: 20000 VND");
        dstk.push_back(demo);
    }

    void KhoiTaoMay() {
        dsmay.push_back(May(1, "PC Gaming 1", GIA_LOAI_1));
        dsmay.push_back(May(2, "PC Gaming 2", GIA_LOAI_1));
        dsmay.push_back(May(3, "PC Gaming 3", GIA_LOAI_1));
        dsmay.push_back(May(4, "PC Van Phong 1", GIA_LOAI_2));
        dsmay.push_back(May(5, "PC Van Phong 2", GIA_LOAI_2));
        dsmay.push_back(May(6, "PC Van Phong 3", GIA_LOAI_2));
        dsmay.push_back(May(7, "VIP Room 1", GIA_LOAI_3));
        dsmay.push_back(May(8, "VIP Room 2", GIA_LOAI_3));
    }

    void KhoiTaoDichVu() {
        dsdv.push_back(DichVu("DV001", "Mi tom", 10000, 50));
        dsdv.push_back(DichVu("DV002", "Nuoc ngot", 5000, 100));
        dsdv.push_back(DichVu("DV003", "Cafe", 15000, 30));
        dsdv.push_back(DichVu("DV004", "Banh my", 8000, 20));
        dsdv.push_back(DichVu("DV005", "Tra sua", 20000, 25));
        dsdv.push_back(DichVu("DV006", "Khoai tay", 15000, 30));
    }

    ~Server() {
        for (auto tk : dstk) {
            delete tk;
        }
    }

    // TAO TAI KHOAN
    void TaoTK() {
        string u, p, hoten, sdt;
        cout << "\n=== TAO TAI KHOAN ===\n";
        cout << "Nhap username: ";
        cin >> u;

        for (auto tk : dstk) {
            if (tk->Username() == u) {
                cout << "Username da ton tai!\n";
                return;
            }
        }

        cout << "Nhap password: ";
        cin >> p;
        cout << "Nhap ho ten: ";
        cin.ignore(1000, '\n');
        getline(cin, hoten);
        cout << "Nhap SDT: ";
        cin >> sdt;

        dstk.push_back(new TaiKhoan(u, p, hoten, sdt));
        cout << "Tao tai khoan thanh cong!\n";
    }

    // DANG NHAP
    int DangNhap() {
        string u, p;

        cout << "\n=== DANG NHAP ===\n";
        cout << "Username: ";
        cin >> u;

        int index = -1;
        for (size_t i = 0; i < dstk.size(); i++) {
            if (dstk[i]->Username() == u) {
                index = static_cast<int>(i);
                break;
            }
        }

        if (index == -1) {
            cout << "Tai khoan khong ton tai!\n";
            return -1;
        }

        if (dstk[index]->TrangThaiKhoa()) {
            cout << "Tai khoan da bi khoa!\n";
            return -1;
        }

        for (int lan = 1; lan <= 3; lan++) {
            cout << "Nhap password (" << lan << "/3): ";
            cin >> p;

            if (p == dstk[index]->Password()) {
                cout << "Dang nhap thanh cong! Xin chao " << dstk[index]->HoTen() << "!\n";
                return index;
            }

            cout << "Sai mat khau!\n";
        }

        dstk[index]->KhoaTaiKhoan();
        cout << "Tai khoan bi khoa vi nhap sai qua 3 lan!\n";
        return -1;
    }

    // SU DUNG DICH VU
    void SuDungDV(int idx) {
        if (dsdv.empty()) {
            cout << "Danh sach dich vu dang rong!\n";
            return;
        }

        cout << "\n=== DICH VU ===\n";
        cout << left << setw(5) << "STT"
             << setw(10) << "Ma DV"
             << setw(20) << "Ten"
             << right << setw(20) << "Gia"
             << "  "
             << left
             << setw(10) << "So luong" << endl;
        cout << string(59, '-') << endl;

        for (size_t i = 0; i < dsdv.size(); i++) {
            cout << left << setw(5) << (i + 1);
            dsdv[i].HienThi();
        }

        cout << "0. Tro ve\n";
        int chon = LuaChon(0, static_cast<int>(dsdv.size()));
        if (chon == 0) {
            cout << "Da tro ve Menu.\n";
            return;
        }

        DichVu &dichvu = dsdv[chon - 1];

        if (dichvu.SoLuong() <= 0) {
            cout << dichvu.Ten() << " da het hang!\n";
            return;
        }

        double gia = dichvu.Gia();
        if (dstk[idx]->SoTien() >= gia) {
            dstk[idx]->NhapSoTien(dstk[idx]->SoTien() - gia);
            dichvu.GiamSoLuong();

            string lichSu = "Mua " + dichvu.Ten() + " - " + to_string((int)gia) + " VND";
            dstk[idx]->ThemLichSu(lichSu);

            cout << "Da mua " << dichvu.Ten() << " thanh cong!\n";
            cout << "So du con lai: " << dstk[idx]->SoTien() << " VND\n";
        } else {
            cout << "Khong du tien! Vui long nap them tien.\n";
        }
    }

    void MenuChonMay(int idx) {
        int chon;
        do {
            cout << "\n=== MENU CHON MAY USER ===\n";
            cout << "1. Xem danh sach may\n";
            cout << "2. Chon may de choi\n";
            cout << "0. Tro ve\n";

            chon = LuaChon(0, 2);

            switch (chon) {
                case 1:
                    DanhSachMay();
                    break;
                case 2: {
                    if (dstk[idx]->SoTien() <= 0) {
                        cout << "So du bang 0, vui long nap tien truoc khi chon may!\n";
                        break;
                    }

                    DanhSachMay();
                    int id;
                    if (!SoNguyen("\nNhap ID may can choi (0 de tro ve): ", id)) {
                        break;
                    }

                    if (id == 0) {
                        cout << "Da tro ve menu chon may.\n";
                        break;
                    }

                    bool found = false;
                    for (auto &may : dsmay) {
                        if (may.ID() == id) {
                            found = true;

                            if (may.TrangThai() != TrangThaiMay::Trong) {
                                may.BatMay();
                                break;
                            }

                            may.BatMay();
                            double gioCoTheChoi = dstk[idx]->SoTien() / may.GiaTheoGio();
                            dstk[idx]->NhapGioChoi(gioCoTheChoi);

                            string lichSu = "Chon may " + may.TenMay() + " - 0 VND";
                            dstk[idx]->ThemLichSu(lichSu);

                            cout << "Ban da chon " << may.TenMay() << ".\n";
                            cout << "Voi so du hien tai, ban co the choi khoang "
                                 << fixed << setprecision(1) << gioCoTheChoi << " gio.\n";
                            break;
                        }
                    }

                    if (!found) {
                        cout << "Khong tim thay may!\n";
                    }
                    break;
                }
            }

        } while (chon != 0);
    }

    // QUAN LY MAY
    void QuanLyMay() {
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

            chon = LuaChon(0, 6);

            switch (chon) {
                case 1: DanhSachMay(); break;
                case 2: BatMay(); break;
                case 3: TatMay(); break;
                case 4: BaoTriMay(); break;
                case 5: ThemMay(); break;
                case 6: CaiDatGiaMay(); break;
            }
        } while (chon != 0);
    }

    void DanhSachMay() {
        cout << "\n=== DANH SACH MAY ===\n";
        cout << left << setw(5) << "ID"
               << setw(20) << "Ten may"
             << setw(15) << "Trang thai"
               << right << setw(10) << "Gia/gio"
               << left << endl;
           cout << string(52, '-') << endl;

        int trong = 0, dangChoi = 0, baoTri = 0;

        for (auto &may : dsmay) {
            may.HienThi();
            if (may.TrangThai() == TrangThaiMay::Trong) {
                trong++;
            } else if (may.TrangThai() == TrangThaiMay::DangChoi) {
                dangChoi++;
            } else {
                baoTri++;
            }
        }

        cout << string(52, '-') << endl;
        cout << "Tong: " << dsmay.size() << " may | ";
        cout << "Trong: " << trong << " | ";
        cout << "Dang choi: " << dangChoi << " | ";
        cout << "Bao tri: " << baoTri << endl;
    }

    void BatMay() {
        DanhSachMay();
        int id;
        if (!SoNguyen("\nNhap ID may can bat: ", id)) {
            return;
        }

        if (id <= 0) {
            cout << "ID may phai lon hon 0!\n";
            return;
        }

        for (auto &may : dsmay) {
            if (may.ID() == id) {
                may.BatMay();
                return;
            }
        }
        cout << "Khong tim thay may!\n";
    }

    void TatMay() {
        DanhSachMay();
        int id;
        if (!SoNguyen("\nNhap ID may can tat: ", id)) {
            return;
        }

        if (id <= 0) {
            cout << "ID may phai lon hon 0!\n";
            return;
        }

        for (auto &may : dsmay) {
            if (may.ID() == id) {
                may.TatMay();
                return;
            }
        }
        cout << "Khong tim thay may!\n";
    }

    void BaoTriMay() {
        DanhSachMay();
        int id;
        if (!SoNguyen("\nNhap ID may can dat bao tri: ", id)) {
            return;
        }

        if (id <= 0) {
            cout << "ID may phai lon hon 0!\n";
            return;
        }

        for (auto &may : dsmay) {
            if (may.ID() == id) {
                if (may.TrangThai() == TrangThaiMay::DangChoi) {
                    cout << "May dang choi, hay tat may truoc khi dat bao tri!\n";
                    return;
                }

                if (may.TrangThai() == TrangThaiMay::BaoTri) {
                    cout << "May da o che do bao tri!\n";
                    return;
                }

                may.BaoTri();
                return;
            }
        }
        cout << "Khong tim thay may!\n";
    }

    void ThemMay() {
        int id;
        string ten;
        double gia;

        if (!SoNguyen("Nhap ID may: ", id)) {
            return;
        }

        if (id <= 0) {
            cout << "ID may phai lon hon 0!\n";
            return;
        }

        for (auto &may : dsmay) {
            if (may.ID() == id) {
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

        if (!SoThuc("Nhap gia theo gio: ", gia)) {
            return;
        }

        if (gia <= 0) {
            cout << "Gia may phai lon hon 0!\n";
            return;
        }

        dsmay.push_back(May(id, ten, gia));
        cout << "Them may thanh cong!\n";
    }

    void CaiDatGiaMay() {
        DanhSachMay();
        int id;
        if (!SoNguyen("\nNhap ID may: ", id)) {
            return;
        }

        if (id <= 0) {
            cout << "ID may phai lon hon 0!\n";
            return;
        }

        for (auto &may : dsmay) {
            if (may.ID() == id) {
                double gia;
                if (!SoThuc("Nhap gia moi: ", gia)) {
                    return;
                }

                if (gia <= 0) {
                    cout << "Gia may phai lon hon 0!\n";
                    return;
                }

                may.NhapGiaTheoGio(gia);
                cout << "Cap nhat gia thanh cong!\n";
                return;
            }
        }
        cout << "Khong tim thay may!\n";
    }

    // QUAN LY DICH VU
    void QuanLyDichVu() {
        int chon;
        do {
            cout << "\n=== QUAN LY DICH VU ===\n";
            cout << "1. Xem danh sach dich vu\n";
            cout << "2. Them dich vu\n";
            cout << "3. Cap nhat gia dich vu\n";
            cout << "4. Xoa dich vu\n";
            cout << "0. Tro ve\n";

            chon = LuaChon(0, 4);

            switch (chon) {
                case 1: DanhSachDV(); break;
                case 2: ThemDichVu(); break;
                case 3: CaiDatGiaDV(); break;
                case 4: XoaDichVu(); break;
            }
        } while (chon != 0);
    }

    void DanhSachDV() {
        cout << "\n=== DANH SACH DICH VU ===\n";
        cout << left << setw(5) << "STT"
             << setw(10) << "Ma DV"
             << setw(20) << "Ten"
             << right << setw(10) << "Gia"
               << "  "
             << left
             << setw(12) << "So luong" << endl;
           cout << string(60, '-') << endl;

        for (size_t i = 0; i < dsdv.size(); i++) {
            cout << left << setw(5) << (i + 1);
            dsdv[i].HienThi();
        }
    }

    void ThemDichVu() {
        string ma, ten;
        double gia;
        int sl;

        cout << "Nhap ma dich vu: ";
        cin >> ma;

        for (auto &dv : dsdv) {
            if (dv.MaDV() == ma) {
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

        if (!SoThuc("Nhap gia: ", gia)) {
            return;
        }

        if (gia <= 0) {
            cout << "Gia dich vu phai lon hon 0!\n";
            return;
        }

        if (!SoNguyen("Nhap so luong: ", sl)) {
            return;
        }

        if (sl < 0) {
            cout << "So luong khong duoc am!\n";
            return;
        }

        dsdv.push_back(DichVu(ma, ten, gia, sl));
        cout << "Them dich vu thanh cong!\n";
    }

    void CaiDatGiaDV() {
        if (dsdv.empty()) {
            cout << "Danh sach dich vu dang rong!\n";
            return;
        }

        DanhSachDV();
        cout << "\nNhap so thu tu dich vu: ";
        int chon = LuaChon(1, static_cast<int>(dsdv.size()));

        double gia;
        if (!SoThuc("Nhap gia moi: ", gia)) {
            return;
        }

        if (gia <= 0) {
            cout << "Gia dich vu phai lon hon 0!\n";
            return;
        }

        dsdv[chon - 1].NhapGia(gia);
        cout << "Cap nhat gia thanh cong!\n";
    }

    void XoaDichVu() {
        if (dsdv.empty()) {
            cout << "Danh sach dich vu dang rong!\n";
            return;
        }

        DanhSachDV();
        cout << "\nNhap so thu tu dich vu can xoa: ";
        int chon = LuaChon(1, static_cast<int>(dsdv.size()));

        dsdv.erase(dsdv.begin() + (chon - 1));
        cout << "Xoa dich vu thanh cong!\n";
    }

    bool XacThucAdmin() {
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

    // QUAN LY TAI KHOAN (ADMIN)
    void QuanLyTaiKhoan() {
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

            chon = LuaChon(0, 7);

            switch (chon) {
                case 1: TaoTK(); break;
                case 2: HienThiDSTK(); break;
                case 3: NapTienTaiKhoan(); break;
                case 4: KhoaTK(); break;
                case 5: MoKhoaTK(); break;
                case 6: XoaTK(); break;
                case 7: XemLichSuGiaoDich(); break;
            }
        } while (chon != 0);
    }

    void HienThiDSTK() {
        cout << "\n=== DANH SACH TAI KHOAN ===\n";
        cout << left << setw(15) << "Username"
             << setw(20) << "Ho ten"
             << setw(15) << "So tien"
             << setw(12) << "Trang thai" << endl;
        cout << string(62, '-') << endl;

        for (auto tk : dstk) {
            cout << left << setw(15) << tk->Username()
                 << setw(20) << tk->HoTen()
                 << setw(15) << tk->SoTien()
                 << setw(12) << (tk->TrangThaiKhoa() ? "Bi khoa" : "Hoat dong") << endl;
        }
    }

    void KhoaTK() {
        string u;
        cout << "Nhap username can khoa: ";
        cin >> u;

        for (auto tk : dstk) {
            if (tk->Username() == u) {
                tk->KhoaTaiKhoan();
                cout << "Tai khoan da bi khoa!\n";
                return;
            }
        }
        cout << "Khong tim thay!\n";
    }

    void MoKhoaTK() {
        string u;
        cout << "Nhap username can mo khoa: ";
        cin >> u;

        for (auto tk : dstk) {
            if (tk->Username() == u) {
                tk->MoKhoaTaiKhoan();
                cout << "Tai khoan da duoc mo khoa!\n";
                return;
            }
        }
        cout << "Khong tim thay!\n";
    }

    void XoaTK() {
        string u;
        cout << "Nhap username can xoa: ";
        cin >> u;

        for (size_t i = 0; i < dstk.size(); i++) {
            if (dstk[i]->Username() == u) {
                delete dstk[i];
                dstk.erase(dstk.begin() + static_cast<long long>(i));
                cout << "Xoa tai khoan thanh cong!\n";
                return;
            }
        }
        cout << "Khong tim thay!\n";
    }

    void NapTienTaiKhoan() {
        if (dstk.empty()) {
            cout << "Chua co tai khoan nao de nap tien!\n";
            return;
        }

        string u;
        cout << "Nhap username can nap tien: ";
        cin >> u;

        for (auto tk : dstk) {
            if (tk->Username() == u) {
                cout << "\n=== NAP TIEN CHO " << tk->Username() << " ===\n";
                cout << "1. 10.000 VND\n";
                cout << "2. 20.000 VND\n";
                cout << "3. 50.000 VND\n";
                cout << "4. 100.000 VND\n";
                cout << "5. Nhap so tien khac\n";
                cout << "0. Tro ve\n";

                int chon = LuaChon(0, 5);
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
                        if (!SoThuc("Nhap so tien: ", tien)) {
                            return;
                        }
                        break;
                }

                if (tien <= 0) {
                    cout << "So tien khong hop le!\n";
                    return;
                }

                tk->NhapSoTien(tk->SoTien() + tien);
                string lichSu = "Admin nap " + to_string((int)tien) + " VND - So du: " + to_string((int)tk->SoTien());
                tk->ThemLichSu(lichSu);

                cout << "Nap tien thanh cong cho " << tk->Username() << "!\n";
                cout << "So du hien tai: " << tk->SoTien() << " VND\n";
                return;
            }
        }

        cout << "Khong tim thay!\n";
    }

    void XemLichSuGiaoDich() {
        string u;
        cout << "Nhap username: ";
        cin >> u;

        for (auto tk : dstk) {
            if (tk->Username() == u) {
                tk->XemLichSu();
                return;
            }
        }
        cout << "Khong tim thay!\n";
    }

    // THONG KE
    void ThongKe() {
        cout << "\n=== THONG KE ===\n";

        double tongtien = 0;
        int sotkhoatdong = 0;
        int sotkbikhoa = 0;
        int dangchoi = 0;

        for (auto tk : dstk) {
            tongtien += tk->SoTien();
            if (tk->TrangThaiKhoa()) {
                sotkbikhoa++;
            } else {
                sotkhoatdong++;
            }
        }

        for (auto &may : dsmay) {
            if (may.TrangThai() == TrangThaiMay::DangChoi) {
                dangchoi++;
            }
        }

        cout << "Tong so tai khoan: " << dstk.size() << endl;
        cout << "Tai khoan hoat dong: " << sotkhoatdong << endl;
        cout << "Tai khoan bi khoa: " << sotkbikhoa << endl;
        cout << "Tong so tien trong he thong: " << tongtien << " VND\n";
        cout << "Tong so may: " << dsmay.size() << endl;
        cout << "May dang choi: " << dangchoi << endl;
    }

    // MENU USER
    void MenuUser(int idx) {
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

            chon = LuaChon(0, 6);

            switch (chon) {
                case 1: dstk[idx]->NapTien(); break;
                case 2: SuDungDV(idx); break;
                case 3: dstk[idx]->DoiMatKhau(); break;
                case 4: MenuChonMay(idx); break;
                case 5: dstk[idx]->HienThi(); break;
                case 6: dstk[idx]->XemLichSu(); break;
            }

        } while (chon != 0);
    }

    // MENU ADMIN
    void MenuAdmin() {
        int chon;
        do {
            cout << "\n=== MENU QUAN LY (ADMIN) ===\n";
            cout << "1. Quan ly tai khoan\n";
            cout << "2. Quan ly may\n";
            cout << "3. Quan ly dich vu\n";
            cout << "4. Thong ke\n";
            cout << "0. Thoat\n";

            chon = LuaChon(0, 4);

            switch (chon) {
                case 1: QuanLyTaiKhoan(); break;
                case 2: QuanLyMay(); break;
                case 3: QuanLyDichVu(); break;
                case 4: ThongKe(); break;
            }

        } while (chon != 0);
    }

    // MENU CHINH
    void menu() {
        int chon;
        do {
            cout << "\n========== CHAO MUNG BAN DEN VOI QUAN NET BINH NGUYEN VO TAN ==========";
            cout << "\n========== MENU ==========\n";
            cout << "1. Tao tai khoan\n";
            cout << "2. Dang nhap\n";
            cout << "3. Quan ly (Admin)\n";
            cout << "0. Thoat\n";

            chon = LuaChon(0, 3);

            switch (chon) {
                case 1: TaoTK(); break;
                case 2: {
                    int idx = DangNhap();
                    if (idx != -1) {
                        MenuUser(idx);
                    }
                    break;
                }
                case 3:
                    if (XacThucAdmin()) {
                        MenuAdmin();
                    }
                    break;
            }

        } while (chon != 0);

        cout << "Tam biet! Hen gap lai!\n";
    }
};

// MAIN
int main() {
    Server s;
    s.menu();
    return 0;
}
