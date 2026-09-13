% Laura Vanessa Gomez Fonseca y Sergio Andrés Marín Patiño


% Problema 1 - Inversa generalizada de Moore-Penrose (Octave)
A = [1  0  2;
     2 -1  5;
     0  1 -1;
     1  3 -1];

Ap = pinv(A);

printf("rank(A) = %d  (A es 4x3, RANGO DEFICIENTE: r=2 < 3)\n", rank(A));
disp("A- (Moore-Penrose) ="); disp(Ap);

p1 = norm(A*Ap*A - A,     'fro');
p2 = norm(Ap*A*Ap - Ap,   'fro');
p3 = norm(A*Ap - (A*Ap)', 'fro');
p4 = norm(Ap*A - (Ap*A)', 'fro');

printf("\n--- Comprobacion (todas ~0 => se cumplen) ---\n");
printf("P1  ||A*A-*A - A||     = %.3e\n", p1);
printf("P2  ||A-*A*A- - A-||   = %.3e\n", p2);
printf("P3  ||A*A- - (A*A-)'|| = %.3e\n", p3);
printf("P4  ||A-*A - (A-*A)'|| = %.3e\n", p4);
