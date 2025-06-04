#include "Diem.h"
#include "LopTinChi.h"
#include "MonHoc.h"
#include "AVLTree.h"
#include <iostream>
#include <cstring>
#include <iomanip>
#include <new>
#include <vector> 
#include <string> 

bool KiemTraChuoiHopLe(const char* str, int maxLen) {
    if (str == NULL || str[0] == '\0') return false;
    if (strlen(str) > maxLen) return false;
    return true;
}

bool NhapDiemSinhVienLopTC(DanhSachLopTinChi &dsLTC, int maLTC, const char* maSV, float diem) {
    if (diem < 0.0f || diem > 10.0f) {
        std::cerr << "Loi: Diem phai trong khoang 0.0 den 10.0.\n";
        return false;
    }
    if (!KiemTraChuoiHopLe(maSV, MAX_MASV_LEN)) {
        std::cerr << "Loi: Ma sinh vien khong hop le.\n";
        return false;
    }
    int index = TimLopTinChiTheoMa(dsLTC, maLTC);
    if (index == -1) {
        std::cerr << "Loi: Lop tin chi " << maLTC << " khong ton tai.\n";
        return false;
    }
    LopTinChi* lop = dsLTC.nodes[index];
    if (lop->huyLop) {
        std::cerr << "Loi: Lop tin chi " << maLTC << " da bi huy.\n";
        return false;
    }
    
    NodeDK* nodeDK = TimDangKyTheoMASV(lop->dssvdk, maSV);
    if (nodeDK == NULL) {
        std::cerr << "Loi: Sinh vien " << maSV << " chua dang ky lop tin chi " << maLTC << ".\n";
        return false;
    }
    nodeDK->data.DIEM = diem;
    nodeDK->data.daCoDiem = true;
    return true;
}


void NhapDiemTheoBang(DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, int maLTC) {
    int index = TimLopTinChiTheoMa(dsLTC, maLTC);
    if (index == -1) {
        std::cout << "Lop tin chi " << maLTC << " khong ton tai!\n";
        return;
    }
    LopTinChi* lop = dsLTC.nodes[index];
    int count = lop->soSVDK;
    if (count == 0) {
        std::cout << "Lop tin chi " << maLTC << " chua co sinh vien dang ky!\n";
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
        std::cerr << "Loi: Khong du bo nho de tao bang diem.\n";
        return;
    }
	//demsosv
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
            strcpy(diemArr[idx].HO, "(Khong)");
            strcpy(diemArr[idx].TEN, "(tim thay)");
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

    std::cout << "\n                   NHAP DIEM LOP TIN CHI " << maLTC << "\n";
    std::cout << "Mon hoc: " << lop->MAMH << " - Nien khoa: " << lop->nienkhoa
              << " - Hoc ky: " << lop->hocky << " - Nhom: " << lop->nhom << "\n";
    std::cout << "+-----+------------+------------------------------------+-------+\n";
    std::cout << "| STT |    MASV    | Ho va Ten                          | Diem  |\n";
    std::cout << "+-----+------------+------------------------------------+-------+\n";
    std::cout << std::fixed << std::setprecision(2);

    for (int i = 0; i < count; i++) {
        std::cout << "| " << std::setw(3) << std::left << (i + 1) << " | ";
        std::cout << std::setw(10) << std::left << diemArr[i].MASV << " | ";
        char hoTen[45];
        strcpy(hoTen, diemArr[i].	HO);
        strcat(hoTen, " ");
        strcat(hoTen, diemArr[i].TEN);
        std::cout << std::setw(34) << std::left << hoTen << " | ";
        if (diemArr[i].daCoDiem) {
            std::cout << std::setw(5) << std::right << diemArr[i].DIEM << " |\n";
        } else {
            std::cout << std::setw(5) << std::right << "" << " |\n";
        }
    }
    std::cout << "+-----+------------+------------------------------------+-------+\n";

    std::cout << "Nhap diem cho tung sinh vien (nhap -1 de bo qua, 0-10 de cap nhat):\n";
    for (int i = 0; i < count; i++) {
        float diem;
        std::cout << "Sinh vien " << diemArr[i].MASV << " (" << diemArr[i].HO << " " << diemArr[i].TEN << "): ";
        std::cin >> diem;
        if (diem >= 0.0f && diem <= 10.0f) {
            NhapDiemSinhVienLopTC(dsLTC, maLTC, diemArr[i].MASV, diem);
        } else if (diem != -1.0f) {
            std::cerr << "Loi: Diem khong hop le, bo qua.\n";
        }
    }

    delete[] diemArr;
    std::cout << "Da nhap diem xong.\n";
}

