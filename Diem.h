#ifndef DIEM_H
#define DIEM_H

#include "LopTinChi.h"
#include "SinhVien.h"


bool NhapDiemSinhVienLopTC(DanhSachLopTinChi &dsLTC, int maLTC, const char* maSV, float diem);


void InBangDiemMonHoc(const DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, const char* maMH);


void InBangDiemTrungBinhKhoa(const DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, const char* tenLop);


void InBangDiemTongKet(const DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, const char* maSV);

#endif // DIEM_H