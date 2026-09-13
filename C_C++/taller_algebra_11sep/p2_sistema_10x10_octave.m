% Laura Vanessa Gomez Fonseca y Sergio Andrés Marin Patiño

1;   % <-- marca el archivo como SCRIPT (habilita funciones locales)

% ---- Funcion: Gauss con pivoteo parcial + sustitucion hacia atras ----
function x = gauss_pp (A, b)
  n = rows(A);
  M = [A b];
  for k = 1:n-1
    [~, p] = max(abs(M(k:n,k)));  p = p + k - 1;   % pivoteo parcial
    M([k p],:) = M([p k],:);
    for i = k+1:n
      f = M(i,k)/M(k,k);
      M(i,k:end) = M(i,k:end) - f*M(k,k:end);
    endfor
  endfor
  x = zeros(n,1);
  for i = n:-1:1
    x(i) = (M(i,end) - M(i,i+1:n)*x(i+1:n)) / M(i,i);
  endfor
endfunction

% ---- Cuerpo principal ----
A = [2 1 0 3 2 1 0 2 1 4;
     1 3 2 0 1 4 2 1 0 2;
     0 2 4 1 3 0 1 2 4 1;
     3 0 1 5 2 1 3 0 2 1;
     2 1 3 2 6 2 1 4 0 3;
     1 4 0 1 2 5 2 1 3 0;
     0 2 1 3 1 2 4 0 2 1;
     2 1 2 0 4 1 0 5 3 2;
     1 0 4 2 0 3 2 3 6 1;
     4 2 1 1 3 0 1 2 1 5];
b = (1:10)';

xg = gauss_pp(A,b);

[L,U,P] = lu(A); 
y = L\(P*b); 
xlu = U\y;
[Q,R] = qr(A); 
xqr = R\(Q'*b);

printf("cond(A) = %.4f    det(A) = %.1f\n", cond(A), det(A));
printf("||xG - xLU|| = %.3e\n", norm(xg-xlu));
printf("||xG - xQR|| = %.3e\n", norm(xg-xqr));
printf("residual  Gauss=%.3e  LU=%.3e  QR=%.3e\n", ...
       norm(A*xg-b), norm(A*xlu-b), norm(A*xqr-b));

tic; for r=1:2000, gauss_pp(A,b); end;              tg=toc;
tic; for r=1:2000, [L,U,P]=lu(A); U\(L\(P*b)); end; tl=toc;
tic; for r=1:2000, [Q,R]=qr(A); R\(Q'*b); end;      tq=toc;
printf("tiempo x2000 (s): Gauss=%.4f  LU=%.4f  QR=%.4f\n", tg, tl, tq);

disp("Solucion x ="); disp(xg);
