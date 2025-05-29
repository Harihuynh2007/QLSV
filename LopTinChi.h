
#ifndef LOPTINCHI_H
#define LOPTINCHI_H
#include "SinhVien.h"
#include <fstream>

struct NodeAVL;
typedef NodeAVL* DanhSachMonHoc;

struct DangKy {
    char MASV[MAX_MASV_LEN + 1]; 
    float DIEM;
    bool daCoDiem; // bao trang thai da co diem
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


const int MAX_LTC = 10000; 
struct DanhSachLopTinChi {
    LopTinChi* nodes[MAX_LTC]; // Mang con tro toi lop tin chi
    int soLuong;               // So luong lop tin chi hien co
};


void KhoiTaoDSDangKy(DanhSachDangKy &firstDK);
void GiaiPhongDSDangKy(DanhSachDangKy &firstDK);
bool ThemDangKyVaoDSLK(DanhSachDangKy &firstDK, const DangKy &dk);
NodeDK* TimDangKyTheoMASV(DanhSachDangKy firstDK, const char* maSV);
bool XoaDangKyTheoMASV(DanhSachDangKy &firstDK, const char* maSV);
int DemSoLuongDangKy(DanhSachDangKy firstDK);


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

void HuyLopTuDongTheoNienKhoaHocKy(DanhSachLopTinChi &ds, int nienKhoa, int hocKy);

bool ThemSVVaoLopTC(DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, int maLTC, const char* maSV);
bool XoaSVKhoiLopTC(DanhSachLopTinChi &dsLTC, int maLTC, const char* maSV);
bool NhapDiemSinhVienLopTC(DanhSachLopTinChi &dsLTC, int maLTC, const char* maSV, float diem);
void InDSSVDaDangKyCuaLop(const DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, int maLTC);
void InDSSVSapXepCuaLop(const DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, int maLTC);
void InBangDiemLop(const DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, int maLTC);


void SaveDanhSachLopTinChi(DanhSachLopTinChi &ds, const char* filename);
void LoadDanhSachLopTinChi(DanhSachLopTinChi &ds, const char* filename);

void DangKyLopTinChiTheoHocKy(DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, const DanhSachMonHoc &dsMH);

#endif 
// --- END OF FILE LopTinChi.h ---