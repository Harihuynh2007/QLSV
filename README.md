# Quản Lý Sinh Viên - Dự Án Cấu Trúc Dữ Liệu Và Giải Thuật (CTDL-GT)

## 1. Mô tả dự án
Hệ thống quản lý sinh viên cho trường đại học, bao gồm quản lý:
- Môn học
- Lớp sinh viên
- Sinh viên
- Lớp tín chỉ
- Điểm số

Dữ liệu lưu trữ ra file, cho phép nạp lại sau mỗi lần mở chương trình.

---

## 2. Cấu trúc dữ liệu đã sử dụng

| Thành phần | Cấu trúc dùng | Ghi chú |
|:---|:---|:---|
| Môn học | **Cây cân bằng AVL** (`AVLTree`) | Quản lý các môn học |
| Sinh viên trong lớp | **Danh sách liên kết đơn** (`NodeSV`) | Sinh viên thuộc lớp sinh viên |
| Lớp sinh viên | **Mảng động** (`DanhSachLopSV`) | Quản lý danh sách các lớp sinh viên |
| Lớp tín chỉ | **Mảng tĩnh con trỏ** (`DanhSachLopTinChi`) | Lưu lớp tín chỉ đăng ký theo môn học |
| Danh sách đăng ký lớp tín chỉ | **Danh sách liên kết đơn** (`NodeDK`) | Sinh viên đăng ký lớp tín chỉ |

---

## 3. Các chức năng đã hoàn thành

| Chức năng | Trạng thái | Ghi chú |
|:---|:---|:---|
| Thêm, sửa, xóa môn học (AVL Tree) | ✅ |
| Thêm, sửa, xóa lớp sinh viên | ✅ |
| Thêm, sửa, xóa sinh viên trong lớp | ✅ |
| Thêm, sửa, xóa lớp tín chỉ | ✅ |
| Đăng ký môn học cho sinh viên | ✅ |
| Nhập điểm cho sinh viên | ✅ |
| Xem danh sách điểm theo lớp tín chỉ | ✅ |
| Lưu dữ liệu ra file: `MonHoc.txt`, `LopSV.txt`, `LopTinChi.txt` | ✅ |
| Load dữ liệu từ file khi mở chương trình | ✅ |
| Menu điều hướng người dùng (giao diện console) | ✅ |

---

## 4. Các file source trong dự án

| File | Nội dung |
|:---|:---|
| `main.cpp` | Giao diện menu, gọi chức năng chính |
| `AVLTree.h / AVLTree.cpp` | Cấu trúc cây AVL cho môn học |
| `Diem.h / Diem.cpp` | Xử lý điểm sinh viên |
| `MonHoc.h / MonHoc.cpp` | Xử lý danh sách môn học |
| `SinhVien.h / SinhVien.cpp` | Xử lý danh sách sinh viên |
| `LopSV.h / LopSV.cpp` | Xử lý lớp sinh viên |
| `LopTinChi.h / LopTinChi.cpp` | Xử lý lớp tín chỉ và đăng ký môn học |
| `Makefile` | Tự động build project bằng Dev-C++ |
| `MonHoc.txt` | File lưu dữ liệu môn học |
| `LopSV.txt` | File lưu dữ liệu lớp sinh viên và sinh viên |
| `LopTinChi.txt` | File lưu dữ liệu lớp tín chỉ và đăng ký |

---

## 5. Hướng dẫn sử dụng

- Build project bằng Dev-C++ hoặc sử dụng `Makefile`.
- Khi chạy chương trình:
  - Tự động **load** dữ liệu từ file nếu có.
- Khi thoát chương trình:
  - Tự động **save** toàn bộ dữ liệu ra file.

---

# 📢 Ghi chú
- Dự án tuân thủ yêu cầu đề bài:
  - Không sử dụng thư viện có sẵn như `vector`, `list`, `map`.
  - Dùng cây AVL, danh sách liên kết, mảng động đúng yêu cầu.
  - Lưu và nạp dữ liệu qua file text.

---

# ✅ Hoàn thành 100%
