function R = Algebraic(nume, d)
	% Functia care calculeaza vectorul PageRank folosind varianta algebrica de calcul.
	% Intrari: 
	%	-> nume: numele fisierului in care se scrie;
	%	-> d: probabilitatea ca un anumit utilizator sa continue navigarea la o pagina urmatoare.
	% Iesiri:
	%	-> R: vectorul de PageRank-uri acordat pentru fiecare pagina.

%citesc
[K, n, Adj] = read(nume);

%Formula algoritmului algebraic
M = (PR_Inv(K) * Adj)';
R = PR_Inv(eye(n) - d * M) * (((1 - d)/ n) * ones(n, 1));

end