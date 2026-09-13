
% Laura Vanessa Gomez Fonseca y Sergio Andrés Marín Patiño

% Problema 5 - Minimos cuadrados P=b0+b1*V+b2*I+b3*T (Octave)
data = csvread("datos_convertidor_realista.csv", 1, 0);

V = data(:,1); I = data(:,2); T = data(:,3); P = data(:,4);
n = rows(data);
X = [ones(n,1) V I T]; y = P;

beta = X \ y;

printf("beta = [b0=%.4f  b1(V)=%.4f  b2(I)=%.4f  b3(T)=%.4f]\n", beta);
res = y - X*beta; SSE = res'*res; MSE = SSE/n; RMSE = sqrt(MSE);
R2 = 1 - SSE/sum((y-mean(y)).^2);

printf("SSE=%.3f  MSE=%.4f  RMSE=%.4f  R2=%.5f\n", SSE, MSE, RMSE, R2);
printf("cond(X)    = %.4e\n", cond(X));
printf("cond(X'*X) = %.4e   (~ cond(X)^2)\n", cond(X'*X));
sy = std(y,1);
printf("influencia estandarizada:  V=%.4f  I=%.4f  T=%.4f\n", ...
       beta(2)*std(V,1)/sy, beta(3)*std(I,1)/sy, beta(4)*std(T,1)/sy);
