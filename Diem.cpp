#include "Diem.h"
#include <iostream>
#include <cstring>
#include <iomanip>

bool NhapDiemSinhVienLopTC(DanhSachLopTinChi &dsLTC, int maLTC, const char* maSV, float diem) {
	if(diem < 0.0f || diem > 10.0f){
		std::cerr << "Loi : Diem phai trong khoan 0.0 den 10.0 \n";
		return false;
	}
	int index = TimLopTinChiTheoMa(dsLTC, maLTC);
	if(index == -1){
		std::cerr << "Loi: Lop tin chi " << maLTC << " khong ton tai.\n";
		return false;
	}
	LopTinChi* lop = dsLTC.nodes[index];
	if (lop->huyLop) {
        std::cerr << "Loi : Lop tin chi " << maLTC << " da bi huy, khong the nhap diem.\n";
        return false;
    }
    NodeDK* nodeDK = TimDangKyTheoMASV(lop->dssvdk, maSV);
    if (nodeDK == NULL) {
        std::cerr << "Loi: Sinh vien " << maSV << " chua dang ky lop tin chi " << maLTC << ".\n";
        return false;
    }
    nodeDK-> data.DIEM = diem;
    nodeDK-> data.daCoDiem = true;
    return true;	
}

void InBangDiemMonHoc(const DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, const char* maMH) {
	if (maMH == NULL || maMH[0] == '\0') {
        std::cout << "Loi: Ma mon hoc khong hop le!\n";
        return;
    }
    
    int countLTC = 0;
    for (int i = 0; i < MAX_LTC; i++) {
        if (dsLTC.nodes[i] != NULL && strcmp(dsLTC.nodes[i]->MAMH, maMH) == 0) {
            countLTC++;
        }
    }
    
    if (countLTC == 0) {
        std::cout << "khong co lop tin chi nao thuoc mon hoc '" << maMH << "'!\n";
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
        std::cout << "Mon hoc '" << maMH << "' chua co sinh vien dang ky!\n";
        return;
    }
    DiemSV* diemArr = new (std::nothrow) DiemSV[totalSV];
    if (!diemArr) {
        std::cerr << "Loi: khong du bo nho de tao bang diem mon hoc !\n";
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
                    strcpy(diemArr[idx].HO, "(khong)");
                    strcpy(diemArr[idx].TEN, "(tim thay)");
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
	
	for(int i = 0; i < totalSV; i++){
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