
// Laura Vanessa Gomez Fonseca y Sergio Andrés Marin Patiño

// Problema 5 - Minimos cuadrados P=b0+b1*V+b2*I+b3*T (C++/Eigen3)
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <eigen3/Eigen/Dense>

using namespace Eigen;
using namespace std;

int main() {
    ifstream f("datos_convertidor_realista.csv");
    if (!f) { cerr << "No se encontro el CSV\n"; return 1; }
    string line; getline(f, line);
    vector<double> vV, vI, vT, vP;
    while (getline(f, line)) {
        if (line.empty()) continue;
        stringstream ss(line); string cell; double a[4]; int k = 0;
        while (getline(ss, cell, ',')) a[k++] = stod(cell);
        vV.push_back(a[0]); vI.push_back(a[1]); vT.push_back(a[2]); vP.push_back(a[3]);
    }
    int n = vV.size();
    MatrixXd X(n,4); VectorXd y(n);
    for (int r = 0; r < n; ++r) { X(r,0)=1; X(r,1)=vV[r]; X(r,2)=vI[r]; X(r,3)=vT[r]; y(r)=vP[r]; }
    VectorXd beta = X.colPivHouseholderQr().solve(y);
    cout << "beta = [b0 b1(V) b2(I) b3(T)] = " << beta.transpose() << "\n";
    VectorXd res = y - X*beta;
    double SSE = res.squaredNorm(), MSE = SSE/n, RMSE = sqrt(MSE);
    double SST = (y.array() - y.mean()).matrix().squaredNorm();
    cout << "SSE=" << SSE << "  MSE=" << MSE << "  RMSE=" << RMSE
         << "  R2=" << 1 - SSE/SST << "\n";
    JacobiSVD<MatrixXd> svd(X);
    auto sv = svd.singularValues();
    cout << "cond(X) = " << sv(0)/sv(sv.size()-1) << "\n";
    return 0;
}
