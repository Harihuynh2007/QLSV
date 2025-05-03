#include "MonHoc.h"
#include "AVLTree.h"
#include <iostream>
#include <cstring>
#include <iomanip>

// Hàm tìm kiếm môn học theo mã
NodeAVL* TimMonHocTheoMa(DanhSachMonHoc ds, const char* maMH) {
    return SearchAVL(ds, maMH);
}

// Hàm thêm môn học
DanhSachMonHoc ThemMonHoc(DanhSachMonHoc ds, MonHoc mh) {
    return InsertAVL(ds, mh);
}

// Hàm xóa môn học
DanhSachMonHoc XoaMonHoc(DanhSachMonHoc ds, const char* maMH) {
    return DeleteAVL(ds, maMH);
}

// Hàm cập nhật thông tin môn học
void CapNhatMonHoc(DanhSachMonHoc ds, const char* maMH, MonHoc mhMoi) {
    UpdateAVL(ds, maMH, mhMoi);
}

// Hàm hỗ trợ để in một môn học
void PrintMonHoc(MonHoc mh, int stt) {
    std::cout << std::left << std::setw(4) << stt
              << " | " << std::setw(10) << mh.MAMH
              << " | " << std::setw(50) << mh.TENMH
              << " | " << std::setw(5) << mh.STCLT
              << " | " << std::setw(5) << mh.STCTH << "\n";
}

// Hàm thu thập môn học từ cây AVL vào mảng
void ThuThapMonHoc(DanhSachMonHoc ds, MonHoc* &arr, int &size, int &capacity) {
    if (ds == NULL) return;

    // Mở rộng mảng nếu cần
    if (size >= capacity) {
        capacity = (capacity == 0) ? 10 : capacity * 2;
        MonHoc* newArr = new MonHoc[capacity];
        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }

    // Thêm môn học vào mảng
    arr[size++] = ds->data;

    // Đệ quy cho cây con
    ThuThapMonHoc(ds->left, arr, size, capacity);
    ThuThapMonHoc(ds->right, arr, size, capacity);
}

// Hàm sắp xếp mảng theo TENMH
void SapXepTheoTenMonHoc(MonHoc* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (strcmp(arr[j].TENMH, arr[j + 1].TENMH) > 0) {
                MonHoc temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Hàm in danh sách môn học (theo MAMH - mặc định của cây AVL)
void InDanhSachMonHoc(DanhSachMonHoc ds) {
    if (ds == NULL) {
        std::cout << "Danh sach mon hoc rong.\n";
        return;
    }
    std::cout << "\n--- Danh Sach Mon Hoc (Sap xep theo MAMH) ---\n";
    std::cout << std::left << std::setw(4) << "STT"
              << " | " << std::setw(10) << "MA MH"
              << " | " << std::setw(50) << "TEN MON HOC"
              << " | " << std::setw(5) << "LT"
              << " | " << std::setw(5) << "TH" << "\n";
    std::cout << std::setfill('-') << std::setw(4) << "-" << "-|-"
              << std::setw(10) << "-" << "-|-"
              << std::setw(50) << "-" << "-|-"
              << std::setw(5) << "-" << "-|-"
              << std::setw(5) << "-" << std::setfill(' ') << std::endl;

    int stt = 1;
    InorderTraversal(ds, [&stt](MonHoc mh) {
        PrintMonHoc(mh, stt++);
    });
    std::cout << "Tong so mon hoc: " << CountNodes(ds) << "\n";
}

// Hàm in danh sách môn học đã sắp xếp theo TENMH
void InDanhSachMonHocSapXepTheoTen(DanhSachMonHoc ds) {
    if (ds == NULL) {
        std::cout << "Danh sach mon hoc rong.\n";
        return;
    }

    // Thu thập môn học vào mảng
    MonHoc* arr = nullptr;
    int size = 0, capacity = 0;
    ThuThapMonHoc(ds, arr, size, capacity);

    // Sắp xếp theo TENMH
    SapXepTheoTenMonHoc(arr, size);

    // In danh sách đã sắp xếp
    std::cout << "\n--- Danh Sach Mon Hoc (Sap xep theo TENMH) ---\n";
    std::cout << std::left << std::setw(4) << "STT"
              << " | " << std::setw(10) << "MA MH"
              << " | " << std::setw(50) << "TEN MON HOC"
              << " | " << std::setw(5) << "LT"
              << " | " << std::setw(5) << "TH" << "\n";
    std::cout << std::setfill('-') << std::setw(4) << "-" << "-|-"
              << std::setw(10) << "-" << "-|-"
              << std::setw(50) << "-" << "-|-"
              << std::setw(5) << "-" << "-|-"
              << std::setw(5) << "-" << std::setfill(' ') << std::endl;

    for (int i = 0; i < size; i++) {
        PrintMonHoc(arr[i], i + 1);
    }
    std::cout << "Tong so mon hoc: " << size << "\n";

    // Giải phóng bộ nhớ
    delete[] arr;
}

// Hàm giải phóng bộ nhớ
void GiaiPhongDSMonHoc(DanhSachMonHoc &ds) {
    FreeAVL(ds);
}

// Hàm đếm số môn học
int DemSoMonHoc(DanhSachMonHoc ds) {
    return CountNodes(ds);
}