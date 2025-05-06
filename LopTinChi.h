
#ifndef LOPTINCHI_H
#define LOPTINCHI_H
#include "SinhVien.h"
#include <fstream>

// --- Khai báo struct DangKy và NodeDK ---
struct DangKy {
    char MASV[MAX_MASV_LEN + 1]; // Sử dụng hằng số từ SinhVien.h nếu có
    float DIEM;
    bool daCoDiem; // Cờ báo trạng thái nhập điểm
};

struct NodeDK {
    DangKy data;
    NodeDK* next;
};

typedef NodeDK* DanhSachDangKy; // Con trỏ đầu DSLK đăng ký

// --- Khai báo struct LopTinChi ---
struct LopTinChi {
    int MALOPTC;     // Mã lớp tín chỉ
    char MAMH[11];   // Mã môn học
    int nienkhoa;    // Niên khóa
    int hocky;       // Học kỳ
    int nhom;        // Nhóm
    int sv_min;      // Số SV tối thiểu
    int sv_max;      // Số SV tối đa
    bool huyLop;     // Cờ hủy lớp
    DanhSachDangKy dssvdk; // Con trỏ tới DSLK sinh viên đăng ký
    int soSVDK;      // Số lượng SV đã đăng ký hiện tại
};

// --- Khai báo cấu trúc quản lý danh sách lớp tín chỉ ---
const int MAX_LTC = 10000; // Số lượng lớp tín chỉ tối đa
struct DanhSachLopTinChi {
    LopTinChi* nodes[MAX_LTC]; // Mảng con trỏ tới các lớp tín chỉ
    int soLuong;               // Số lượng lớp tín chỉ hiện có
};

// --- Khai báo các hàm xử lý DanhSachDangKy ---
void KhoiTaoDSDangKy(DanhSachDangKy &firstDK);
void GiaiPhongDSDangKy(DanhSachDangKy &firstDK);
bool ThemDangKyVaoDSLK(DanhSachDangKy &firstDK, const DangKy &dk);
NodeDK* TimDangKyTheoMASV(DanhSachDangKy firstDK, const char* maSV);
bool XoaDangKyTheoMASV(DanhSachDangKy &firstDK, const char* maSV);
int DemSoLuongDangKy(DanhSachDangKy firstDK);

// --- Khai báo các hàm xử lý DanhSachLopTinChi ---
void KhoiTaoDSLTC(DanhSachLopTinChi &ds);
void GiaiPhongDSLTC(DanhSachLopTinChi &ds);
int TimLopTinChiTheoMa(const DanhSachLopTinChi &ds, int maLTC);
LopTinChi* TimLopTinChiTheoTieuChi(const DanhSachLopTinChi &ds, const char* maMH, int nienKhoa, int hocKy, int nhom);
int ThemLopTC(DanhSachLopTinChi &ds, const LopTinChi &lopTCData);
bool XoaLopTCTheoMa(DanhSachLopTinChi &ds, int maLTC);
bool HieuChinhLopTinChi(DanhSachLopTinChi &ds, int maLTC, const LopTinChi &lopTCMoi);
bool HuyLopTinChi(DanhSachLopTinChi &ds, int maLTC);
int TimMaLopTCMax(const DanhSachLopTinChi &ds);
void SapXepDSLTC(DanhSachLopTinChi &ds, bool tangDan = true);

// Trong LopTinChi.h, thêm vào phần khai báo hàm
void HuyLopTuDongTheoNienKhoaHocKy(DanhSachLopTinChi &ds, int nienKhoa, int hocKy);

// --- Khai báo các hàm thao tác nghiệp vụ ---
bool ThemSVVaoLopTC(DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, int maLTC, const char* maSV);
bool XoaSVKhoiLopTC(DanhSachLopTinChi &dsLTC, int maLTC, const char* maSV);
bool NhapDiemSinhVienLopTC(DanhSachLopTinChi &dsLTC, int maLTC, const char* maSV, float diem);
void InDSSVDaDangKyCuaLop(const DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, int maLTC);
void InDSSVSapXepCuaLop(const DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, int maLTC);
void InBangDiemLop(const DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, int maLTC);


void SaveDanhSachDangKy(DanhSachDangKy first, std::ofstream &file);
void LoadDanhSachLopTinChi(DanhSachLopTinChi &ds, const char* filename);
#endif // LOPTINCHI_H
// --- END OF FILE LopTinChi.h ---