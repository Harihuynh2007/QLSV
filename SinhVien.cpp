#include "SinhVien.h"
#include <iostream>
#include <cstring>
#include <iomanip>

// --- Các hàm quản lý cơ bản ---

// Khởi tạo danh sách sinh viên rỗng
void KhoiTaoDSSinhVien(DanhSachSinhVien &first) {
    first = NULL;
}

// Giải phóng bộ nhớ của danh sách sinh viên
void GiaiPhongDSSinhVien(DanhSachSinhVien &first) {
    NodeSV* current = first;
    while (current != NULL) {
        NodeSV* temp = current;
        current = current->next;
        delete temp;
    }
    first = NULL;
}

// Kiểm tra danh sách rỗng
bool IsEmpty(const DanhSachSinhVien first) {
    return first == NULL;
}

// Tìm sinh viên theo mã, trả về con trỏ đến node hoặc NULL nếu không tìm thấy
NodeSV* TimSinhVienTheoMa(DanhSachSinhVien first, const char* maSV) {
    if (maSV == NULL) return NULL; // Tham số không hợp lệ
    
    NodeSV* current = first;
    while (current != NULL) {
        if (strcmp(current->data.MASV, maSV) == 0) {
            return current; // Trả về node nếu tìm thấy
        }
        current = current->next;
    }
    return NULL; // Không tìm thấy
}

// Thêm sinh viên vào danh sách (thêm vào đầu danh sách cho đơn giản)
bool ThemSinhVien(DanhSachSinhVien &first, SinhVien sv) {
    // Kiểm tra sinh viên đã tồn tại chưa
    if (TimSinhVienTheoMa(first, sv.MASV) != NULL) {
        std::cerr << "Loi: Ma sinh vien '" << sv.MASV << "' da ton tai!\n";
        return false;
    }
    
    // Tạo node mới
    NodeSV* newNode = new (std::nothrow) NodeSV;
    if (newNode == NULL) {
        std::cerr << "Loi: Khong du bo nho de them sinh vien!\n";
        return false;
    }
    
    // Sao chép dữ liệu sinh viên vào node mới
    // Đảm bảo sao chép an toàn với null termination
    strncpy(newNode->data.MASV, sv.MASV, MAX_MASV_LEN);
    newNode->data.MASV[MAX_MASV_LEN] = '\0';
    
    strncpy(newNode->data.HO, sv.HO, MAX_HO_LEN);
    newNode->data.HO[MAX_HO_LEN] = '\0';
    
    strncpy(newNode->data.TEN, sv.TEN, MAX_TEN_LEN);
    newNode->data.TEN[MAX_TEN_LEN] = '\0';
    
    strncpy(newNode->data.PHAI, sv.PHAI, MAX_PHAI_LEN);
    newNode->data.PHAI[MAX_PHAI_LEN] = '\0';
    
    strncpy(newNode->data.SODT, sv.SODT, MAX_SODT_LEN);
    newNode->data.SODT[MAX_SODT_LEN] = '\0';
    
    // Thêm node vào đầu danh sách
    newNode->next = first;
    first = newNode;
    
    return true;
}


bool XoaSinhVienTheoMa(DanhSachSinhVien &first, const char* maSV) {
    if (IsEmpty(first) || maSV == NULL) {
        return false;
    }
    
    // Trường hợp xóa node đầu tiên
    if (strcmp(first->data.MASV, maSV) == 0) {
        NodeSV* temp = first;
        first = first->next;
        delete temp;
        return true;
    }
    
    NodeSV* current = first;
    while (current->next != NULL) {
        if (strcmp(current->next->data.MASV, maSV) == 0) {
            NodeSV* temp = current->next;
            current->next = temp->next;
            delete temp;
            return true;
        }
        current = current->next;
    }
    
    std::cerr << "Loi: Khong tim thay sinh vien voi ma '" << maSV << "' de xoa.\n";
    return false;
}


bool HieuChinhSinhVien(DanhSachSinhVien first, const char* maSV, const SinhVien svMoi) {
    NodeSV* node = TimSinhVienTheoMa(first, maSV);
    if (node == NULL) {
        std::cerr << "Loi: Khong tim thay sinh vien voi ma '" << maSV << "' de hieu chinh.\n";
        return false;
    }
    
    // Giữ nguyên mã sinh viên (khóa chính), cập nhật các thông tin khác
    strncpy(node->data.HO, svMoi.HO, MAX_HO_LEN);
    node->data.HO[MAX_HO_LEN] = '\0';
    
    strncpy(node->data.TEN, svMoi.TEN, MAX_TEN_LEN);
    node->data.TEN[MAX_TEN_LEN] = '\0';
    
    strncpy(node->data.PHAI, svMoi.PHAI, MAX_PHAI_LEN);
    node->data.PHAI[MAX_PHAI_LEN] = '\0';
    
    strncpy(node->data.SODT, svMoi.SODT, MAX_SODT_LEN);
    node->data.SODT[MAX_SODT_LEN] = '\0';
    
    std::cout << "Sinh vien voi ma '" << maSV << "' da duoc hieu chinh.\n";
    return true;
}


