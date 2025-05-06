// --- START OF FILE LopTinChi.cpp ---
#include <fstream>
#include <sstream>
#include "LopTinChi.h"
#include "SinhVien.h"
#include <iostream>
#include <cstring>
#include <iomanip>
#include <new>

// --- Registration list (DanhSachDangKy - Singly Linked List) functions ---

void KhoiTaoDSDangKy(DanhSachDangKy &firstDK) {
    firstDK = NULL;
}

void GiaiPhongDSDangKy(DanhSachDangKy &firstDK) {
    NodeDK* p = NULL;
    while (firstDK != NULL) {
        p = firstDK;
        firstDK = firstDK->next;
        delete p;
    }
}

NodeDK* TimDangKyTheoMASV(DanhSachDangKy firstDK, const char* maSV) {
    NodeDK* current = firstDK;
    while (current != NULL) {
        if (strcmp(current->data.MASV, maSV) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

bool ThemDangKyVaoDSLK(DanhSachDangKy &firstDK, const DangKy &dk) {
    if (TimDangKyTheoMASV(firstDK, dk.MASV) != NULL) {
        std::cerr << "Lỗi: Sinh viên " << dk.MASV << " đã đăng ký lớp này rồi.\n";
        return false;
    }

    NodeDK* newNode = new (std::nothrow) NodeDK;
    if (newNode == NULL) {
        std::cerr << "Lỗi: Không đủ bộ nhớ để cấp phát NodeDK mới.\n";
        return false;
    }

    newNode->data = dk;
    newNode->next = NULL;

    if (firstDK == NULL || strcmp(dk.MASV, firstDK->data.MASV) < 0) {
        newNode->next = firstDK;
        firstDK = newNode;
        return true;
    }

    NodeDK* prev = firstDK;
    while (prev->next != NULL && strcmp(prev->next->data.MASV, dk.MASV) < 0) {
        prev = prev->next;
    }

    newNode->next = prev->next;
    prev->next = newNode;
    return true;
}

bool XoaDangKyTheoMASV(DanhSachDangKy &firstDK, const char* maSV) {
    if (firstDK == NULL) return false;

    NodeDK* temp = NULL;
    if (strcmp(firstDK->data.MASV, maSV) == 0) {
        temp = firstDK;
        firstDK = firstDK->next;
        delete temp;
        return true;
    }

    NodeDK* prev = firstDK;
    while (prev->next != NULL && strcmp(prev->next->data.MASV, maSV) != 0) {
        prev = prev->next;
    }

    if (prev->next != NULL) {
        temp = prev->next;
        prev->next = temp->next;
        delete temp;
        return true;
    }

    return false;
}

int DemSoLuongDangKy(DanhSachDangKy firstDK) {
    int count = 0;
    NodeDK* p = firstDK;
    while (p != NULL) {
        count++;
        p = p->next;
    }
    return count;
}

// --- Credit class list (DanhSachLopTinChi - Array of Pointers) functions ---

void KhoiTaoDSLTC(DanhSachLopTinChi &ds) {
    for (int i = 0; i < MAX_LTC; i++) {
        ds.nodes[i] = NULL;
    }
    ds.soLuong = 0;
}

void GiaiPhongDSLTC(DanhSachLopTinChi &ds) {
    for (int i = 0; i < MAX_LTC; i++) {
        if (ds.nodes[i] != NULL) {
            GiaiPhongDSDangKy(ds.nodes[i]->dssvdk);
            delete ds.nodes[i];
            ds.nodes[i] = NULL;
        }
    }
    ds.soLuong = 0;
}

int TimLopTinChiTheoMa(const DanhSachLopTinChi &ds, int maLTC) {
    for (int i = 0; i < MAX_LTC; i++) {
        if (ds.nodes[i] != NULL && ds.nodes[i]->MALOPTC == maLTC) {
            return i;
        }
    }
    return -1;
}

LopTinChi* TimLopTinChiTheoTieuChi(const DanhSachLopTinChi &ds, const char* maMH, int nienKhoa, int hocKy, int nhom) {
    LopTinChi* result = NULL;
    bool foundMultiple = false;

    for (int i = 0; i < MAX_LTC; i++) {
        if (ds.nodes[i] != NULL &&
            strcmp(ds.nodes[i]->MAMH, maMH) == 0 &&
            ds.nodes[i]->nienkhoa == nienKhoa &&
            ds.nodes[i]->hocky == hocKy &&
            ds.nodes[i]->nhom == nhom) {
            if (result == NULL) {
                result = ds.nodes[i];
            } else {
                foundMultiple = true;
                break;
            }
        }
    }

    return foundMultiple ? NULL : result;
}

int TimMaLopTCMax(const DanhSachLopTinChi &ds) {
    int maxMa = 0;
    for (int i = 0; i < MAX_LTC; i++) {
        if (ds.nodes[i] != NULL && ds.nodes[i]->MALOPTC > maxMa) {
            maxMa = ds.nodes[i]->MALOPTC;
        }
    }
    return maxMa;
}

int ThemLopTC(DanhSachLopTinChi &ds, const LopTinChi &lopTCData) {
    if (ds.soLuong >= MAX_LTC) {
        std::cerr << "Lỗi: Danh sách lớp tín chỉ đã đầy (" << MAX_LTC << " lớp).\n";
        return -1;
    }

    // Kiểm tra trùng MALOPTC
    if (lopTCData.MALOPTC > 0 && TimLopTinChiTheoMa(ds, lopTCData.MALOPTC) != -1) {
        std::cerr << "Lỗi: Mã lớp tín chỉ " << lopTCData.MALOPTC << " đã tồn tại.\n";
        return -1;
    }

    int emptyIndex = -1;
    for (int i = 0; i < MAX_LTC; i++) {
        if (ds.nodes[i] == NULL) {
            emptyIndex = i;
            break;
        }
    }

    if (emptyIndex == -1) {
        std::cerr << "Lỗi: Không tìm thấy vị trí trống để thêm lớp tín chỉ.\n";
        return -1;
    }

    ds.nodes[emptyIndex] = new (std::nothrow) LopTinChi;
    if (ds.nodes[emptyIndex] == NULL) {
        std::cerr << "Lỗi: Không đủ bộ nhớ để cấp phát LopTinChi mới.\n";
        return -1;
    }

    *ds.nodes[emptyIndex] = lopTCData;

    if (ds.nodes[emptyIndex]->MALOPTC <= 0) {
        ds.nodes[emptyIndex]->MALOPTC = TimMaLopTCMax(ds) + 1;
    }

    KhoiTaoDSDangKy(ds.nodes[emptyIndex]->dssvdk);
    ds.nodes[emptyIndex]->soSVDK = 0;
    ds.nodes[emptyIndex]->huyLop = false; // Mặc định không hủy

    ds.soLuong++;
    return ds.nodes[emptyIndex]->MALOPTC;
}

bool XoaLopTCTheoMa(DanhSachLopTinChi &ds, int maLTC) {
    int index = TimLopTinChiTheoMa(ds, maLTC);
    if (index == -1) return false;

    GiaiPhongDSDangKy(ds.nodes[index]->dssvdk);
    delete ds.nodes[index];
    ds.nodes[index] = NULL;
    ds.soLuong--;
    return true;
}

bool HieuChinhLopTinChi(DanhSachLopTinChi &ds, int maLTC, const LopTinChi &lopTCMoi) {
    int index = TimLopTinChiTheoMa(ds, maLTC);
    if (index == -1) return false;

    ds.nodes[index]->sv_min = lopTCMoi.sv_min;
    ds.nodes[index]->sv_max = lopTCMoi.sv_max;
    ds.nodes[index]->huyLop = lopTCMoi.huyLop;

    return true;
}

bool HuyLopTinChi(DanhSachLopTinChi &ds, int maLTC) {
    int index = TimLopTinChiTheoMa(ds, maLTC);
    if (index == -1) return false;

    ds.nodes[index]->huyLop = true;
    return true;
}

void SapXepDSLTC(DanhSachLopTinChi &ds, bool tangDan) {
    if (ds.soLuong < 2) return;

    LopTinChi** tempArray = new (std::nothrow) LopTinChi*[ds.soLuong];
    if (!tempArray) {
        std::cerr << "Lỗi: Không đủ bộ nhớ để sắp xếp danh sách lớp tín chỉ.\n";
        return;
    }

    int count = 0;
    for (int i = 0; i < MAX_LTC; i++) {
        if (ds.nodes[i] != NULL) {
            tempArray[count++] = ds.nodes[i];
        }
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            bool shouldSwap = false;
            if (tangDan && tempArray[j]->MALOPTC > tempArray[j + 1]->MALOPTC) {
                shouldSwap = true;
            } else if (!tangDan && tempArray[j]->MALOPTC < tempArray[j + 1]->MALOPTC) {
                shouldSwap = true;
            }

            if (shouldSwap) {
                LopTinChi* temp = tempArray[j];
                tempArray[j] = tempArray[j + 1];
                tempArray[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < MAX_LTC; i++) {
        ds.nodes[i] = NULL;
    }

    for (int i = 0; i < count; i++) {
        ds.nodes[i] = tempArray[i];
    }

    delete[] tempArray;
}

// --- Operation functions combining different data structures ---

bool ThemSVVaoLopTC(DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, int maLTC, const char* maSV) {
    int index = TimLopTinChiTheoMa(dsLTC, maLTC);
    if (index == -1) {
        std::cerr << "Lỗi: Lớp tín chỉ " << maLTC << " không tồn tại.\n";
        return false;
    }

    LopTinChi* lop = dsLTC.nodes[index];

    if (lop->soSVDK >= lop->sv_max) {
        std::cerr << "Lỗi: Lớp tín chỉ " << maLTC << " đã đầy.\n";
        return false;
    }

    if (lop->huyLop) {
        std::cerr << "Lỗi: Lớp tín chỉ " << maLTC << " đã bị hủy.\n";
        return false;
    }

    NodeSV* nodeSV = TimSinhVienTheoMa(dsSV, maSV);
    if (nodeSV == NULL) {
        std::cerr << "Lỗi: Sinh viên " << maSV << " không tồn tại trong danh sách sinh viên.\n";
        return false;
    }

    if (TimDangKyTheoMASV(lop->dssvdk, maSV) != NULL) {
        std::cerr << "Lỗi: Sinh viên " << maSV << " đã đăng ký lớp này rồi.\n";
        return false;
    }

    DangKy dk;
    strcpy(dk.MASV, maSV);
    dk.DIEM = -1.0f;
    dk.daCoDiem = false;

    bool success = ThemDangKyVaoDSLK(lop->dssvdk, dk);
    if (success) {
        lop->soSVDK++;
    } else {
        std::cerr << "Lỗi: Không thể thêm sinh viên " << maSV << " vào danh sách đăng ký.\n";
    }

    return success;
}

bool XoaSVKhoiLopTC(DanhSachLopTinChi &dsLTC, int maLTC, const char* maSV) {
    int index = TimLopTinChiTheoMa(dsLTC, maLTC);
    if (index == -1) return false;

    LopTinChi* lop = dsLTC.nodes[index];

    bool success = XoaDangKyTheoMASV(lop->dssvdk, maSV);
    if (success) {
        lop->soSVDK--;
    }

    return success;
}


void InDSSVDaDangKyCuaLop(const DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, int maLTC) {
    int index = TimLopTinChiTheoMa(dsLTC, maLTC);
    if (index == -1) {
        std::cout << "Lớp tín chỉ " << maLTC << " không tồn tại!\n";
        return;
    }

    LopTinChi* lop = dsLTC.nodes[index];
    if (lop->soSVDK == 0) {
        std::cout << "Lớp tín chỉ " << maLTC << " (" << lop->MAMH << ") chưa có sinh viên đăng ký.\n";
        return;
    }

    std::cout << "\n         DANH SÁCH SINH VIÊN ĐĂNG KÝ LỚP TÍN CHỈ " << maLTC << "\n";
    std::cout << "Môn học: " << lop->MAMH << " - Niên khóa: " << lop->nienkhoa
              << " - Học kỳ: " << lop->hocky << " - Nhóm: " << lop->nhom << "\n";
    std::cout << "+-----+------------+-------------------------+------------------+---------------+\n";
    std::cout << "| STT |    MASV    | Họ                      | Tên              | Lớp           |\n";
    std::cout << "+-----+------------+-------------------------+------------------+---------------+\n";

    int stt = 1;
    NodeDK* p = lop->dssvdk;

    while (p != NULL) {
        NodeSV* nodeSV = TimSinhVienTheoMa(dsSV, p->data.MASV);

        std::cout << "| " << std::setw(3) << std::left << stt << " | ";
        std::cout << std::setw(10) << std::left << p->data.MASV << " | ";

        if (nodeSV != NULL) {
            std::cout << std::setw(23) << std::left << nodeSV->data.HO << " | ";
            std::cout << std::setw(16) << std::left << nodeSV->data.TEN << " | ";
            std::cout << std::setw(13) << std::left << nodeSV->data.LOP << " |";
        } else {
            std::cout << std::setw(23) << std::left << "(Không tìm thấy)" << " | ";
            std::cout << std::setw(16) << std::left << "" << " | ";
            std::cout << std::setw(13) << std::left << "" << " |";
        }
        std::cout << "\n";

        stt++;
        p = p->next;
    }

    std::cout << "+-----+------------+-------------------------+------------------+---------------+\n";
    std::cout << "Tổng số sinh viên đã đăng ký: " << lop->soSVDK << "\n";
}

void InDSSVSapXepCuaLop(const DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, int maLTC) {
    int index = TimLopTinChiTheoMa(dsLTC, maLTC);
    if (index == -1) {
        std::cout << "Lớp tín chỉ " << maLTC << " không tồn tại!\n";
        return;
    }

    LopTinChi* lop = dsLTC.nodes[index];
    int count = lop->soSVDK;

    if (count == 0) {
        std::cout << "Lớp tín chỉ " << maLTC << " (" << lop->MAMH << ") chưa có sinh viên đăng ký!\n";
        return;
    }

    struct SVInfo {
        char MASV[16];
        char HO[31];
        char TEN[11];
        char LOP[16];
    };

    SVInfo* svArr = new (std::nothrow) SVInfo[count];
    if (!svArr) {
        std::cerr << "Lỗi: Không đủ bộ nhớ để sắp xếp danh sách sinh viên.\n";
        return;
    }

    int idx = 0;
    NodeDK* p = lop->dssvdk;

    while (p != NULL && idx < count) {
        strcpy(svArr[idx].MASV, p->data.MASV);

        NodeSV* nodeSV = TimSinhVienTheoMa(dsSV, p->data.MASV);
        if (nodeSV != NULL) {
            strcpy(svArr[idx].HO, nodeSV->data.HO);
            strcpy(svArr[idx].TEN, nodeSV->data.TEN);
            strcpy(svArr[idx].LOP, nodeSV->data.LOP);
        } else {
            strcpy(svArr[idx].HO, "(Không");
            strcpy(svArr[idx].TEN, "tìm thấy)");
            strcpy(svArr[idx].LOP, "");
        }

        idx++;
        p = p->next;
    }
    count = idx;

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            int tenCmp = strcmp(svArr[j].TEN, svArr[j + 1].TEN);
            if (tenCmp > 0) {
                SVInfo temp = svArr[j];
                svArr[j] = svArr[j + 1];
                svArr[j + 1] = temp;
            } else if (tenCmp == 0) {
                if (strcmp(svArr[j].HO, svArr[j + 1].HO) > 0) {
                    SVInfo temp = svArr[j];
                    svArr[j] = svArr[j + 1];
                    svArr[j + 1] = temp;
                }
            }
        }
    }

    std::cout << "\n      DANH SÁCH SINH VIÊN ĐĂNG KÝ LỚP TÍN CHỈ " << maLTC << " (SẮP XẾP THEO TÊN, HỌ)\n";
    std::cout << "Môn học: " << lop->MAMH << " - Niên khóa: " << lop->nienkhoa
              << " - Học kỳ: " << lop->hocky << " - Nhóm: " << lop->nhom << "\n";
    std::cout << "+-----+------------+-------------------------+------------------+---------------+\n";
    std::cout << "| STT |    MASV    | Họ                      | Tên              | Lớp           |\n";
    std::cout << "+-----+------------+-------------------------+------------------+---------------+\n";

    for (int i = 0; i < count; i++) {
        std::cout << "| " << std::setw(3) << std::left << (i + 1) << " | ";
        std::cout << std::setw(10) << std::left << svArr[i].MASV << " | ";
        std::cout << std::setw(23) << std::left << svArr[i].HO << " | ";
        std::cout << std::setw(16) << std::left << svArr[i].TEN << " | ";
        std::cout << std::setw(13) << std::left << svArr[i].LOP << " |\n";
    }

    std::cout << "+-----+------------+-------------------------+------------------+---------------+\n";
    std::cout << "Tổng số sinh viên đã đăng ký: " << count << "\n";

    delete[] svArr;
}


void HuyLopTuDongTheoNienKhoaHocKy(DanhSachLopTinChi &ds, int nienKhoa, int hocKy) {
    if (ds.soLuong == 0) {
        std::cout << "Danh sách lớp tín chỉ rỗng.\n";
        return;
    }

    int count = 0;
    for (int i = 0; i < MAX_LTC; i++) {
        if (ds.nodes[i] != NULL &&
            ds.nodes[i]->nienkhoa == nienKhoa &&
            ds.nodes[i]->hocky == hocKy &&
            !ds.nodes[i]->huyLop) {
            if (ds.nodes[i]->soSVDK < ds.nodes[i]->sv_min) {
                ds.nodes[i]->huyLop = true;
                count++;
                std::cout << "Đã hủy lớp tín chỉ " << ds.nodes[i]->MALOPTC
                          << " (MAMH: " << ds.nodes[i]->MAMH
                          << ") do số sinh viên đăng ký (" << ds.nodes[i]->soSVDK
                          << ") nhỏ hơn số tối thiểu (" << ds.nodes[i]->sv_min << ").\n";
            }
        }
    }

    if (count == 0) {
        std::cout << "Không có lớp tín chỉ nào trong niên khóa " << nienKhoa
                  << ", học kỳ " << hocKy << " cần hủy.\n";
    } else {
        std::cout << "Đã hủy " << count << " lớp tín chỉ.\n";
    }
}

void InBangDiemLop(const DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, int maLTC) {
    int index = TimLopTinChiTheoMa(dsLTC, maLTC);
    if (index == -1) {
        std::cout << "Lớp tín chỉ " << maLTC << " không tồn tại!\n";
        return;
    }

    LopTinChi* lop = dsLTC.nodes[index];
    int count = lop->soSVDK;

    if (count == 0) {
        std::cout << "Lớp tín chỉ " << maLTC << " (" << lop->MAMH << ") chưa có sinh viên đăng ký!\n";
        return;
    }

    struct DiemSV {
        char MASV[16];
        char HO[31];
        char TEN[11];
        float DIEM;
        bool daCoDiem;
    };

    DiemSV* diemArr = new (std::nothrow) DiemSV[count];
    if (!diemArr) {
        std::cerr << "Lỗi: Không đủ bộ nhớ để tạo bảng điểm.\n";
        return;
    }

    int idx = 0;
    NodeDK* p = lop->dssvdk;
    while (p != NULL && idx < count) {
        strcpy(diemArr[idx].MASV, p->data.MASV);
        diemArr[idx].DIEM = p->data.DIEM;
        diemArr[idx].daCoDiem = p->data.daCoDiem;

        NodeSV* nodeSV = TimSinhVienTheoMa(dsSV, p->data.MASV);
        if (nodeSV != NULL) {
            strcpy(diemArr[idx].HO, nodeSV->data.HO);
            strcpy(diemArr[idx].TEN, nodeSV->data.TEN);
        } else {
            strcpy(diemArr[idx].HO, "(Không");
            strcpy(diemArr[idx].TEN, "tìm thấy)");
        }

        idx++;
        p = p->next;
    }
    count = idx;

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(diemArr[j].MASV, diemArr[j + 1].MASV) > 0) {
                DiemSV temp = diemArr[j];
                diemArr[j] = diemArr[j + 1];
                diemArr[j + 1] = temp;
            }
        }
    }

    std::cout << "\n                   BẢNG ĐIỂM LỚP TÍN CHỈ " << maLTC << "\n";
    std::cout << "Môn học: " << lop->MAMH << " - Niên khóa: " << lop->nienkhoa
              << " - Học kỳ: " << lop->hocky << " - Nhóm: " << lop->nhom << "\n";
    std::cout << "+-----+------------+------------------------------------+-------+\n";
    std::cout << "| STT |    MASV    | Họ và Tên                          | Điểm  |\n";
    std::cout << "+-----+------------+------------------------------------+-------+\n";

    std::cout << std::fixed << std::setprecision(2);

    for (int i = 0; i < count; i++) {
        std::cout << "| " << std::setw(3) << std::left << (i + 1) << " | ";
        std::cout << std::setw(10) << std::left << diemArr[i].MASV << " | ";

        char hoTen[45];
        strcpy(hoTen, diemArr[i].HO);
        strcat(hoTen, " ");
        strcat(hoTen, diemArr[i].TEN);
        std::cout << std::setw(34) << std::left << hoTen << " | ";

        if (diemArr[i].daCoDiem) {
            std::cout << std::setw(5) << std::right << diemArr[i].DIEM << " |";
        } else {
            std::cout << std::setw(5) << std::right << "" << " |";
        }
        std::cout << "\n";
    }

    std::cout << "+-----+------------+------------------------------------+-------+\n";
    std::cout << "Tổng số sinh viên: " << count << "\n";

    delete[] diemArr;
}