void InBangDiemMonHoc(const DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, const DanhSachMonHoc &dsMH, const char* maMH) {
    if (!KiemTraChuoiHopLe(maMH, 10)) {
        std::cout << "Loi: Ma mon hoc khong hop le!\n";
        return;
    }

    char tenMH[51] = "Unknown";
    NodeAVL* pMH = TimMonHocTheoMa(dsMH, maMH); 
    if (pMH != NULL) {
        strcpy(tenMH, pMH->data.TENMH);
    }

    int countLTC = 0;
    for (int i = 0; i < MAX_LTC; i++) {
        if (dsLTC.nodes[i] != NULL && strcmp(dsLTC.nodes[i]->MAMH, maMH) == 0 && !dsLTC.nodes[i]->huyLop) {
            countLTC++;
        }
    }
    if (countLTC == 0) {
        std::cout << "Khong co lop tin chi nao thuoc mon hoc '" << maMH << "'!\n";
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
        if (dsLTC.nodes[i] != NULL && strcmp(dsLTC.nodes[i]->MAMH, maMH) == 0 && !dsLTC.nodes[i]->huyLop) {
            totalSV += dsLTC.nodes[i]->soSVDK;
        }
    }
    if (totalSV == 0) {
        std::cout << "Mon hoc '" << maMH << "' chua co sinh vien dang ky!\n";
        return;
    }

    DiemSV* diemArr = new (std::nothrow) DiemSV[totalSV];
    if (!diemArr) {
        std::cerr << "Loi: Khong du bo nho de tao bang diem mon hoc!\n";
        return;
    }

    int idx = 0;
    for (int i = 0; i < MAX_LTC; i++) {
        if (dsLTC.nodes[i] != NULL && strcmp(dsLTC.nodes[i]->MAMH, maMH) == 0 && !dsLTC.nodes[i]->huyLop) {
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
                    strcpy(diemArr[idx].HO, "(Khong)");
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

    std::cout << "\n                   BANG DIEM MON HOC " << tenMH << " (" << maMH << ")\n";
    std::cout << "+-----+------------+------------------------------------+-------+-----------------+\n";
    std::cout << "| STT |    MASV    | Ho va Ten                          | Diem  | Ma Lop Tin Chi  |\n";
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
    std::cout << "Tong so sinh vien: " << totalSV << "\n";

    delete[] diemArr;
}

void InBangDiemTrungBinhKhoa(const DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, const DanhSachMonHoc &dsMH, const char* maLop) {
    if (!KiemTraChuoiHopLe(maLop, 15)) {
        std::cout << "Loi: Ma lop khong hop le!\n";
        return;
    }
    
    int totalSV = 0;
    NodeSV* pSV = dsSV;
    while (pSV != NULL) {
        if (strcmp(pSV->data.LOP, maLop) == 0) totalSV++;
        pSV = pSV->next;
    }

    struct DiemTB {
        char MASV[16];
        char HO[31];
        char TEN[11];
        float diemTB;
        int tongTinChi;
    };
	DiemTB* diemArr = new (std::nothrow) DiemTB[totalSV];

    if (!diemArr) {
        std::cerr << "Loi: Khong du bo nho de tao bang diem trung binh!\n";
        return;
    }

    int idx = 0;
    pSV = dsSV;
    while (pSV != NULL && idx < totalSV) {
        if (strcmp(pSV->data.LOP, maLop) == 0) {
            strcpy(diemArr[idx].MASV, pSV->data.MASV);
            strcpy(diemArr[idx].HO, pSV->data.HO);
            strcpy(diemArr[idx].TEN, pSV->data.TEN);
            diemArr[idx].diemTB = 0.0f;
            diemArr[idx].tongTinChi = 0;
            idx++;
        }
        pSV = pSV->next;
    }
    totalSV = idx;
    
    if (totalSV == 0) {
        std::cout << "Lop " << maLop << " khong co sinh vien!\n";
        return;
    }

    for (int i = 0; i < totalSV; i++) {
        float tongDiem = 0.0f;
        int tongTinChi = 0;
        for (int j = 0; j < MAX_LTC; j++) {
            if (dsLTC.nodes[j] != NULL && !dsLTC.nodes[j]->huyLop) {
                NodeDK* pDK = dsLTC.nodes[j]->dssvdk;
                while (pDK != NULL) {
                	//tinhdiem
                    if (strcmp(pDK->data.MASV, diemArr[i].MASV) == 0 && pDK->data.daCoDiem) {
                        NodeAVL* pMH = TimMonHocTheoMa(dsMH, dsLTC.nodes[j]->MAMH);
                        int tinChi = (pMH != NULL) ? (pMH->data.STCLT + pMH->data.STCTH) : 0;
                        tongDiem += pDK->data.DIEM * tinChi;
                        tongTinChi += tinChi;
                    }
                    pDK = pDK->next;
                }
            }
        }
        if (tongTinChi > 0) {
            diemArr[i].diemTB = tongDiem / tongTinChi;
        }
        diemArr[i].tongTinChi = tongTinChi;
    }

 	//bbsort
    for (int i = 0; i < totalSV - 1; i++) {
        for (int j = 0; j < totalSV - i - 1; j++) {
            if (strcmp(diemArr[j].MASV, diemArr[j + 1].MASV) > 0) {
                DiemTB temp = diemArr[j];
                diemArr[j] = diemArr[j + 1];
                diemArr[j + 1] = temp;
            }
        }
    }


    std::cout << "\n                   BANG THONG KE DIEM TRUNG BINH KHOA HOC\n";
    std::cout << "Lop: " << maLop << "\n";
    std::cout << "+-----+------------+------------------------------------+----------+\n";
    std::cout << "| STT |    MASV    | Ho va Ten                          | Diem TB  |\n";
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
        if (diemArr[i].tongTinChi > 0) {
            std::cout << std::setw(8) << std::right << diemArr[i].diemTB << " |\n";
        } else {
            std::cout << std::setw(8) << std::right << "" << " |\n";
        }
    }
    std::cout << "+-----+------------+------------------------------------+----------+\n";
    std::cout << "Tong so sinh vien: " << totalSV << "\n";

    delete[] diemArr;
}


void InBangDiemTongKet(const DanhSachLopTinChi &dsLTC, const DanhSachSinhVien &dsSV, const DanhSachMonHoc &dsMH, const char* maLop) {
    if (!KiemTraChuoiHopLe(maLop, 15)) {
        std::cout << "Loi: Ma lop khong hop le!\n";
        return;
    }
  
    int totalSV = 0;
    NodeSV* pSV = dsSV;
    while (pSV != NULL) {
        if (strcmp(pSV->data.LOP, maLop) == 0) totalSV++;
        pSV = pSV->next;
    }
    
    if (totalSV == 0) {
        std::cout << "Lop " << maLop << " khong co sinh vien!\n";
        return;
    }

    struct DiemTK {
        char MASV[16];
        char HO[31];
        char TEN[11];
        float diem[100]; 
    };

    DiemTK* diemArr = new (std::nothrow) DiemTK[totalSV];
    if (!diemArr) {
        std::cerr << "Loi: Khong du bo nho de tao bang diem tong ket!\n";
        return;
    }

   
    const int MAX_MONHOC = 100;
	char maMHList[MAX_MONHOC][11];
	int numMH = 0;
	
	InorderTraversal(dsMH, [&](MonHoc mh) {
	    bool monDuocHoc = false;
	//duyetcaymh
	    for (int i = 0; i < totalSV && !monDuocHoc; i++) {
	        for (int j = 0; j < MAX_LTC && !monDuocHoc; j++) {
	            if (dsLTC.nodes[j] != NULL && !dsLTC.nodes[j]->huyLop &&
	                strcmp(dsLTC.nodes[j]->MAMH, mh.MAMH) == 0) {
					//dsdksv cua ltc
	                NodeDK* pDK = dsLTC.nodes[j]->dssvdk;
	                while (pDK != NULL) {
	                    if (strcmp(pDK->data.MASV, diemArr[i].MASV) == 0 && pDK->data.daCoDiem) {
	                        monDuocHoc = true;
	                        break;
	                    }
	                    pDK = pDK->next;
	                }
	            }
	        }
	    }
	
	    if (monDuocHoc && numMH < MAX_MONHOC) {
	        strcpy(maMHList[numMH], mh.MAMH);
	        numMH++;
	    }
	});


  
    int idx = 0;
    pSV = dsSV;
    while (pSV != NULL && idx < totalSV) {
        if (strcmp(pSV->data.LOP, maLop) == 0) {
            strcpy(diemArr[idx].MASV, pSV->data.MASV);
            strcpy(diemArr[idx].HO, pSV->data.HO);
            strcpy(diemArr[idx].TEN, pSV->data.TEN);
            for (int j = 0; j < numMH; j++) {
                diemArr[idx].diem[j] = -1.0f; // -1 nghĩa là chưa có điểm
            }
            idx++;
        }
        pSV = pSV->next;
    }
    totalSV = idx;

   
    for (int i = 0; i < totalSV; i++) {
        for (int j = 0; j < MAX_LTC; j++) {
            if (dsLTC.nodes[j] != NULL && !dsLTC.nodes[j]->huyLop) {
                NodeDK* pDK = dsLTC.nodes[j]->dssvdk;
                while (pDK != NULL) {
                    if (strcmp(pDK->data.MASV, diemArr[i].MASV) == 0 && pDK->data.daCoDiem) {
                        for (int k = 0; k < numMH; k++) {
                            if (strcmp(dsLTC.nodes[j]->MAMH, maMHList[k]) == 0) {
                                if (diemArr[i].diem[k] < pDK->data.DIEM) {
                                    diemArr[i].diem[k] = pDK->data.DIEM;
                                }
                            }
                        }
                    }
                    pDK = pDK->next;
                }
            }
        }
    }

 
    for (int i = 0; i < totalSV - 1; i++) {
        for (int j = 0; j < totalSV - i - 1; j++) {
            if (strcmp(diemArr[j].MASV, diemArr[j + 1].MASV) > 0) {
                DiemTK temp = diemArr[j];
                diemArr[j] = diemArr[j + 1];
                diemArr[j + 1] = temp;
            }
        }
    }

    std::cout << "\n                   BANG DIEM TONG KET\n";
    std::cout << "Lop: " << maLop << "\n";
    std::cout << "+-----+------------+------------------------------------+";
    for (int i = 0; i < numMH; i++) {
        std::cout << std::setw(10) << maMHList[i] << "|";
    }
    std::cout << "\n";
    std::cout << "| STT |    MASV    | Ho va Ten                          |";
    for (int i = 0; i < numMH; i++) {
        std::cout << std::setw(10) << "         " << "|";
    }
    std::cout << "\n";
    std::cout << "+-----+------------+------------------------------------+";
    for (int i = 0; i < numMH; i++) {
        std::cout << "----------|";
    }
    std::cout << "\n";
    std::cout << std::fixed << std::setprecision(2);

    for (int i = 0; i < totalSV; i++) {
        std::cout << "| " << std::setw(3) << std::left << (i + 1) << " | ";
        std::cout << std::setw(10) << std::left << diemArr[i].MASV << " | ";
        char hoTen[45];
        strcpy(hoTen, diemArr[i].HO);
        strcat(hoTen, " ");
        strcat(hoTen, diemArr[i].TEN);
        std::cout << std::setw(31) << std::left << hoTen << " | ";
        for (int j = 0; j < numMH; j++) {
            if (diemArr[i].diem[j] >= 0.0f) {
                std::cout << std::setw(9) << std::right << diemArr[i].diem[j] << " |";
            } else {
                std::cout << std::setw(9) << std::right << "" << " |";
            }
        }
        std::cout << "\n";
    }
    std::cout << "+-----+------------+------------------------------------+";
    for (int i = 0; i < numMH; i++) {
        std::cout << "----------|";
    }
    std::cout << "\n";
    std::cout << "Tong so sinh vien: " << totalSV << "\n";

    delete[] diemArr;
}