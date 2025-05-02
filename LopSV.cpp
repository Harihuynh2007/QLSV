#include "LopSV.h"
#include <iostream>
#include <cstring>
#include <new>

 
void KhoiTaoDSLopSV(DanhSachLopSV &ds) {
    ds.lop = NULL;
    ds.n = 0;
    ds.capacity = 0;
}


void GiaiPhongDSLopSV(DanhSachLopSV &ds) {
    for (int i = 0; i < ds.n; i++) {
        GiaiPhongDSSinhVien(ds.lop[i].dssv);
    }
    delete[] ds.lop;
    ds.lop = NULL;
    ds.n = 0;
    ds.capacity = 0;
}


int TimLopSV(const DanhSachLopSV &ds, const char* maLop) {
    for (int i = 0; i < ds.n; i++) {
        if (strcmp(ds.lop[i].MALOP, maLop) == 0) {
            return i;
        }
    }
    return -1;
}


bool ThemLopSV(DanhSachLopSV &ds, LopSV lop) {
    if (TimLopSV(ds, lop.MALOP) != -1) {
        std::cerr << "Loi: Ma lop '" << lop.MALOP << "' da ton tai!\n";
        return false;
    }
    if (ds.n == ds.capacity) {
        ExtendLopArray(ds);
    }
    ds.lop[ds.n] = lop;
    ds.lop[ds.n].dssv = NULL; // Khởi tạo danh sách sinh viên rỗng
    ds.n++;
    return true;
}


bool XoaLopSV(DanhSachLopSV &ds, const char* maLop) {
    int index = TimLopSV(ds, maLop);
    if (index == -1) {
        std::cerr << "Loi: Khong tim thay lop '" << maLop << "' de xoa.\n";
        return false;
    }
    GiaiPhongDSSinhVien(ds.lop[index].dssv);
    for (int i = index; i < ds.n - 1; i++) {
        ds.lop[i] = ds.lop[i + 1];
    }
    ds.n--;
    return true;
}


bool HieuChinhLopSV(DanhSachLopSV &ds, const char* maLop, LopSV lopMoi) {
    int index = TimLopSV(ds, maLop);
    if (index == -1) {
        std::cerr << "Loi: Khong tim thay lop '" << maLop << "' de hieu chinh.\n";
        return false;
    }
    strcpy(ds.lop[index].TENLOP, lopMoi.TENLOP);
    std::cout << "Lop '" << maLop << "' da duoc hieu chinh.\n";
    return true;
}

// Mo rong mang khi full
void ExtendLopArray(DanhSachLopSV &ds) {
    int new_capacity = ds.capacity == 0 ? 10 : ds.capacity * 2;
    LopSV* new_lop = new (std::nothrow) LopSV[new_capacity];
    if (!new_lop) {
        std::cerr << "Loi: Khong du bo nho de mo rong danh sach lop!\n";
        return;
    }
    for (int i = 0; i < ds.n; i++) {
        new_lop[i] = ds.lop[i];
    }
    delete[] ds.lop;
    ds.lop = new_lop;
    ds.capacity = new_capacity;
}