#include <fstream>

void SaveDanhSachDangKy(DanhSachDangKy first, std::ofstream &file) {
    NodeDK* current = first;
    while (current != NULL) {
        file << current->data.MASV << "|"
             << current->data.DIEM << std::endl;
        current = current->next;
    }
}

void SaveDanhSachLopTinChi(DanhSachLopTinChi &ds, const char* filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Khong the mo file de ghi LopTinChi!\n";
        return;
    }

    for (int i = 0; i < MAX_LTC; i++) {
	    if (ds.nodes[i] != NULL) {
	        LopTinChi* ltc = ds.nodes[i];
	        file << ltc->MALOPTC << "|"
	             << ltc->MAMH << "|"
	             << ltc->nienkhoa << "|"
	             << ltc->hocky << "|"
	             << ltc->nhom << "|"
	             << ltc->sv_min << "|"
	             << ltc->sv_max << "|"
	             << ltc->huyLop << "|"
	             << ltc->soSVDK << std::endl;
	
	        SaveDanhSachDangKy(ltc->dssvdk, file);
	        file << "#ENDCLASS" << std::endl;
	    }
	}
	file << "#END" << std::endl;
}


void LoadDanhSachLopTinChi(DanhSachLopTinChi &ds, const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Khong the mo file de doc LopTinChi!\n";
        return;
    }

    KhoiTaoDSLTC(ds);

    std::string line;
    LopTinChi* currentLTC = NULL;

    while (std::getline(file, line)) {
        if (line == "#END") break;
        if (line == "#ENDCLASS") {
            currentLTC = NULL;
            continue;
        }

        std::stringstream ss(line);
        std::string token;

        if (currentLTC == NULL) {
            // Đây là dòng thông tin LopTinChi
            currentLTC = new LopTinChi;
            std::getline(ss, token, '|'); currentLTC->MALOPTC = stoi(token);
            std::getline(ss, token, '|'); strcpy(currentLTC->MAMH, token.c_str());
            std::getline(ss, token, '|'); currentLTC->nienkhoa = stoi(token);
            std::getline(ss, token, '|'); currentLTC->hocky = stoi(token);
            std::getline(ss, token, '|'); currentLTC->nhom = stoi(token);
            std::getline(ss, token, '|'); currentLTC->sv_min = stoi(token);
            std::getline(ss, token, '|'); currentLTC->sv_max = stoi(token);
            std::getline(ss, token, '|'); currentLTC->huyLop = (token == "1");
            std::getline(ss, token, '|'); currentLTC->soSVDK = stoi(token);

            KhoiTaoDSDangKy(currentLTC->dssvdk);

            // Tìm vị trí trống trong ds.nodes[]
            int emptyIndex = -1;
            for (int i = 0; i < MAX_LTC; i++) {
                if (ds.nodes[i] == NULL) {
                    emptyIndex = i;
                    break;
                }
            }

            if (emptyIndex != -1) {
                ds.nodes[emptyIndex] = currentLTC;
                ds.soLuong++;
            } else {
                std::cerr << "Danh sach Lop Tin Chi day, khong them duoc!\n";
                delete currentLTC;
                currentLTC = NULL;
            }
        } else {
            // Đây là dòng thông tin sinh viên đăng ký
            DangKy dk;
            std::getline(ss, token, '|'); strcpy(dk.MASV, token.c_str());
            std::getline(ss, token, '|'); dk.DIEM = stof(token);
            dk.daCoDiem = (dk.DIEM >= 0.0f);

            ThemDangKyVaoDSLK(currentLTC->dssvdk, dk);
        }
    }

    file.close();
}



// --- END OF FILE LopTinChi.cpp ---