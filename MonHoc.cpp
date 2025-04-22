#include "MonHoc.h"
#include <iostream> 
#include <new>      // Để dùng std::nothrow khi cấp phát
#include <cstring>  
#include <iomanip>  // Để định dạng output (setw, left)

// --- Định nghĩa các hàm ---

// Khởi tạo danh sách rỗng
void KhoiTaoDSMonHoc(DanhSachMonHoc &ds) {
    ds.nodes = NULL; 
    ds.soLuong = 0;
    ds.capacity = 0;
}

// Giải phóng bộ nhớ
void GiaiPhongDSMonHoc(DanhSachMonHoc &ds) {
    if (ds.nodes != NULL) {
        delete[] ds.nodes; // Giải phóng mảng đã cấp phát bằng new[]
        ds.nodes = NULL;    // Tránh dangling pointer
    }
    ds.soLuong = 0;
    ds.capacity = 0;
}

bool IsEmpty(const DanhSachMonHoc &ds) {
    return ds.soLuong == 0;
}

bool IsFull(const DanhSachMonHoc &ds) {
    return ds.soLuong == ds.capacity;
}

// Tìm vị trí môn học theo mã, trả về -1 nếu không tìm thấy
int TimMonHocTheoMa(const DanhSachMonHoc &ds, const char* maMH) {
    if (maMH == NULL || ds.nodes == NULL) return -1; // Tham số hoặc danh sách không hợp lệ

    for (int i = 0; i < ds.soLuong; ++i) {
        if (strcmp(ds.nodes[i].MAMH, maMH) == 0) {
            return i;
        }
    }
    return -1; // 
}

bool ThemMonHoc(DanhSachMonHoc &ds, MonHoc mh) {
	
    // --- Kiểm tra mã môn học đã tồn tại chưa
	if (TimMonHocTheoMa(ds, mh.MAMH) != -1) {
	    std::cerr << "Loi: Ma mon hoc '" << mh.MAMH << "' da ton tai!\n";
	    return false;
    }

    // --- Xử lý cấp phát động nếu mảng đầy hoặc chưa được cấp phát ---
    if (ds.soLuong == ds.capacity) {
        int new_capacity;
        if (ds.capacity == 0) {
            new_capacity = 10; // Cấp phát lần đầu cho 10 phần tử
        } else {
            new_capacity = ds.capacity * 2; // Gấp đôi dung lượng
        }

        // Cố gắng cấp phát bộ nhớ mới, sử dụng nothrow để không bị exception nếu thất bại
        MonHoc* temp_nodes = new (std::nothrow) MonHoc[new_capacity];

        if (temp_nodes == NULL) {
            // Cấp phát thất bại (hết bộ nhớ?)
            std::cerr << "Loi: Khong du bo nho de mo rong danh sach mon hoc!\n";
            return false; 
        }

        // Sao chép dữ liệu từ mảng cũ (nếu có) sang mảng mới
        if (ds.nodes != NULL) {
            for (int i = 0; i < ds.soLuong; ++i) {
                 temp_nodes[i] = ds.nodes[i]; 
            }
            // Giải phóng bộ nhớ của mảng cũ
            delete[] ds.nodes;
        }

        // Cập nhật con trỏ và capacity của danh sách
        ds.nodes = temp_nodes;
        ds.capacity = new_capacity;
        // std::cout << "Debug: Capacity danh sach mon hoc tang len: " << ds.capacity << std::endl; // Debug
    }

    
    // Sao chép dữ liệu từ mh vào vị trí cuối cùng của mảng
    strncpy(ds.nodes[ds.soLuong].MAMH, mh.MAMH, sizeof(ds.nodes[ds.soLuong].MAMH) - 1);
    ds.nodes[ds.soLuong].MAMH[sizeof(ds.nodes[ds.soLuong].MAMH) - 1] = '\0'; // Đảm bảo null termination

    strncpy(ds.nodes[ds.soLuong].TENMH, mh.TENMH, sizeof(ds.nodes[ds.soLuong].TENMH) - 1);
    ds.nodes[ds.soLuong].TENMH[sizeof(ds.nodes[ds.soLuong].TENMH) - 1] = '\0'; 

    ds.soLuong++; 
    return true;  
}


