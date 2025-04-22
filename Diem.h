#ifndef DIEM_H
#define DIEM_H

#include "LopTinChi.h"
#include "SinhVien.h"

// Hàm nhập điểm cho sinh viên trong lớp tín chỉ
bool NhapDiemSinhVienLopTC(DanhSachLopTinChi &dsLTC, int maLTC, const char* maSV, float diem);

// Hàm in bảng điểm môn học
void InBangDiemMonHoc(const DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, const char* maMH);

// Hàm in bảng điểm trung bình khoa
void InBangDiemTrungBinhKhoa(const DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, const char* tenLop);

// Hàm in bảng điểm tổng kết của sinh viên
void InBangDiemTongKet(const DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, const char* maSV);

#endif // DIEM_H