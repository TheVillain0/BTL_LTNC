Cook Time
"Cook Time" là một trò chơi quản lý nhà bếp 2D được phát triển bằng C++ và SFML. Trong trò chơi này, người chơi sẽ vào vai một đầu bếp cần giao nguyên liệu cho các đầu bếp NPC khác để hoàn thành các món ăn.

![MMeatTomatoChef](https://github.com/user-attachments/assets/dbaff62b-3381-4acb-915c-61cc3df6bb15)


Tính năng
Mẫu đầu bếp được tạo ngẫu nhiên với yêu cầu nguyên liệu độc đáo.
Phát hiện va chạm và tương tác thời gian thực giữa người chơi và các đầu bếp NPC.
Cập nhật hình ảnh động theo nguyên liệu được giao bởi người chơi.
Điều khiển đơn giản và trực quan.
Cài đặt
Tải về kho mã:
Tải về mã nguồn của trò chơi từ kho chứa trên GitHub.

Cài đặt SFML:
Làm theo hướng dẫn trên trang web của SFML để tải về và cài đặt SFML cho nền tảng của bạn.

Biên dịch trò chơi:
Đảm bảo bạn có trình biên dịch C++ đã được cài đặt. Sử dụng các lệnh sau để biên dịch trò chơi:


Chạy trò chơi:
Sau khi biên dịch xong, chạy trò chơi bằng lệnh:


./CookTime
Cách chơi
Di chuyển: Sử dụng các phím mũi tên để di chuyển nhân vật của người chơi xung quanh nhà bếp.
Nhặt/Giao nguyên liệu: Đứng gần nguyên liệu hoặc đầu bếp NPC và nhấn phím cách để tương tác.
Cơ chế trò chơi
Đầu bếp NPC: Khi bắt đầu trò chơi, các đầu bếp NPC sẽ ngẫu nhiên chọn một trong sáu mẫu, mỗi mẫu yêu cầu hai nguyên liệu cụ thể.
Giao nguyên liệu: Khi người chơi giao đúng nguyên liệu cho một đầu bếp NPC, hình ảnh của đầu bếp sẽ được cập nhật để hiển thị tiến trình (giao nguyên liệu đầu tiên, sau đó là hoàn thành).
Chiến thắng trò chơi: Giao thành công các nguyên liệu cần thiết cho tất cả các đầu bếp NPC.
Phụ thuộc
SFML: Thư viện Đa phương tiện Đơn giản và Nhanh (SFML) được sử dụng để vẽ đồ họa, quản lý cửa sổ và xử lý đầu vào.
Giấy phép
Dự án này được cấp phép theo Giấy phép MIT. Xem tệp LICENSE để biết thêm chi tiết.
