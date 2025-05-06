#include "MonHoc.h"
#include "SinhVien.h"
#include "LopTinChi.h"
#include "Diem.h"
#include "LopSV.h"
#include <iostream>
#include <cstring>
#include <iomanip>

// Hàm xóa bộ nhớ đệm nhập liệu
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

void hienThiMenuLopSV() {
    std::cout << "\n--- QUAN LY LOP SINH VIEN ---\n";
    std::cout << "1. Them lop sinh vien\n";
    std::cout << "2. Xoa lop sinh vien\n";
    std::cout << "3. Hieu chinh lop sinh vien\n";
    std::cout << "4. Nhap sinh vien cho lop\n";
    std::cout << "5. In danh sach sinh vien cua lop\n";
    std::cout << "6. Quay lai\n";
    std::cout << "Nhap lua chon (1-6): ";
}

void quanLyLopSV(DanhSachLopSV &ds) {
    int luaChon;
    do {
        hienThiMenuLopSV();
        std::cin >> luaChon;
        std::cin.ignore(10000, '\n');

        switch (luaChon) {
            case 1: {
                LopSV lop;
                std::cout << "Nhap ma lop (toi da 15 ky tu): ";
                std::cin.getline(lop.MALOP, 16);
                std::cout << "Nhap ten lop (toi da 50 ky tu): ";
                std::cin.getline(lop.TENLOP, 51);
                lop.dssv = NULL;
                ThemLopSV(ds, lop);
                break;
            }
            case 2: {
                char maLop[16];
                std::cout << "Nhap ma lop can xoa: ";
                std::cin.getline(maLop, 16);
                XoaLopSV(ds, maLop);
                break;
            }
            case 3: {
                char maLop[16];
                std::cout << "Nhap ma lop can hieu chinh: ";
                std::cin.getline(maLop, 16);
                LopSV lopMoi;
                std::cout << "Nhap ten lop moi: ";
                std::cin.getline(lopMoi.TENLOP, 51);
                HieuChinhLopSV(ds, maLop, lopMoi);
                break;
            }
            case 4: {
                char maLop[16];
                std::cout << "Nhap ma lop de them sinh vien: ";
                std::cin.getline(maLop, 16);
                int index = TimLopSV(ds, maLop);
                if (index == -1) {
                    std::cerr << "Khong tim thay lop '" << maLop << "'.\n";
                } else {
                    while (true) {
                        SinhVien sv;
                        std::cout << "Nhap ma sinh vien (nhap rong de dung): ";
                        std::cin.getline(sv.MASV, MAX_MASV_LEN + 1);
                        if (strlen(sv.MASV) == 0) break;
                        std::cout << "Nhap ho sinh vien: ";
                        std::cin.getline(sv.HO, MAX_HO_LEN + 1);
                        std::cout << "Nhap ten sinh vien: ";
                        std::cin.getline(sv.TEN, MAX_TEN_LEN + 1);
                        std::cout << "Nhap phai (Nam/Nu/Khac): ";
                        std::cin.getline(sv.PHAI, MAX_PHAI_LEN + 1);
                        std::cout << "Nhap so dien thoai: ";
                        std::cin.getline(sv.SODT, MAX_SODT_LEN + 1);
                        strcpy(sv.LOP, maLop); // Gán lớp cho sinh viên
                        ThemSinhVien(ds.lop[index].dssv, sv);
                    }
                }
                break;
            }
            case 5: {
                char maLop[16];
                std::cout << "Nhap ma lop de in danh sach sinh vien: ";
                std::cin.getline(maLop, 16);
                int index = TimLopSV(ds, maLop);
                if (index == -1) {
                    std::cerr << "Khong tim thay lop '" << maLop << "'.\n";
                } else {
                    InDanhSachSinhVienSapXepTheoTen(ds.lop[index].dssv);
                }
                break;
            }
            case 6:
                break;
            default:
                std::cerr << "Lua chon khong hop le!\n";
        }
    } while (luaChon != 6);
}

void hienThiMenu() {
    std::cout << "\n=== CHUONG TRINH QUAN LY SINH VIEN ===\n";
    std::cout << "1. Quan ly mon hoc\n";
    std::cout << "2. Quan ly lop sinh vien\n"; // <-- Thêm
    std::cout << "3. Quan ly sinh vien\n";
    std::cout << "4. Quan ly lop tin chi\n";
    std::cout << "5. Thoat\n";
    std::cout << "Nhap lua chon (1-5): ";
}


