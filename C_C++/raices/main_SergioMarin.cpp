#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <gsl/gsl_roots.h>
#include <gsl/gsl_errno.h>

/*
// f(x) = x^3 - 5x + 1
double f(double x, void *params) { (void)params; return x*x*x - 5.0*x + 1.0; }
double df(double x, void *params){ (void)params; return 3.0*x*x - 5.0; }
void  fdf(double x, void *params, double *y, double *dy){
    (void)params; *y = x*x*x - 5.0*x + 1.0; *dy = 3.0*x*x - 5.0;
}
*/

// f(x) = e^(-x) - x
//
double f(double x, void *params) { (void)params; return exp(-x) - x; }
double df(double x, void *params){ (void)params; return -exp(-x) - 1.0; }
void  fdf(double x, void *params, double *y, double *dy){
    (void)params; *y = exp(-x) - x; *dy = -exp(-x) - 1.0;
}
//


// --- Familia INTERVALO (biseccion, falsepos, brent) ---
int resolver_intervalo(const gsl_root_fsolver_type *T, double x_lo, double x_hi){

gsl_function F;
F.function = &f;
F.params = nullptr;
gsl_root_fsolver *s = gsl_root_fsolver_alloc(T);
gsl_root_fsolver_set(s, &F, x_lo, x_hi);

std::cout << "iter\tinf\t\tsup\t\traiz\n";
int status, iter = 0, max_iter = 100; double r = 0.0;
do {
    iter++;
    status = gsl_root_fsolver_iterate(s);
    r    = gsl_root_fsolver_root(s);
    x_lo = gsl_root_fsolver_x_lower(s);
    x_hi = gsl_root_fsolver_x_upper(s);
    std::cout << iter << "\t" << x_lo << "\t" << x_hi << "\t" << r << "\n";
    status = gsl_root_test_interval(x_lo, x_hi, 0.0, 1e-8);
} while (status == GSL_CONTINUE && iter < max_iter);

std::cout << "\nRaiz = " << r << " | iter = " << iter
          << " | f(raiz) = " << f(r,nullptr) << std::endl;
gsl_root_fsolver_free(s);
return iter;

}

// --- Familia DERIVADA (newton, secante, steffenson) ---
int resolver_derivada(const gsl_root_fdfsolver_type *T, double x0){
gsl_function_fdf FDF;
FDF.f=&f;
FDF.df=&df;
FDF.fdf=&fdf;
FDF.params=nullptr;
gsl_root_fdfsolver *s = gsl_root_fdfsolver_alloc(T);
gsl_root_fdfsolver_set(s, &FDF, x0);

std::cout << "iter\tx\n";
int status, iter = 0, max_iter = 100; double x = x0, x_prev;

do {
    iter++;
    status = gsl_root_fdfsolver_iterate(s);
    x_prev = x;
    x = gsl_root_fdfsolver_root(s);
    std::cout << iter << "\t" << x << "\n";
    status = gsl_root_test_delta(x, x_prev, 0.0, 1e-8);
} while (status == GSL_CONTINUE && iter < max_iter);

std::cout << "\nRaiz = " << x << " | iter = " << iter
          << " | f(raiz) = " << f(x,nullptr) << std::endl;
gsl_root_fdfsolver_free(s);
return iter;

}

int main(int argc, char **argv){

std::cout << std::setprecision(10) << std::fixed;
const char *m = (argc > 1) ? argv[1] : "biseccion";

double x_lo = 0.0, x_hi = 1.0, x0 = 0.5;

if      (!std::strcmp(m,"biseccion"))  resolver_intervalo(gsl_root_fsolver_bisection, x_lo, x_hi);
else if (!std::strcmp(m,"falsepos"))   resolver_intervalo(gsl_root_fsolver_falsepos,  x_lo, x_hi);
else if (!std::strcmp(m,"brent"))      resolver_intervalo(gsl_root_fsolver_brent,     x_lo, x_hi);
else if (!std::strcmp(m,"newton"))     resolver_derivada(gsl_root_fdfsolver_newton,     x0);
else if (!std::strcmp(m,"secante"))    resolver_derivada(gsl_root_fdfsolver_secant,     x0);
else if (!std::strcmp(m,"steffenson")) resolver_derivada(gsl_root_fdfsolver_steffenson, x0);
else { std::cerr << "Metodo desconocido: " << m << std::endl; return 1; }
return 0;

}
