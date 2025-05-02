#ifndef MONHOC_H
#define MONHOC_H

#include <stdlib.h> // For malloc, realloc, free
#include <string.h> // For strcpy, strcmp
#include <stdio.h>  // For printf, NULL

struct MonHoc {
	char MAMH[11];
	char TENMH[51];
	int STCLT; 
    int STCTH;
};

struct DanhSachMonHoc{
	MonHoc *nodes;  
    int capacity;
    int soLuong;
};

// Các hàm quản lý cơ bản
void KhoiTaoDSMonHoc(DanhSachMonHoc &ds);
void GiaiPhongDSMonHoc(DanhSachMonHoc &ds);
bool IsEmpty(const DanhSachMonHoc &ds);
bool IsFull(const DanhSachMonHoc &ds);

// Các hàm thao tác trên danh sách
int TimMonHocTheoMa(const DanhSachMonHoc &ds, const char* maMH);
bool ThemMonHoc(DanhSachMonHoc &ds, MonHoc mh);
bool XoaMonHocTaiIndex(DanhSachMonHoc &ds, int index);
bool XoaMonHocTheoMa(DanhSachMonHoc &ds, const char* maMH);
bool HieuChinhMonHoc(DanhSachMonHoc &ds, const char* maMH, MonHoc mhMoi);

// Các hàm xuất và sắp xếp
void InDanhSachMonHoc(const DanhSachMonHoc &ds);
void SapXepMonHocTheoTen(DanhSachMonHoc &ds);

#endif 