// Hàm hiển thị menu môn học
void hienThiMenuMonHoc() {
    std::cout << "\n--- QUAN LY MON HOC ---\n";
    std::cout << "1. Them mon hoc\n";
    std::cout << "2. Xoa mon hoc\n";
    std::cout << "3. Hieu chinh mon hoc\n";
    std::cout << "4. In danh sach mon hoc (theo MAMH)\n";
    std::cout << "5. In danh sach mon hoc (theo TENMH)\n";
    std::cout << "6. Quay lai\n";
    std::cout << "Nhap lua chon (1-6): ";
}

// Hàm hiển thị menu sinh viên
void hienThiMenuSinhVien() {
    std::cout << "\n--- QUAN LY SINH VIEN ---\n";
    std::cout << "1. Them sinh vien\n";
    std::cout << "2. Xoa sinh vien\n";
    std::cout << "3. Hieu chinh sinh vien\n";
    std::cout << "4. In danh sach sinh vien\n";
    std::cout << "5. Quay lai\n";
    std::cout << "Nhap lua chon (1-5): ";
}

// Hàm hiển thị menu lớp tín chỉ
void hienThiMenuLopTinChi() {
    std::cout << "\n--- QUAN LY LOP TIN CHI ---\n";
    std::cout << "1. Them lop tin chi\n";
    std::cout << "2. Xoa lop tin chi\n";
    std::cout << "3. Hieu chinh lop tin chi\n";
    std::cout << "4. Huy lop tin chi\n";
    std::cout << "5. Them sinh vien vao lop tin chi\n";
    std::cout << "6. Xoa sinh vien khoi lop tin chi\n";
    std::cout << "7. Nhap diem sinh vien\n";
    std::cout << "8. In danh sach sinh vien da dang ky\n";
    std::cout << "9. In danh sach sinh vien sap xep\n";
    std::cout << "10. In bang diem lop tin chi\n";
    std::cout << "11. Huy lop tu dong theo nien khoa va hoc ky\n";
    std::cout << "12. Nhap diem theo bang\n";
    std::cout << "13. In bang diem mon hoc\n";
    std::cout << "14. In bang diem trung binh khoa hoc\n";
    std::cout << "15. In bang diem tong ket\n";
    std::cout << "16. Quay lai\n";
    std::cout << "Nhap lua chon (1-16): ";
}

// Hàm nhập thông tin môn học
void nhapMonHoc(MonHoc &mh) {
    std::cout << "Nhap ma mon hoc (toi da 10 ky tu): ";
    std::cin.getline(mh.MAMH, 11);
    std::cout << "Nhap ten mon hoc (toi da 50 ky tu): ";
    std::cin.getline(mh.TENMH, 51);
    std::cout << "Nhap so tin chi ly thuyet: ";
    std::cin >> mh.STCLT;
    std::cout << "Nhap so tin chi thuc hanh: ";
    std::cin >> mh.STCTH;
    clearInputBuffer();
}

// Hàm nhập thông tin sinh viên
void nhapSinhVien(SinhVien &sv) {
    std::cout << "Nhap ma sinh vien (toi da 15 ky tu): ";
    std::cin.getline(sv.MASV, MAX_MASV_LEN + 1);
    std::cout << "Nhap ho (toi da 30 ky tu): ";
    std::cin.getline(sv.HO, MAX_HO_LEN + 1);
    std::cout << "Nhap ten (toi da 10 ky tu): ";
    std::cin.getline(sv.TEN, MAX_TEN_LEN + 1);
    std::cout << "Nhap phai (Nam/Nu/Khac): ";
    std::cin.getline(sv.PHAI, MAX_PHAI_LEN + 1);
    std::cout << "Nhap so dien thoai (toi da 15 ky tu): ";
    std::cin.getline(sv.SODT, MAX_SODT_LEN + 1);
    std::cout << "Nhap lop (toi da 15 ky tu): ";
    std::cin.getline(sv.LOP, 16);
}

