#ifndef MONHOC_H
#define MONHOC_H

// Forward declaration của AVLTree
struct NodeAVL;
typedef NodeAVL* AVLTree;

struct MonHoc {
    char MAMH[11];
    char TENMH[51];
    int STCLT;
    int STCTH;
};

typedef AVLTree DanhSachMonHoc;

// Hàm quản lý danh sách môn học
NodeAVL* TimMonHocTheoMa(DanhSachMonHoc ds, const char* maMH);
DanhSachMonHoc ThemMonHoc(DanhSachMonHoc ds, MonHoc mh);
DanhSachMonHoc XoaMonHoc(DanhSachMonHoc ds, const char* maMH);
void CapNhatMonHoc(DanhSachMonHoc ds, const char* maMH, MonHoc mhMoi);
void InDanhSachMonHoc(DanhSachMonHoc ds);
void InDanhSachMonHocSapXepTheoTen(DanhSachMonHoc ds);
void GiaiPhongDSMonHoc(DanhSachMonHoc &ds);
int DemSoMonHoc(DanhSachMonHoc ds);

// Hàm hỗ trợ cho sắp xếp
void ThuThapMonHoc(DanhSachMonHoc ds, MonHoc* &arr, int &size, int &capacity);
void SapXepTheoTenMonHoc(MonHoc* arr, int size);

#endif // MONHOC_H