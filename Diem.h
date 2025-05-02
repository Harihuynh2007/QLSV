#ifndef DIEM_H
#define DIEM_H

#include "LopTinChi.h"
#include "SinhVien.h"
#include "MonHoc.h"

bool NhapDiemSinhVienLopTC(DanhSachLopTinChi &dsLTC, int maLTC, const char* maSV, float diem);
void NhapDiemTheoBang(DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, int maLTC);
void InBangDiemMonHoc(const DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, const DanhSachMonHoc &dsMH, const char* maMH);
void InBangDiemTrungBinhKhoa(const DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, const DanhSachMonHoc &dsMH, const char* maLop);
void InBangDiemTongKet(const DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, const DanhSachMonHoc &dsMH, const char* maLop);

#endif // DIEM_H