// Hàm nhập thông tin lớp tín chỉ
void nhapLopTinChi(LopTinChi &ltc, const DanhSachMonHoc &dsMH) {
    std::cout << "Nhap ma mon hoc (toi da 10 ky tu): ";
    std::cin.getline(ltc.MAMH, 11);
    // Kiểm tra MAMH tồn tại
    if (!TimMonHocTheoMa(dsMH, ltc.MAMH)) {
        std::cerr << "Loi: Ma mon hoc '" << ltc.MAMH << "' khong ton tai!\n";
        ltc.MAMH[0] = '\0'; // Đánh dấu không hợp lệ
        return;
    }
    std::cout << "Nhap nien khoa (vi du: 2023): ";
    std::cin >> ltc.nienkhoa;
    std::cout << "Nhap hoc ky (1-3): ";
    std::cin >> ltc.hocky;
    std::cout << "Nhap nhom (1-10): ";
    std::cin >> ltc.nhom;
    std::cout << "Nhap so sinh vien toi thieu: ";
    std::cin >> ltc.sv_min;
    std::cout << "Nhap so sinh vien toi da: ";
    std::cin >> ltc.sv_max;
    clearInputBuffer();
    ltc.MALOPTC = 0; // Để tự động gán
    ltc.huyLop = false;
    ltc.soSVDK = 0;
    KhoiTaoDSDangKy(ltc.dssvdk);
}

// Hàm quản lý môn học
void quanLyMonHoc(DanhSachMonHoc &dsMH) {
    int luaChon;
    do {
        hienThiMenuMonHoc();
        std::cin >> luaChon;
        clearInputBuffer();

        switch (luaChon) {
            case 1: { // Thêm môn học
                MonHoc mh;
                nhapMonHoc(mh);
                if (mh.MAMH[0] == '\0') {
                    std::cerr << "Loi: Ma mon hoc khong duoc rong!\n";
                } else {
                    dsMH = ThemMonHoc(dsMH, mh);
                    std::cout << "Da them mon hoc '" << mh.MAMH << "' thanh cong.\n";
                }
                break;
            }
            case 2: { // Xóa môn học
                char maMH[11];
                std::cout << "Nhap ma mon hoc can xoa: ";
                std::cin.getline(maMH, 11);
                dsMH = XoaMonHoc(dsMH, maMH);
                break;
            }
            case 3: { // Hiệu chỉnh môn học
                char maMH[11];
                std::cout << "Nhap ma mon hoc can hieu chinh: ";
                std::cin.getline(maMH, 11);
                MonHoc mhMoi;
                nhapMonHoc(mhMoi);
                CapNhatMonHoc(dsMH, maMH, mhMoi);
                break;
            }
            case 4: { // In danh sách môn học (theo MAMH)
                InDanhSachMonHoc(dsMH);
                break;
            }
            case 5: { // In danh sách môn học (theo TENMH)
                InDanhSachMonHocSapXepTheoTen(dsMH);
                break;
            }
            case 6: // Quay lại
                break;
            default:
                std::cerr << "Loi: Lua chon khong hop le!\n";
        }
    } while (luaChon != 6);
}

// Hàm quản lý sinh viên
void quanLySinhVien(DanhSachSinhVien &dsSV) {
    int luaChon;
    do {
        hienThiMenuSinhVien();
        std::cin >> luaChon;
        clearInputBuffer();

        switch (luaChon) {
            case 1: { // Thêm sinh viên
                SinhVien sv;
                nhapSinhVien(sv);
                if (sv.MASV[0] == '\0') {
                    std::cerr << "Loi: Ma sinh vien khong duoc rong!\n";
                } else if (ThemSinhVien(dsSV, sv)) {
                    std::cout << "Da them sinh vien '" << sv.MASV << "' thanh cong.\n";
                }
                break;
            }
            case 2: { // Xóa sinh viên
                char maSV[MAX_MASV_LEN + 1];
                std::cout << "Nhap ma sinh vien can xoa: ";
                std::cin.getline(maSV, MAX_MASV_LEN + 1);
                if (XoaSinhVienTheoMa(dsSV, maSV)) {
                    std::cout << "Da xoa sinh vien '" << maSV << "' thanh cong.\n";
                }
                break;
            }
            case 3: { // Hiệu chỉnh sinh viên
                char maSV[MAX_MASV_LEN + 1];
                std::cout << "Nhap ma sinh vien can hieu chinh: ";
                std::cin.getline(maSV, MAX_MASV_LEN + 1);
                SinhVien svMoi;
                nhapSinhVien(svMoi);
                strcpy(svMoi.MASV, maSV); // Giữ nguyên mã
                if (HieuChinhSinhVien(dsSV, maSV, svMoi)) {
                    std::cout << "Da hieu chinh sinh vien '" << maSV << "' thanh cong.\n";
                }
                break;
            }
            case 4: { // In danh sách sinh viên
                InDanhSachSinhVien(dsSV);
                break;
            }
            case 5: // Quay lại
                break;
            default:
                std::cerr << "Loi: Lua chon khong hop le!\n";
        }
    } while (luaChon != 5);
}

