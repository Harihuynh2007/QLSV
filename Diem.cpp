#include "Diem.h"
#include <iostream>
#include <cstring>
#include <iomanip>

bool NhapDiemSinhVienLopTC(DanhSachLopTinChi &dsLTC, int maLTC, const char* maSV, float diem) {
    if (diem < 0.0f || diem > 10.0f) {
        std::cerr << "Lỗi: Điểm phải trong khoảng từ 0.0 đến 10.0.\n";
        return false;
    }
    int index = TimLopTinChiTheoMa(dsLTC, maLTC);
    if (index == -1) {
        std::cerr << "Lỗi: Lớp tín chỉ " << maLTC << " không tồn tại.\n";
        return false;
    }
    LopTinChi* lop = dsLTC.nodes[index];
    if (lop->huyLop) {
        std::cerr << "Lỗi: Lớp tín chỉ " << maLTC << " đã bị hủy, không thể nhập điểm.\n";
        return false;
    }
    NodeDK* nodeDK = TimDangKyTheoMASV(lop->dssvdk, maSV);
    if (nodeDK == NULL) {
        std::cerr << "Lỗi: Sinh viên " << maSV << " chưa đăng ký lớp tín chỉ " << maLTC << ".\n";
        return false;
    }
    nodeDK->data.DIEM = diem;
    nodeDK->data.daCoDiem = true;
    return true;
}

