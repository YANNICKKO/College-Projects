%functia din laborator
function X = SST(A, b)

n = length(A);
X = zeros(n, 1);

for i = n: -1: 1
    s = 0;
    for j = i+1: n
        s = s + A(i, j) * X(j,1);
    end
    X(i,1) = (b(i,1) - s) / A(i,i);
end

end