// Hàm quản lý lớp tín chỉ
void quanLyLopTinChi(DanhSachLopTinChi &dsLTC, const DanhSachMonHoc &dsMH, const DanhSachSinhVien &dsSV) {
    int luaChon;
    do {
        hienThiMenuLopTinChi();
        std::cin >> luaChon;
        clearInputBuffer();

        switch (luaChon) {
            case 1: { // Thêm lớp tín chỉ
                LopTinChi ltc;
                nhapLopTinChi(ltc, dsMH);
                if (ltc.MAMH[0] != '\0') {
                    int maLTC = ThemLopTC(dsLTC, ltc);
                    if (maLTC != -1) {
                        std::cout << "Da them lop tin chi voi ma " << maLTC << " thanh cong.\n";
                    }
                }
                break;
            }
            case 2: { // Xóa lớp tín chỉ
                int maLTC;
                std::cout << "Nhap ma lop tin chi can xoa: ";
                std::cin >> maLTC;
                clearInputBuffer();
                if (XoaLopTCTheoMa(dsLTC, maLTC)) {
                    std::cout << "Da xoa lop tin chi " << maLTC << " thanh cong.\n";
                }
                break;
            }
            case 3: { // Hiệu chỉnh lớp tín chỉ
                int maLTC;
                std::cout << "Nhap ma lop tin chi can hieu chinh: ";
                std::cin >> maLTC;
                LopTinChi ltcMoi;
                std::cout << "Nhap so sinh vien toi thieu moi: ";
                std::cin >> ltcMoi.sv_min;
                std::cout << "Nhap so sinh vien toi da moi: ";
                std::cin >> ltcMoi.sv_max;
                std::cout << "Nhap trang thai huy lop (0: khong huy, 1: huy): ";
                int huyLop;
                std::cin >> huyLop;
                ltcMoi.huyLop = (huyLop == 1);
                clearInputBuffer();
                if (HieuChinhLopTinChi(dsLTC, maLTC, ltcMoi)) {
                    std::cout << "Da hieu chinh lop tin chi " << maLTC << " thanh cong.\n";
                }
                break;
            }
            case 4: { // Hủy lớp tín chỉ
                int maLTC;
                std::cout << "Nhap ma lop tin chi can huy: ";
                std::cin >> maLTC;
                clearInputBuffer();
                if (HuyLopTinChi(dsLTC, maLTC)) {
                    std::cout << "Da huy lop tin chi " << maLTC << " thanh cong.\n";
                }
                break;
            }
            case 5: { // Thêm sinh viên vào lớp tín chỉ
                int maLTC;
                char maSV[MAX_MASV_LEN + 1];
                std::cout << "Nhap ma lop tin chi: ";
                std::cin >> maLTC;
                clearInputBuffer();
                std::cout << "Nhap ma sinh vien: ";
                std::cin.getline(maSV, MAX_MASV_LEN + 1);
                if (ThemSVVaoLopTC(dsLTC, dsSV, maLTC, maSV)) {
                    std::cout << "Da them sinh vien '" << maSV << "' vao lop tin chi " << maLTC << " thanh cong.\n";
                }
                break;
            }
            case 6: { // Xóa sinh viên khỏi lớp tín chỉ
                int maLTC;
                char maSV[MAX_MASV_LEN + 1];
                std::cout << "Nhap ma lop tin chi: ";
                std::cin >> maLTC;
                clearInputBuffer();
                std::cout << "Nhap ma sinh vien: ";
                std::cin.getline(maSV, MAX_MASV_LEN + 1);
                if (XoaSVKhoiLopTC(dsLTC, maLTC, maSV)) {
                    std::cout << "Da xoa sinh vien '" << maSV << "' khoi lop tin chi " << maLTC << " thanh cong.\n";
                }
                break;
            }
            case 7: { // Nhập điểm sinh viên
                int maLTC;
                char maSV[MAX_MASV_LEN + 1];
                float diem;
                std::cout << "Nhap ma lop tin chi: ";
                std::cin >> maLTC;
                clearInputBuffer();
                std::cout << "Nhap ma sinh vien: ";
                std::cin.getline(maSV, MAX_MASV_LEN + 1);
                std::cout << "Nhap diem (0.0 - 10.0): ";
                std::cin >> diem;
                clearInputBuffer();
                if (NhapDiemSinhVienLopTC(dsLTC, maLTC, maSV, diem)) {
                    std::cout << "Da nhap diem " << diem << " cho sinh vien '" << maSV << "' trong lop tin chi " << maLTC << ".\n";
                }
                break;
            }
            case 8: { // In danh sách sinh viên đã đăng ký
                int maLTC;
                std::cout << "Nhap ma lop tin chi: ";
                std::cin >> maLTC;
                clearInputBuffer();
                InDSSVDaDangKyCuaLop(dsLTC, dsSV, maLTC);
                break;
            }
            case 9: { // In danh sách sinh viên sắp xếp
                int maLTC;
                std::cout << "Nhap ma lop tin chi: ";
                std::cin >> maLTC;
                clearInputBuffer();
                InDSSVSapXepCuaLop(dsLTC, dsSV, maLTC);
                break;
            }
            case 10: { // In bảng điểm lớp tín chỉ
                int maLTC;
                std::cout << "Nhap ma lop tin chi: ";
                std::cin >> maLTC;
                clearInputBuffer();
                InBangDiemLop(dsLTC, dsSV, maLTC);
                break;
            }
            case 11: { // Hủy tự động theo niên khóa và học kỳ
                int nienKhoa, hocKy;
                std::cout << "Nhap nien khoa: ";
                std::cin >> nienKhoa;
                std::cout << "Nhap hoc ky: ";
                std::cin >> hocKy;
                clearInputBuffer();
                HuyLopTuDongTheoNienKhoaHocKy(dsLTC, nienKhoa, hocKy);
                break;
            }
            case 12: { // Nhập điểm theo bảng
                int maLTC;
                std::cout << "Nhap ma lop tin chi: ";
                std::cin >> maLTC;
                clearInputBuffer();
                NhapDiemTheoBang(dsLTC, dsSV, maLTC);
                break;
            }
            case 13: { // In bảng điểm môn học
                char maMH[11];
                std::cout << "Nhap ma mon hoc: ";
                std::cin.getline(maMH, 11);
                InBangDiemMonHoc(dsLTC, dsSV, dsMH, maMH);
                break;
            }
            case 14: { // In bảng điểm trung bình khóa học
                char maLop[16];
                std::cout << "Nhap ma lop: ";
                std::cin.getline(maLop, 16);
                InBangDiemTrungBinhKhoa(dsLTC, dsSV, dsMH, maLop);
                break;
            }
            case 15: { // In bảng điểm tổng kết
                char maLop[16];
                std::cout << "Nhap ma lop: ";
                std::cin.getline(maLop, 16);
                InBangDiemTongKet(dsLTC, dsSV, dsMH, maLop);
                break;
            }
            case 16: // Quay lại
                break;
            default:
                std::cerr << "Loi: Lua chon khong hop le!\n";
        }
    } while (luaChon != 16);
}