bool XoaMonHocTaiIndex(DanhSachMonHoc &ds, int index) {
    if (index < 0 || index >= ds.soLuong) {
        std::cerr << "Loi: Vi tri xoa khong hop le (" << index << "). Pham vi hop le [0, " << ds.soLuong - 1 << "]\n";
        return false; // Vị trí không hợp lệ
    }

    // Dồn các phần tử từ vị trí (index + 1) lên vị trí index
    for (int i = index; i < ds.soLuong - 1; ++i) {
        ds.nodes[i] = ds.nodes[i + 1]; // Gán struct MonHoc
    }

    ds.soLuong--; // Giảm số lượng phần tử

    // (Tùy chọn) Có thể thu nhỏ mảng nếu soLuong quá nhỏ so với capacity (ví dụ: < capacity / 4)
    // Việc này phức tạp hơn và thường không làm khi xóa từng phần tử.
    // if (ds.capacity > 10 && ds.soLuong < ds.capacity / 4) {
    //     int new_capacity = ds.capacity / 2;
    //     MonHoc* temp_nodes = new (std::nothrow) MonHoc[new_capacity];
    //     if (temp_nodes != NULL) {
    //         for (int i = 0; i < ds.soLuong; ++i) {
    //             temp_nodes[i] = ds.nodes[i];
    //         }
    //         delete[] ds.nodes;
    //         ds.nodes = temp_nodes;
    //         ds.capacity = new_capacity;
    //         std::cout << "Debug: Capacity danh sach mon hoc giam xuong: " << ds.capacity << std::endl; // Debug
    //     }
    // }

    return true; // Xóa thành công
}

// Bổ sung: Hàm xóa môn học theo mã
bool XoaMonHocTheoMa(DanhSachMonHoc &ds, const char* maMH) {
    int index = TimMonHocTheoMa(ds, maMH);
    if (index == -1) {
        std::cerr << "Loi: Khong tim thay mon hoc voi ma '" << maMH << "' de xoa.\n";
        return false; // Không tìm thấy mã
    }
    // Gọi hàm xóa theo index sau khi tìm thấy
    std::cout << "Tim thay mon hoc voi ma '" << maMH << "' tai vi tri " << index << ". Dang xoa...\n";
    return XoaMonHocTaiIndex(ds, index);
}


// Bổ sung: Hàm hiệu chỉnh thông tin môn học theo mã
// mhMoi chứa thông tin mới (trừ mã MH nếu mã không thay đổi)
bool HieuChinhMonHoc(DanhSachMonHoc &ds, const char* maMH, const MonHoc mhMoi) {
    int index = TimMonHocTheoMa(ds, maMH);
    if (index == -1) {
        std::cerr << "Loi: Khong tim thay mon hoc voi ma '" << maMH << "' de hieu chinh.\n";
        return false; // Không tìm thấy mã
    }

    // Cập nhật thông tin.
    // Lưu ý: Không nên sửa mã môn học nếu mã là khóa chính.
    // Chỉ cập nhật tên môn học và các trường khác (nếu có).
    strncpy(ds.nodes[index].TENMH, mhMoi.TENMH, sizeof(ds.nodes[index].TENMH) - 1);
    ds.nodes[index].TENMH[sizeof(ds.nodes[index].TENMH) - 1] = '\0'; // Đảm bảo null termination

    // Cập nhật các trường khác nếu có...

    std::cout << "Mon hoc voi ma '" << maMH << "' da duoc hieu chinh.\n";
    return true; // Hiệu chỉnh thành công
}


void InDanhSachMonHoc(const DanhSachMonHoc &ds) {
    if (IsEmpty(ds)) {
        std::cout << "Danh sach mon hoc rong.\n";
        return;
    }
    std::cout << "\n--- Danh Sach Mon Hoc ---\n";
    // Sử dụng iomanip để định dạng cột
    std::cout << std::left << std::setw(4) << "STT"
              << " | " << std::setw(10) << "MA MH"
              << " | " << "TEN MON HOC\n";
    std::cout << std::setfill('-') << std::setw(4) << "-" << "-|-"
              << std::setw(10) << "-" << "-|-"
              << std::setw(50) << "-" << std::setfill(' ') << std::endl;

    for (int i = 0; i < ds.soLuong; ++i) {
        std::cout << std::left << std::setw(4) << i + 1
                  << " | " << std::setw(10) << ds.nodes[i].MAMH
                  << " | " << ds.nodes[i].TENMH << std::endl;
    }
    std::cout << std::setfill('-') << std::setw(70) << "-" << std::setfill(' ') << std::endl;
    std::cout << "Tong so mon hoc: " << ds.soLuong << std::endl;
}


void SapXepMonHocTheoTen(DanhSachMonHoc &ds) {
    if (ds.soLuong < 2) return; 

    bool swapped;
    for (int i = 0; i < ds.soLuong - 1; ++i) {
        swapped = false; // Cờ tối ưu: nếu không có hoán đổi nào trong 1 lượt, danh sách đã sắp xếp
        for (int j = 0; j < ds.soLuong - i - 1; ++j) {
            // So sánh tên môn học bằng strcmp
            if (strcmp(ds.nodes[j].TENMH, ds.nodes[j + 1].TENMH) > 0) {
                // Nếu tên ở vị trí j lớn hơn tên ở vị trí j+1 -> hoán đổi
                MonHoc temp = ds.nodes[j];
                ds.nodes[j] = ds.nodes[j + 1];
                ds.nodes[j + 1] = temp;
                swapped = true;
            }
        }
        // Nếu không có hoán đổi nào trong vòng lặp trong, dừng lại
        if (!swapped) break;
    }
    std::cout << "Danh sach mon hoc da duoc sap xep theo ten (Bubble Sort).\n";
}

