function [K, n, Adj, val1, val2] = read(nume)

input = fopen(nume, "rt");
n = fscanf(input, "%d", 1);

%matricea de adiacenta
Adj = zeros(n);
%matricea cu nr de pagini de pe fiecare linie
L = zeros(n, 1);

%citim de pe fiecare linie toate legaturile
for i = 1 : n
    lin = fscanf(input, "%d", 1);
    n_el = fscanf(input, "%d", 1);
    for j = 1 : n_el
        col = fscanf(input, "%d", 1);
        Adj(lin, col) = 1;
    end
    Adj(i, i) = 0;
    L(i) = sum(Adj(i, :));
end

%matricea cu diagonala L
K = diag(L);

%pentru apartenenta
val1 = fscanf(input, "%f", 1);
val2 = fscanf(input, "%f", 1);


fclose(input);
end