int main() {
    DanhSachMonHoc dsMH = NULL;
	DanhSachLopSV dsLopSV;
	DanhSachSinhVien dsSV;
	DanhSachLopTinChi dsLTC;

    // Khởi tạo danh sách sinh viên và lớp tín chỉ
    KhoiTaoDSLopSV(dsLopSV);
    KhoiTaoDSSinhVien(dsSV);
    KhoiTaoDSLTC(dsLTC);

    int luaChon;
    do {
        hienThiMenu();
        std::cin >> luaChon;
        clearInputBuffer();

        switch (luaChon) {
		    case 1:
		        quanLyMonHoc(dsMH);
		        break;
		    case 2:
		        quanLyLopSV(dsLopSV); // <-- Thêm
		        break;
		    case 3:
		        quanLySinhVien(dsSV);
		        break;
		    case 4:
		        quanLyLopTinChi(dsLTC, dsMH, dsSV);
		        break;
		    case 5:
		        std::cout << "Cam on ban da su dung chuong trinh!\n";
		        break;
		    default:
		        std::cerr << "Loi: Lua chon khong hop le!\n";
		}
    } while (luaChon != 4);

    // Giải phóng bộ nhớ
    GiaiPhongDSMonHoc(dsMH);
    GiaiPhongDSSinhVien(dsSV);
    GiaiPhongDSLTC(dsLTC);

    return 0;
}