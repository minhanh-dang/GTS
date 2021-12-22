#include <iostream>
#include<iomanip>
using namespace std;

class matrix
{
    double** p;
    int m, n;
public:

    matrix(int row, int col)
    {
        m = row;
        n = col;
        p = new double* [m];
        for (int i = 0; i < m; i++)
            p[i] = new double[n];
    }
    ~matrix()
    {
        for (int i = 0; i < m; i++)
            delete p[i];
        delete p;
    }
    void accept()
    {
        
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                
                cin >> p[i][j];  
            }
        }
    }

    void display()
    {
       
        for (int i = 0; i < m; i++)
        {
            cout << endl;
            for (int j = 0; j < n; j++)
            {
                cout  << setw(15)<< p[i][j] << "        ";
            }
        }
    }
    friend matrix chuyenvi(matrix);

    friend matrix operator + (matrix, matrix);
    friend matrix operator * (matrix, matrix);
    friend matrix vienquanh(matrix);
    friend matrix nghichdao2(matrix);
};
matrix nghichdao2(matrix a) {
    matrix T(a.m, a.n);
    if (a.m == 2)
        if (a.p[0][0] * a.p[1][1] - a.p[0][1] * a.p[1][0] == 0)
            cout << "\nMatran khong kha nghich";

        else {
            T.p[0][0] = a.p[1][1] / (a.p[0][0] * a.p[1][1] - a.p[0][1] * a.p[1][0]);
            T.p[0][1] = -a.p[0][1] / (a.p[0][0] * a.p[1][1] - a.p[0][1] * a.p[1][0]);
            T.p[1][0] = -a.p[1][0] / (a.p[0][0] * a.p[1][1] - a.p[0][1] * a.p[1][0]);
            T.p[1][1] = a.p[0][0] / (a.p[0][0] * a.p[1][1] - a.p[0][1] * a.p[1][0]);
        }
    return T;

}
matrix  chuyenvi(matrix a) {
    matrix T(a.n, a.m);
    for (int i = 0; i < a.n; i++) {
        for (int j = 0; j < a.m; j++) {
            T.p[i][j] = a.p[j][i];
        }
    }
    return T;
}


matrix operator* (matrix a, matrix b)
{
    matrix T(a.m, b.n);
    if (a.n == b.m)
    {

        for (int i = 0; i < a.m; i++)
        {
            for (int k = 0; k < b.n; k++)
            {
                T.p[i][k] = 0;
                for (int j = 0; j < a.n; j++)
                {
                    T.p[i][k] += a.p[i][j] * b.p[j][k];
                }
            }
        }

    }
    return T;
}
matrix operator +(matrix a, matrix b) {
    matrix T = a;
    for (size_t i = 0; i < a.m; i++)
    {
        for (size_t j = 0; j < a.n; j++)
        {
            T.p[i][j] = a.p[i][j] + b.p[i][j];
        }
    }
    return T;
}


    matrix vienquanh(matrix a) {
        if (a.n == 2) {// truong hop chan de quy
            a = nghichdao2(a);
        }
        else {
            cout<<"\n\n";
            // khoi tao cac ma tran con 
            matrix a_11(a.n - 1, a.n - 1);
            matrix a_111(a.n - 1, a.n - 1);
            matrix a_12(a.n - 1, 1);
            matrix a_21(1, a.n - 1);
            double   a_22 = a.p[a.n - 1][a.n - 1];
            for (size_t i = 0; i < a.n - 1; i++)
            {
                for (size_t j = 0; j < a.n - 1; j++)
                {
                    a_11.p[i][j] = a.p[i][j];
                }
            }
    
            for (size_t i = 0; i < a.n - 1; i++)
            {
                a_12.p[i][0] = a.p[i][a.n - 1];
                a_21.p[0][i] = a.p[a.n - 1][i];
            }
           
            if (a.n > 2) // neu chua gap truong hop chan
                a_111 = vienquanh(a_11); 
            matrix X = (a_111 * a_12);  
            matrix Y = (a_21 * a_111);    
            matrix chuyen = (Y * a_12);
            double theta = a_22 - chuyen.p[0][0]; ;
            if (theta == 0) { cout << "\n\n\nMa tran khong kha nghich"; }
            matrix x = (X * Y); 
            for (size_t i = 0; i < a.n - 1; i++)
            {
                for (size_t j = 0; j < a.n - 1; j++)
                {
                    a.p[i][j] = a_111.p[i][j] + x.p[i][j] / theta;
                    a.p[a.n - 1][i] = Y.p[0][i] / (-theta);
                    a.p[i][a.n - 1] = -X.p[i][0] / theta;
                    a.p[a.n - 1][a.n - 1] = 1 / theta;

                }
            }
        }
        return a;

    }

void IoFile(bool ok){
    if (ok) {
         freopen("C:\\Users\\HP\\OneDrive\\Desktop\\cpp.vsc123\\input.inp","r",stdin);
        freopen("C:\\Users\\HP\\OneDrive\\Desktop\\cpp.vsc123\\output1.out","w",stdout);
    }
}


int main()
{
    cout<<"\nChuong trinh da duoc thuc hien";
    IoFile(true);
    matrix a(4, 4);
    a.accept();
    cout << "\n";
    cout<<"\n  ma tran da nhap";
    a.display();
    cout << "\n\n";
    matrix b = chuyenvi(a); 
    
    matrix t = (b * a); 
    cout << "\n";
    
    matrix s = vienquanh(t);
    
    cout << "\n\n\n  matran nghich dao ";
    matrix inv = (s * b);
    cout << "\n";
    inv.display();
    cout<<"\n\n\n\n\n\n";
    
    return 0;
}