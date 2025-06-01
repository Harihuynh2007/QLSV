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
    char MASV[MAX_MASV_LEN + 1];  
    char HO[MAX_HO_LEN + 1];      
    char TEN[MAX_TEN_LEN + 1];    
    char PHAI[MAX_PHAI_LEN + 1];  
    char SODT[MAX_SODT_LEN + 1];  
	char LOP[16];
};


struct NodeSV {
    SinhVien data; // Dữ liệu sinh viên
    NodeSV* next;  // Con trỏ tới node kế tiếp
};

// kieu du lieu cho danh sach
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
void InDanhSachSinhVienSapXepTheoTen(const DanhSachSinhVien first);


#endif // SINHVIEN_H