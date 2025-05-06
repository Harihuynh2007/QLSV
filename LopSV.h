#ifndef LOPSV_H
#define LOPSV_H

#include "SinhVien.h"

struct LopSV {
    char MALOP[16];
    char TENLOP[51];
    DanhSachSinhVien dssv; // 
};

struct DanhSachLopSV {
    LopSV* lop;
    int n; // So lop hien tai
    int capacity; // Dung luong mang
};


void KhoiTaoDSLopSV(DanhSachLopSV &ds);
void GiaiPhongDSLopSV(DanhSachLopSV &ds);
int TimLopSV(const DanhSachLopSV &ds, const char* maLop);
bool ThemLopSV(DanhSachLopSV &ds, LopSV lop);
bool XoaLopSV(DanhSachLopSV &ds, const char* maLop);
bool HieuChinhLopSV(DanhSachLopSV &ds, const char* maLop, LopSV lopMoi);
void ExtendLopArray(DanhSachLopSV &ds);

// LopSV.h
void SaveDanhSachLopSV(DanhSachLopSV &ds, const char* filename);
void LoadDanhSachLopSV(DanhSachLopSV &ds, const char* filename);



#endif // LOPSV_H