void InDanhSachSinhVien(const DanhSachSinhVien first) {
    if (IsEmpty(first)) {
        std::cout << "Danh sach sinh vien rong.\n";
        return;
    }
    
    std::cout << "\n--- Danh Sach Sinh Vien ---\n";
    
    std::cout << std::left 
              << std::setw(4) << "STT"
              << " | " << std::setw(15) << "MA SV"
              << " | " << std::setw(30) << "HO"
              << " | " << std::setw(10) << "TEN"
              << " | " << std::setw(4) << "PHAI"
              << " | " << "SO DIEN THOAI" << std::endl;
    
    std::cout << std::setfill('-')
              << std::setw(4) << "-" << "-|-"
              << std::setw(15) << "-" << "-|-"
              << std::setw(30) << "-" << "-|-"
              << std::setw(10) << "-" << "-|-"
              << std::setw(4) << "-" << "-|-"
              << std::setw(15) << "-"
              << std::setfill(' ') << std::endl;
    
    int stt = 1;
    NodeSV* current = first;
    while (current != NULL) {
        std::cout << std::left
                  << std::setw(4) << stt++
                  << " | " << std::setw(15) << current->data.MASV
                  << " | " << std::setw(30) << current->data.HO
                  << " | " << std::setw(10) << current->data.TEN
                  << " | " << std::setw(4) << current->data.PHAI
                  << " | " << current->data.SODT << std::endl;
        
        current = current->next;
    }
    
    // In footer của bảng
    std::cout << std::setfill('-') << std::setw(85) << "-" << std::setfill(' ') << std::endl;
    
    // Đếm số lượng sinh viên
    int count = 0;
    current = first;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    
    std::cout << "Tong so sinh vien: " << count << std::endl;
}

void InDanhSachSinhVienSapXepTheoTen(const DanhSachSinhVien first) {
    if (IsEmpty(first)) {
        std::cout << "Danh sach sinh vien rong.\n";
        return;
    }

    // Dem so sv
    int count = 0;
    NodeSV* p = first;
    while (p != NULL) {
        count++;
        p = p->next;
    }

    // Tao mang con tro de luu sinh vien
    NodeSV** svArr = new NodeSV*[count];
    p = first;
    for (int i = 0; i < count; i++) {
        svArr[i] = p;
        p = p->next;
    }

    // sap xep theo ho va ten
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            int cmp = strcmp(svArr[j]->data.TEN, svArr[j + 1]->data.TEN);
            if (cmp > 0 || (cmp == 0 && strcmp(svArr[j]->data.HO, svArr[j + 1]->data.HO) > 0)) {
                NodeSV* temp = svArr[j];
                svArr[j] = svArr[j + 1];
                svArr[j + 1] = temp;
            }
        }
    }

    std::cout << "\n--- Danh Sach Sinh Vien (Sap xep theo ten + ho) ---\n";
    std::cout << std::left 
              << std::setw(4) << "STT"
              << " | " << std::setw(15) << "MA SV"
              << " | " << std::setw(30) << "HO"
              << " | " << std::setw(10) << "TEN"
              << " | " << std::setw(4) << "PHAI"
              << " | " << "SO DIEN THOAI" << std::endl;
    
    std::cout << std::setfill('-')
              << std::setw(4) << "-" << "-|-"
              << std::setw(15) << "-" << "-|-"
              << std::setw(30) << "-" << "-|-"
              << std::setw(10) << "-" << "-|-"
              << std::setw(4) << "-" << "-|-"
              << std::setw(15) << "-" << std::endl;
    std::cout << std::setfill(' ');

    for (int i = 0; i < count; i++) {
        std::cout << std::left
                  << std::setw(4) << (i + 1)
                  << " | " << std::setw(15) << svArr[i]->data.MASV
                  << " | " << std::setw(30) << svArr[i]->data.HO
                  << " | " << std::setw(10) << svArr[i]->data.TEN
                  << " | " << std::setw(4) << svArr[i]->data.PHAI
                  << " | " << svArr[i]->data.SODT << std::endl;
    }

    // Giai phong mang con tro
    delete[] svArr;
}
