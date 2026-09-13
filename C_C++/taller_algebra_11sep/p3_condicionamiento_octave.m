
% Sergio Andrés Marín Patiño y Laura Vanessa Gomez Fonseca


% Problema 3 - Condicionamiento y estabilidad (Octave)
% A original (con ceros) vs A' (18 ceros -> 0.0587). b=[1..10]
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
Ap = A; Ap(A==0) = 0.0587;        % perturbacion: ceros -> 0.0587

x  = A  \ b;                       % solucion original
xp = Ap \ b;                       % solucion perturbada

K = cond(A);
rel_x = norm(x-xp)/norm(x);
rel_A = norm(A-Ap,2)/norm(A,2);

printf("cond(A)  original   = %.4f\n", cond(A));
printf("cond(A') perturbada = %.4f\n", cond(Ap));
printf("ceros modificados   = %d\n", sum(A(:)==0));
printf("\n||dA||/||A|| = %.4e  (cambio en la matriz)\n", rel_A);
printf("||dx||/||x|| = %.4e  (cambio en la solucion)\n", rel_x);
printf("cota K*||dA||/||A|| = %.4e  (debe ser >= ||dx||/||x||)\n", K*rel_A);
printf("amplificacion real  = %.2f x\n", rel_x/rel_A);
if rel_x <= K*rel_A
  printf(">> Se cumple la cota. Sistema BIEN condicionado y estable.\n");
end
