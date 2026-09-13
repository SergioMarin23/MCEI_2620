
// Laura Vanessa Gomez Fonseca y Sergio Andrés Marín Patiño

// Problema 4 - Inversa por directo, QR y SVD (C++/Eigen3). Matriz 10x10 original.
#include <iostream>
#include <eigen3/Eigen/Dense>

using namespace Eigen; using namespace std;

int main(){
    MatrixXd A(10,10);
    A << 2,1,0,3,2,1,0,2,1,4,  1,3,2,0,1,4,2,1,0,2,
         0,2,4,1,3,0,1,2,4,1,  3,0,1,5,2,1,3,0,2,1,
         2,1,3,2,6,2,1,4,0,3,  1,4,0,1,2,5,2,1,3,0,
         0,2,1,3,1,2,4,0,2,1,  2,1,2,0,4,1,0,5,3,2,
         1,0,4,2,0,3,2,3,6,1,  4,2,1,1,3,0,1,2,1,5;

    int n=10; 
    MatrixXd Id=MatrixXd::Identity(n,n);
    MatrixXd Ai_dir = A.inverse();                       // directo
    MatrixXd Ai_qr  = A.householderQr().solve(Id);       // via QR
    JacobiSVD<MatrixXd> svd(A, ComputeThinU|ComputeThinV);
    MatrixXd Ai_svd = svd.solve(Id);                     // via SVD
    cout.precision(3); cout<<scientific;
    cout<<"||inv - QR||  = "<<(Ai_dir-Ai_qr).norm()<<"\n";
    cout<<"||inv - SVD|| = "<<(Ai_dir-Ai_svd).norm()<<"\n";
    cout<<"residual ||A*Ainv-I||:  dir="<<(A*Ai_dir-Id).norm()
        <<"  qr="<<(A*Ai_qr-Id).norm()
        <<"  svd="<<(A*Ai_svd-Id).norm()<<"\n";
    return 0;
}
