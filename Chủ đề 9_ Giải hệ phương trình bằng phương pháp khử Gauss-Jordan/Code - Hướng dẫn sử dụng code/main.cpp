

#include <iostream>
#include <Windows.h>
#include "menu.h"
using namespace std;

void IntroduceTeam();
 
int main() {
    IntroduceTeam();

    menuTotal();

    system("pause");
    return 0;
}

void IntroduceTeam() {
    string introduce = "Truong: Dai hoc Bach Khoa Ha Noi \
                        \nKhoa: Toan ung dung va Tin hoc \
                        \nNhom 7: Giai he phuong trinh bang phuong phap lap Seidel \
                        \n\tNguyen Bui Nam Truong - 20185418 \
                        \n\tNguyen Phu Nhat       - 20185390 \
                        \n\tNguyen Dac Cao        - 20185328 \
                        \n\tPham Huu Quoc Anh     - 20185322 \
                        \n\tDo Quang Hung         - 20185365 \
                        \n\tNguyen Viet Duc       - 20173500 \
                        \n_________________________________________________________\n";
    cout << introduce;

    cout << "Please wait 3 seconds to start . . ." << endl;
    Sleep(3000);
}
