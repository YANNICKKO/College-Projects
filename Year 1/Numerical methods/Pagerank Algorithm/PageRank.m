function [R1 R2] = PageRank(nume, d, eps)
	% Calculeaza indicii PageRank pentru cele 3 cerinte
	% Scrie fisierul de iesire nume.out

%Initializam output-ul
output_name = strcat(nume,".out");
output = fopen(output_name, "w");

%Ne trebuie n si val1, val2 pentru apartenenta
[~, n, ~, val1, val2] = read(nume);
fprintf(output, "%d\n", n);


%Iterative
R1 = Iterative(nume, d, eps);
fprintf(output, "%.6f\n", R1);

%Algebraic
fprintf(output, "\n");
R2 = Algebraic(nume, d);
fprintf(output, "%.6f\n", R2);

%Apartenenta
fprintf(output, "\n");
[PR1, line] = sort(R2, "descend");
for i = 1: n
fprintf(output, "%d %d %f\n", i, line(i), Apartenenta(PR1(i), val1, val2));
end

fclose(output);
end