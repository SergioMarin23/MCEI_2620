// Problema 1 - Inversa de Moore-Penrose (C++/Eigen3)

// Laura Vanessa Gomez Fonseca y Sergio Andrés Marín Patiño


#include <iostream>
#include <eigen3/Eigen/Dense>
using namespace Eigen;
int main() {
    MatrixXd A(4,3);
    A << 1,  0,  2,
         2, -1,  5,
         0,  1, -1,
         1,  3, -1;
    MatrixXd Ap = A.completeOrthogonalDecomposition().pseudoInverse();
    std::cout << "rank(A) = " << A.colPivHouseholderQr().rank()
              << "  (RANGO DEFICIENTE: r=2 < 3)\n";
    std::cout << "A- (Moore-Penrose) =\n" << Ap << "\n\n";
    double p1 = (A*Ap*A - A).norm();
    double p2 = (Ap*A*Ap - Ap).norm();
    double p3 = (A*Ap - (A*Ap).transpose()).norm();
    double p4 = (Ap*A - (Ap*A).transpose()).norm();
    std::cout << "P1 = " << p1 << "\nP2 = " << p2
              << "\nP3 = " << p3 << "\nP4 = " << p4 << "\n";
    return 0;
}
