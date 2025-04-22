#ifndef SINHVIEN_H
#define SINHVIEN_H

// Kích thước buffer cho các trường dữ liệu
#define MAX_MASV_LEN 15
#define MAX_HO_LEN 30
#define MAX_TEN_LEN 10
#define MAX_PHAI_LEN 4 // Nam/Nu/Khac
#define MAX_SODT_LEN 15

// Cấu trúc lưu thông tin sinh viên
struct SinhVien {
    char MASV[MAX_MASV_LEN + 1];  // Mã sinh viên, tối đa 15 ký tự + null terminator
    char HO[MAX_HO_LEN + 1];      // Họ sinh viên, tối đa 30 ký tự + null terminator
    char TEN[MAX_TEN_LEN + 1];    // Tên sinh viên, tối đa 10 ký tự + null terminator
    char PHAI[MAX_PHAI_LEN + 1];  // Phái (Nam/Nữ/Khác), tối đa 4 ký tự + null terminator
    char SODT[MAX_SODT_LEN + 1];  // Số điện thoại, tối đa 15 ký tự + null terminator
	char LOP[16];
};

// Node trong danh sách liên kết sinh viên
struct NodeSV {
    SinhVien data; // Dữ liệu sinh viên
    NodeSV* next;  // Con trỏ tới node kế tiếp
};

// Kiểu dữ liệu cho danh sách (con trỏ đầu của danh sách)
typedef NodeSV* DanhSachSinhVien;

// Các hàm quản lý cơ bản
void KhoiTaoDSSinhVien(DanhSachSinhVien &first);
void GiaiPhongDSSinhVien(DanhSachSinhVien &first);
bool IsEmpty(const DanhSachSinhVien first);

// Các hàm thao tác trên danh sách
NodeSV* TimSinhVienTheoMa(DanhSachSinhVien first, const char* maSV);
bool ThemSinhVien(DanhSachSinhVien &first, SinhVien sv);
bool XoaSinhVienTheoMa(DanhSachSinhVien &first, const char* maSV);
bool HieuChinhSinhVien(DanhSachSinhVien first, const char* maSV, const SinhVien svMoi);

// Hàm xuất danh sách
void InDanhSachSinhVien(const DanhSachSinhVien first);

#endif // SINHVIEN_H