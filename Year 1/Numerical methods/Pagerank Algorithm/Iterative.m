function R = Iterative(nume, d, eps)
	% Functia care calculeaza matricea R folosind algoritmul iterativ.
	% Intrari:
	%	-> nume: numele fisierului din care se citeste;
	%	-> d: coeficentul d, adica probabilitatea ca un anumit navigator sa continue navigarea (0.85 in cele mai multe cazuri)
	%	-> eps: eruarea care apare in algoritm.
	% Iesiri:
	%	-> R: vectorul de PageRank-uri acordat pentru fiecare pagina.

%citesc
[K, n, Adj] = read(nume);


%Formula iterativa

%calculez M
M = (inv(K) * Adj)';

%R -> R(t+1); r -> R(t)

%initial
r = ones(n, 1);
r = r * (1 / n);
R = d * M * r + ((1 - d) / n) * ones(n, 1);
%pe parcurs pana cand eroarea este mai mica ca si eps
while norm(R - r) >= eps
    r = R;
    R = d * M * r + ((1 - d) / n) * ones(n, 1);
end
%la sfarsit
R = r;

end