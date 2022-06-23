function y = Apartenenta(x, val1, val2)
	% Functia care primeste ca parametrii x, val1, val2 si care calculeaza valoarea functiei membru in punctul x.
	% Stim ca 0 <= x <= 1

%pentru a fi continua limitele laterale trebuie sa fie egale
% => a*val1 + b = 0 && a*val2 + b = 1
%din aceste ecuatii reiese ca:
a = 1 / (val2 - val1);
b = -val1 * a;

if x < val1
    y = 0;
elseif x <= val2
    y = a*x + b;
else
    y = 1;
end

end

	