#include "MonHoc.h"
#include "SinhVien.h"
#include "LopTinChi.h"
#include <iostream>
#include <cstring>
#include <iomanip>

// Hàm xóa bộ nhớ đệm nhập liệu
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

// Hàm hiển thị menu chính
void hienThiMenu() {
    std::cout << "\n=== CHUONG TRINH QUAN LY SINH VIEN ===\n";
    std::cout << "1. Quan ly mon hoc\n";
    std::cout << "2. Quan ly sinh vien\n";
    std::cout << "3. Quan ly lop tin chi\n";
    std::cout << "4. Thoat\n";
    std::cout << "Nhap lua chon (1-4): ";
}

// Hàm hiển thị menu môn học
void hienThiMenuMonHoc() {
    std::cout << "\n--- QUAN LY MON HOC ---\n";
    std::cout << "1. Them mon hoc\n";
    std::cout << "2. Xoa mon hoc\n";
    std::cout << "3. Hieu chinh mon hoc\n";
    std::cout << "4. In danh sach mon hoc\n";
    std::cout << "5. Quay lai\n";
    std::cout << "Nhap lua chon (1-5): ";
}

// Hàm hiển thị menu sinh viên
void hienThiMenuSinhVien() {
    std::cout << "\n--- QUAN LY SINH VIEN ---\n";
    std::cout << "1. Them sinh vien\n";
    std::cout << "2. Xoa sinh vien\n";
    std::cout << "3. Hieu chinh sinh vien\n";
    std::cout << "4. In danh sách sinh vien\n";
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
    std::cout << "11. Quay lai\n";
    std::cout << "Nhap lua chon (1-11): ";
}

// Hàm nhập thông tin môn học
void nhapMonHoc(MonHoc &mh) {
    std::cout << "Nhap ma mon hoc (toi da 10 ky tu): ";
    std::cin.getline(mh.MAMH, 11);
    std::cout << "Nhap ten mon hoc (toi da 50 ky tu): ";
    std::cin.getline(mh.TENMH, 51);
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
    if (TimMonHocTheoMa(dsMH, ltc.MAMH) == -1) {
        std::cerr << "Lỗi: Mã môn học '" << ltc.MAMH << "' không tồn tại!\n";
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
                    std::cerr << "Lỗi: Mã môn học không được rỗng!\n";
                } else if (ThemMonHoc(dsMH, mh)) {
                    std::cout << "Đã thêm môn học '" << mh.MAMH << "' thành công.\n";
                }
                break;
            }
            case 2: { // Xóa môn học
                char maMH[11];
                std::cout << "Nhap ma mon hoc can xoa: ";
                std::cin.getline(maMH, 11);
                if (XoaMonHocTheoMa(dsMH, maMH)) {
                    std::cout << "Đã xóa môn học '" << maMH << "' thành công.\n";
                }
                break;
            }
            case 3: { // Hiệu chỉnh môn học
                char maMH[11];
                std::cout << "Nhap ma mon hoc can hieu chinh: ";
                std::cin.getline(maMH, 11);
                MonHoc mhMoi;
                std::cout << "Nhap ten mon hoc moi (toi da 50 ky tu): ";
                std::cin.getline(mhMoi.TENMH, 51);
                strcpy(mhMoi.MAMH, maMH); // Giữ nguyên mã
                if (HieuChinhMonHoc(dsMH, maMH, mhMoi)) {
                    std::cout << "Đã hiệu chỉnh môn học '" << maMH << "' thành công.\n";
                }
                break;
            }
            case 4: { // In danh sách môn học
                SapXepMonHocTheoTen(dsMH);
                InDanhSachMonHoc(dsMH);
                break;
            }
            case 5: // Quay lại
                break;
            default:
                std::cerr << "Lỗi: Lựa chọn không hợp lệ!\n";
        }
    } while (luaChon != 5);
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
                    std::cerr << "Lỗi: Mã sinh viên không được rỗng!\n";
                } else if (ThemSinhVien(dsSV, sv)) {
                    std::cout << "Đã thêm sinh viên '" << sv.MASV << "' thành công.\n";
                }
                break;
            }
            case 2: { // Xóa sinh viên
                char maSV[MAX_MASV_LEN + 1];
                std::cout << "Nhap ma sinh vien can xoa: ";
                std::cin.getline(maSV, MAX_MASV_LEN + 1);
                if (XoaSinhVienTheoMa(dsSV, maSV)) {
                    std::cout << "Đã xóa sinh viên '" << maSV << "' thành công.\n";
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
                    std::cout << "Đã hiệu chỉnh sinh viên '" << maSV << "' thành công.\n";
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
                std::cerr << "Lỗi: Lựa chọn không hợp lệ!\n";
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
                        std::cout << "Đã thêm lớp tín chỉ với mã " << maLTC << " thành công.\n";
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
                    std::cout << "Đã xóa lớp tín chỉ " << maLTC << " thành công.\n";
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
                    std::cout << "Đã hiệu chỉnh lớp tín chỉ " << maLTC << " thành công.\n";
                }
                break;
            }
            case 4: { // Hủy lớp tín chỉ
                int maLTC;
                std::cout << "Nhap ma lop tin chi can huy: ";
                std::cin >> maLTC;
                clearInputBuffer();
                if (HuyLopTinChi(dsLTC, maLTC)) {
                    std::cout << "Đã hủy lớp tín chỉ " << maLTC << " thành công.\n";
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
                    std::cout << "Đã thêm sinh viên '" << maSV << "' vào lớp tín chỉ " << maLTC << " thành công.\n";
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
                    std::cout << "Đã xóa sinh viên '" << maSV << "' khỏi lớp tín chỉ " << maLTC << " thành công.\n";
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
                    std::cout << "Đã nhập điểm " << diem << " cho sinh viên '" << maSV << "' trong lớp tín chỉ " << maLTC << ".\n";
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
            case 11: // Quay lại
                break;
            default:
                std::cerr << "Lỗi: Lựa chọn không hợp lệ!\n";
        }
    } while (luaChon != 11);
}

int main() {
    DanhSachMonHoc dsMH;
    DanhSachSinhVien dsSV;
    DanhSachLopTinChi dsLTC;

    // Khởi tạo danh sách
    KhoiTaoDSMonHoc(dsMH);
    KhoiTaoDSSinhVien(dsSV);
    KhoiTaoDSLTC(dsLTC);

    int luaChon;
    do {
        hienThiMenu();
        std::cin >> luaChon;
        clearInputBuffer();

        switch (luaChon) {
            case 1: // Quản lý môn học
                quanLyMonHoc(dsMH);
                break;
            case 2: // Quản lý sinh viên
                quanLySinhVien(dsSV);
                break;
            case 3: // Quản lý lớp tín chỉ
                quanLyLopTinChi(dsLTC, dsMH, dsSV);
                break;
            case 4: // Thoát
                std::cout << "Cam on ban da su dung chuong trinh!\n";
                break;
            default:
                std::cerr << "Lỗi: Lựa chọn không hợp lệ!\n";
        }
    } while (luaChon != 4);

    // Giải phóng bộ nhớ
    GiaiPhongDSMonHoc(dsMH);
    GiaiPhongDSSinhVien(dsSV);
    GiaiPhongDSLTC(dsLTC);

    return 0;
}