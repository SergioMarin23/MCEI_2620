
% Laura Vaness Gomez Fonseca y Sergio Andrés Marín Patiño


% Problema 4 - Inversa por directo, QR y SVD (Octave). Matriz 10x10 original.
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

n = rows(A); 
Id = eye(n);

Ai_dir = inv(A);
                                 % directo
[Q,R]  = qr(A);  
Ai_qr  = R \ Q';                % A^-1 = R^-1 Q^T
[U,S,V]= svd(A); 
Ai_svd = V*diag(1./diag(S))*U'; % A^-1 = V S^-1 U^T

printf("cond(A) = %.4f\n", cond(A));
printf("||inv - QR||  = %.3e\n", norm(Ai_dir-Ai_qr));
printf("||inv - SVD|| = %.3e\n", norm(Ai_dir-Ai_svd));
printf("residual ||A*Ainv - I||:  dir=%.3e  qr=%.3e  svd=%.3e\n", ...
       norm(A*Ai_dir-Id), norm(A*Ai_qr-Id), norm(A*Ai_svd-Id));
disp("Inversa (metodo SVD):"); disp(Ai_svd);
