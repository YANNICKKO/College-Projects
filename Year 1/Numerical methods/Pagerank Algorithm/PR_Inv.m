function B = PR_Inv(A)
	% Functia care calculeaza inversa matricii A folosind factorizari Gram-Schmidt
	% Se va inlocui aceasta linie cu descrierea algoritmului de inversare
n = length(A);

%calculam Q si R
[Q, R] = Gram_Schmidt(A);

%calculam pentru fiecare coloana a lui B (pe care il si initializam)
%Q(i, :)' = Q'(:, i) (coloana i a lui Q transpus)
B = eye(n);

for i = 1: n
    B(:, i) = SST(R, Q(i, :)');
end

end