void InBangDiemMonHoc(const DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, const char* maMH) {
    if (maMH == NULL || maMH[0] == '\0') {
        std::cout << "Lỗi: Mã môn học không hợp lệ!\n";
        return;
    }

    int countLTC = 0;
    for (int i = 0; i < MAX_LTC; i++) {
        if (dsLTC.nodes[i] != NULL && strcmp(dsLTC.nodes[i]->MAMH, maMH) == 0) {
            countLTC++;
        }
    }

    if (countLTC == 0) {
        std::cout << "Không có lớp tín chỉ nào thuộc môn học '" << maMH << "'!\n";
        return;
    }

    struct DiemSV {
        char MASV[16];
        char HO[31];
        char TEN[11];
        float DIEM;
        bool daCoDiem;
        int maLTC;
    };

    int totalSV = 0;
    for (int i = 0; i < MAX_LTC; i++) {
        if (dsLTC.nodes[i] != NULL && strcmp(dsLTC.nodes[i]->MAMH, maMH) == 0) {
            totalSV += dsLTC.nodes[i]->soSVDK;
        }
    }

    if (totalSV == 0) {
        std::cout << "Môn học '" << maMH << "' chưa có sinh viên đăng ký!\n";
        return;
    }

    DiemSV* diemArr = new (std::nothrow) DiemSV[totalSV];
    if (!diemArr) {
        std::cerr << "Lỗi: Không đủ bộ nhớ để tạo bảng điểm môn học!\n";
        return;
    }

    int idx = 0;
    for (int i = 0; i < MAX_LTC; i++) {
        if (dsLTC.nodes[i] != NULL && strcmp(dsLTC.nodes[i]->MAMH, maMH) == 0) {
            LopTinChi* lop = dsLTC.nodes[i];
            NodeDK* p = lop->dssvdk;
            while (p != NULL && idx < totalSV) {
                strcpy(diemArr[idx].MASV, p->data.MASV);
                diemArr[idx].DIEM = p->data.DIEM;
                diemArr[idx].daCoDiem = p->data.daCoDiem;
                diemArr[idx].maLTC = lop->MALOPTC;

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
        }
    }
    totalSV = idx;

    for (int i = 0; i < totalSV - 1; i++) {
        for (int j = 0; j < totalSV - i - 1; j++) {
            if (strcmp(diemArr[j].MASV, diemArr[j + 1].MASV) > 0) {
                DiemSV temp = diemArr[j];
                diemArr[j] = diemArr[j + 1];
                diemArr[j + 1] = temp;
            }
        }
    }

    std::cout << "\n                   BẢNG ĐIỂM MÔN HỌC " << maMH << "\n";
    std::cout << "+-----+------------+------------------------------------+-------+-----------------+\n";
    std::cout << "| STT |    MASV    | Họ và Tên                          | Điểm  | Mã Lớp Tín Chỉ  |\n";
    std::cout << "+-----+------------+------------------------------------+-------+-----------------+\n";

    std::cout << std::fixed << std::setprecision(2);

    for (int i = 0; i < totalSV; i++) {
        std::cout << "| " << std::setw(3) << std::left << (i + 1) << " | ";
        std::cout << std::setw(10) << std::left << diemArr[i].MASV << " | ";

        char hoTen[45];
        strcpy(hoTen, diemArr[i].HO);
        strcat(hoTen, " ");
        strcat(hoTen, diemArr[i].TEN);
        std::cout << std::setw(34) << std::left << hoTen << " | ";

        if (diemArr[i].daCoDiem) {
            std::cout << std::setw(5) << std::right << diemArr[i].DIEM << " | ";
        } else {
            std::cout << std::setw(5) << std::right << "" << " | ";
        }
        std::cout << std::setw(15) << std::left << diemArr[i].maLTC << " |\n";
    }

    std::cout << "+-----+------------+------------------------------------+-------+-----------------+\n";
    std::cout << "Tổng số sinh viên: " << totalSV << "\n";

    delete[] diemArr;
}

void InBangDiemTrungBinhKhoa(const DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, const char* tenLop) {
    if (tenLop == NULL || tenLop[0] == '\0') {
        std::cout << "Lỗi: Tên lớp không hợp lệ!\n";
        return;
    }

    // Đếm số sinh viên trong lớp
    int totalSV = 0;
    NodeSV* pSV = dsSV;
    while (pSV != NULL) {
        if (strcmp(pSV->data.LOP, tenLop) == 0) {
            totalSV++;
        }
        pSV = pSV->next;
    }

    if (totalSV == 0) {
        std::cout << "Lớp '" << tenLop << "' không có sinh viên nào!\n";
        return;
    }

    struct DiemTB {
        char MASV[16];
        char HO[31];
        char TEN[11];
        float diemTB;
        int soMon;
    };

    DiemTB* diemArr = new (std::nothrow) DiemTB[totalSV];
    if (!diemArr) {
        std::cerr << "Lỗi: Không đủ bộ nhớ để tạo bảng điểm trung bình!\n";
        return;
    }

    int idx = 0;
    pSV = dsSV;
    while (pSV != NULL && idx < totalSV) {
        if (strcmp(pSV->data.LOP, tenLop) == 0) {
            strcpy(diemArr[idx].MASV, pSV->data.MASV);
            strcpy(diemArr[idx].HO, pSV->data.HO);
            strcpy(diemArr[idx].TEN, pSV->data.TEN);
            diemArr[idx].diemTB = 0.0f;
            diemArr[idx].soMon = 0;

            // Tính điểm trung bình
            float tongDiem = 0.0f;
            int soMon = 0;
            for (int i = 0; i < MAX_LTC; i++) {
                if (dsLTC.nodes[i] != NULL) {
                    NodeDK* pDK = dsLTC.nodes[i]->dssvdk;
                    while (pDK != NULL) {
                        if (strcmp(pDK->data.MASV, pSV->data.MASV) == 0 && pDK->data.daCoDiem) {
                            tongDiem += pDK->data.DIEM;
                            soMon++;
                        }
                        pDK = pDK->next;
                    }
                }
            }
            if (soMon > 0) {
                diemArr[idx].diemTB = tongDiem / soMon;
            }
            diemArr[idx].soMon = soMon;
            idx++;
        }
        pSV = pSV->next;
    }
    totalSV = idx;

    if (totalSV == 0) {
        std::cout << "Lớp '" << tenLop << "' không có sinh viên nào!\n";
        delete[] diemArr;
        return;
    }

    for (int i = 0; i < totalSV - 1; i++) {
        for (int j = 0; j < totalSV - i - 1; j++) {
            if (strcmp(diemArr[j].MASV, diemArr[j + 1].MASV) > 0) {
                DiemTB temp = diemArr[j];
                diemArr[j] = diemArr[j + 1];
                diemArr[j + 1] = temp;
            }
        }
    }

    std::cout << "\n                   BẢNG ĐIỂM TRUNG BÌNH KHOA - LỚP " << tenLop << "\n";
    std::cout << "+-----+------------+------------------------------------+----------+\n";
    std::cout << "| STT |    MASV    | Họ và Tên                          | Điểm TB  |\n";
    std::cout << "+-----+------------+------------------------------------+----------+\n";

    std::cout << std::fixed << std::setprecision(2);

    for (int i = 0; i < totalSV; i++) {
        std::cout << "| " << std::setw(3) << std::left << (i + 1) << " | ";
        std::cout << std::setw(10) << std::left << diemArr[i].MASV << " | ";

        char hoTen[45];
        strcpy(hoTen, diemArr[i].HO);
        strcat(hoTen, " ");
        strcat(hoTen, diemArr[i].TEN);
        std::cout << std::setw(34) << std::left << hoTen << " | ";

        if (diemArr[i].soMon > 0) {
            std::cout << std::setw(8) << std::right << diemArr[i].diemTB << " |\n";
        } else {
            std::cout << std::setw(8) << std::right << "" << " |\n";
        }
    }

    std::cout << "+-----+------------+------------------------------------+----------+\n";
    std::cout << "Tổng số sinh viên: " << totalSV << "\n";

    delete[] diemArr;
}

void InBangDiemTongKet(const DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, const char* maSV) {
    if (maSV == NULL || maSV[0] == '\0') {
        std::cout << "Lỗi: Mã sinh viên không hợp lệ!\n";
        return;
    }

    NodeSV* nodeSV = TimSinhVienTheoMa(dsSV, maSV);
    if (nodeSV == NULL) {
        std::cout << "Không tìm thấy sinh viên '" << maSV << "'!\n";
        return;
    }

    struct DiemMon {
        char MAMH[11];
        float DIEM;
        bool daCoDiem;
    };

    int totalMon = 0;
    for (int i = 0; i < MAX_LTC; i++) {
        if (dsLTC.nodes[i] != NULL) {
            NodeDK* pDK = dsLTC.nodes[i]->dssvdk;
            while (pDK != NULL) {
                if (strcmp(pDK->data.MASV, maSV) == 0) {
                    totalMon++;
                }
                pDK = pDK->next;
            }
        }
    }

    if (totalMon == 0) {
        std::cout << "Sinh viên '" << maSV << "' chưa đăng ký môn học nào!\n";
        return;
    }

    DiemMon* diemArr = new (std::nothrow) DiemMon[totalMon];
    if (!diemArr) {
        std::cerr << "Lỗi: Không đủ bộ nhớ để tạo bảng điểm tổng kết!\n";
        return;
    }

    int idx = 0;
    for (int i = 0; i < MAX_LTC; i++) {
        if (dsLTC.nodes[i] != NULL) {
            NodeDK* pDK = dsLTC.nodes[i]->dssvdk;
            while (pDK != NULL && idx < totalMon) {
                if (strcmp(pDK->data.MASV, maSV) == 0) {
                    strcpy(diemArr[idx].MAMH, dsLTC.nodes[i]->MAMH);
                    diemArr[idx].DIEM = pDK->data.DIEM;
                    diemArr[idx].daCoDiem = pDK->data.daCoDiem;
                    idx++;
                }
                pDK = pDK->next;
            }
        }
    }
    totalMon = idx;

    for (int i = 0; i < totalMon - 1; i++) {
        for (int j = 0; j < totalMon - i - 1; j++) {
            if (strcmp(diemArr[j].MAMH, diemArr[j + 1].MAMH) > 0) {
                DiemMon temp = diemArr[j];
                diemArr[j] = diemArr[j + 1];
                diemArr[j + 1] = temp;
            }
        }
    }

    std::cout << "\n                   BẢNG ĐIỂM TỔNG KẾT - SINH VIÊN " << maSV << "\n";
    std::cout << "Họ và Tên: " << nodeSV->data.HO << " " << nodeSV->data.TEN << "\n";

    std::cout << "+-----+------------+";
    for (int i = 0; i < totalMon; i++) {
        std::cout << "------------+";
    }
    std::cout << "\n";

    std::cout << "| STT |    MASV    |";
    for (int i = 0; i < totalMon; i++) {
        std::cout << " " << std::setw(10) << std::left << diemArr[i].MAMH << " |";
    }
    std::cout << "\n";

    std::cout << "+-----+------------+";
    for (int i = 0; i < totalMon; i++) {
        std::cout << "------------+";
    }
    std::cout << "\n";

    std::cout << "| " << std::setw(3) << std::left << 1 << " | ";
    std::cout << std::setw(10) << std::left << maSV << " |";
    std::cout << std::fixed << std::setprecision(2);
    for (int i = 0; i < totalMon; i++) {
        if (diemArr[i].daCoDiem) {
            std::cout << " " << std::setw(10) << std::right << diemArr[i].DIEM << " |";
        } else {
            std::cout << " " << std::setw(10) << std::right << "" << " |";
        }
    }
    std::cout << "\n";

    std::cout << "+-----+------------+";
    for (int i = 0; i < totalMon; i++) {
        std::cout << "------------+";
    }
    std::cout << "\n";

    delete[] diemArr;
}