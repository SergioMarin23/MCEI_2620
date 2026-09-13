
// Sergio Andrés Marín Patiño y Laura Vanessa Gomez Fonseca

// Problema 3 - Condicionamiento y estabilidad (C++/Eigen3)
#include <iostream>
#include <eigen3/Eigen/Dense>
using namespace Eigen; using namespace std;
double spn(const MatrixXd& M){ JacobiSVD<MatrixXd> s(M); return s.singularValues()(0); }
double cond2(const MatrixXd& M){ JacobiSVD<MatrixXd> s(M);
  auto v=s.singularValues(); return v(0)/v(v.size()-1); }
int main(){
    MatrixXd A(10,10);
    A << 2,1,0,3,2,1,0,2,1,4,  1,3,2,0,1,4,2,1,0,2,
         0,2,4,1,3,0,1,2,4,1,  3,0,1,5,2,1,3,0,2,1,
         2,1,3,2,6,2,1,4,0,3,  1,4,0,1,2,5,2,1,3,0,
         0,2,1,3,1,2,4,0,2,1,  2,1,2,0,4,1,0,5,3,2,
         1,0,4,2,0,3,2,3,6,1,  4,2,1,1,3,0,1,2,1,5;
    VectorXd b(10); for(int i=0;i<10;i++) b(i)=i+1;
    MatrixXd Ap=A; int nz=0;
    for(int i=0;i<10;i++) for(int j=0;j<10;j++)
        if(A(i,j)==0){ Ap(i,j)=0.0587; nz++; }

    VectorXd x  = A.partialPivLu().solve(b);
    VectorXd xp = Ap.partialPivLu().solve(b);
    double K=cond2(A);
    double rel_x=(x-xp).norm()/x.norm();
    double rel_A=spn(A-Ap)/spn(A);

    cout.precision(4);
    cout<<"cond(A)  = "<<cond2(A)<<"\n";
    cout<<"cond(A') = "<<cond2(Ap)<<"\n";
    cout<<"ceros modificados = "<<nz<<"\n"<<scientific;
    cout<<"||dA||/||A|| = "<<rel_A<<"\n";
    cout<<"||dx||/||x|| = "<<rel_x<<"\n";
    cout<<"cota K*||dA||/||A|| = "<<K*rel_A<<"\n"<<fixed;
    cout<<"amplificacion real = "<<rel_x/rel_A<<" x\n";
    return 0;
}
