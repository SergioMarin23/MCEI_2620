
// Laura Vanessa Gomez Fonseca y Sergio Andrés Marin Patiño


// Problema 2 - Sistema 10x10 por Gauss, LU y QR (C++/Eigen3). b=[1..10]

#include <iostream>
#include <cmath>
#include <utility>
#include <eigen3/Eigen/Dense>

using namespace Eigen;
using namespace std;

VectorXd gauss_pp(MatrixXd A, VectorXd b) {
    int n = A.rows();
    for (int k = 0; k < n-1; ++k) {
        int p = k; double mx = fabs(A(k,k));
        for (int i = k+1; i < n; ++i)
            if (fabs(A(i,k)) > mx) { mx = fabs(A(i,k)); p = i; }
        A.row(k).swap(A.row(p)); std::swap(b(k), b(p));
        for (int i = k+1; i < n; ++i) {
            double f = A(i,k)/A(k,k);
            A.row(i) -= f*A.row(k);
            b(i)     -= f*b(k);
        }
    }
    VectorXd x(n);
    for (int i = n-1; i >= 0; --i) {
        double s = b(i);
        for (int j = i+1; j < n; ++j) s -= A(i,j)*x(j);
        x(i) = s/A(i,i);
    }
    return x;
}

int main() {
    MatrixXd A(10,10);
    A << 2,1,0,3,2,1,0,2,1,4,
         1,3,2,0,1,4,2,1,0,2,
         0,2,4,1,3,0,1,2,4,1,
         3,0,1,5,2,1,3,0,2,1,
         2,1,3,2,6,2,1,4,0,3,
         1,4,0,1,2,5,2,1,3,0,
         0,2,1,3,1,2,4,0,2,1,
         2,1,2,0,4,1,0,5,3,2,
         1,0,4,2,0,3,2,3,6,1,
         4,2,1,1,3,0,1,2,1,5;
    VectorXd b(10);
    for (int i = 0; i < 10; ++i) b(i) = i+1;
    VectorXd xg  = gauss_pp(A, b);
    VectorXd xlu = A.partialPivLu().solve(b);
    VectorXd xqr = A.householderQr().solve(b);
    cout.precision(4); cout << scientific;
    cout << "||xG - xLU|| = " << (xg-xlu).norm() << "\n";
    cout << "||xG - xQR|| = " << (xg-xqr).norm() << "\n";
    cout << "residual  Gauss=" << (A*xg-b).norm()
         << "  LU=" << (A*xlu-b).norm()
         << "  QR=" << (A*xqr-b).norm() << "\n";
    cout << fixed << "\nSolucion x =\n" << xg << "\n";
    return 0;
}
