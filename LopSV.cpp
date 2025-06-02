#include "LopSV.h"
#include <iostream>
#include <cstring>
#include <new>
#include <fstream>
#include <sstream>
 
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

#include <fstream>

void SaveDanhSachSinhVien(DanhSachSinhVien first, std::ofstream &file) {
    NodeSV* current = first;
    while (current != NULL) {
        file << current->data.MASV << "|"
             << current->data.HO << "|"
             << current->data.TEN << "|"
             << current->data.PHAI << "|"
             << current->data.SODT << "|"
             << current->data.LOP << std::endl;
        current = current->next;
    }
}

void SaveDanhSachLopSV(const DanhSachLopSV &ds, const char* filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Khong the mo file de ghi LopSV!\n";
        return;
    }

    for (int i = 0; i < ds.n; i++) {
        // Ghi thông tin lớp
        file << ds.lop[i].MALOP << "|"
             << ds.lop[i].TENLOP << std::endl;
        
        // Ghi danh sách sinh viên của lớp
        SaveDanhSachSinhVien(ds.lop[i].dssv, file);

        // Kết thúc 1 lớp
        file << "#ENDCLASS" << std::endl;
    }

    // Ghi kết thúc file
    file << "#END" << std::endl;
    file.close();
}
void LoadDanhSachLopSV(DanhSachLopSV &ds, const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Khong the mo file de doc LopSV!\n";
        return;
    }

    KhoiTaoDSLopSV(ds);

    std::string line;
    int currentIndex = -1;

    while (std::getline(file, line)) {
        if (line == "#END") break;
        if (line == "#ENDCLASS") {
            currentIndex = -1;
            continue;
        }

        std::stringstream ss(line);
        std::string token;

        if (currentIndex == -1) {
            // Dòng MALOP|TENLOP
            LopSV lop;
            std::getline(ss, token, '|'); strcpy(lop.MALOP, token.c_str());
            std::getline(ss, token, '|'); strcpy(lop.TENLOP, token.c_str());
            lop.dssv = NULL;
            ThemLopSV(ds, lop);
            currentIndex = ds.n - 1;
        } else {
            // Dòng SinhVien
            SinhVien sv;
            std::getline(ss, token, '|'); strcpy(sv.MASV, token.c_str());
            std::getline(ss, token, '|'); strcpy(sv.HO, token.c_str());
            std::getline(ss, token, '|'); strcpy(sv.TEN, token.c_str());
            std::getline(ss, token, '|'); strcpy(sv.PHAI, token.c_str());
            std::getline(ss, token, '|'); strcpy(sv.SODT, token.c_str());
            strcpy(sv.LOP, ds.lop[currentIndex].MALOP);

            ThemSinhVien(ds.lop[currentIndex].dssv, sv);
        }
    }

    file.close();
}

void GopTatCaSinhVienTuLopSV(const DanhSachLopSV &dsLop, DanhSachSinhVien &dsSV) {
    KhoiTaoDSSinhVien(dsSV); 
    for (int i = 0; i < dsLop.n; i++) {
        NodeSV* p = dsLop.lop[i].dssv;
        while (p != NULL) {
            ThemSinhVien(dsSV, p->data);
            p = p->next;
        }
    }
}


