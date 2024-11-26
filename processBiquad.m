function [y, w] = processBiquad(x, filt, ch)

    N = length(x);  % Number of input samples
    y = zeros(N, 1); % Output vector of zeroes
    % w = zeros(N, 1); % Intermediate vector of zeroes

    % Filter coefficients

    a0 = filt.a0;
    a1 = filt.a1;
    a2 = filt.a2;
    b0 = filt.b0;
    b1 = filt.b1;
    b2 = filt.b2;

    % Get initial state   
    w1 = filt.w(1, ch);
    w2 = filt.w(2, ch);

    % Difference equations
    for n = 1:N % Loop through each sample in x
        wn = x(n) - (b1/b0) * w1 - (b2/b0) * w2;
        y(n) = (a0/b0) * wn + (a1/b0) * w1 + (a2/b0) * w2;

        w2 = w1; % w[n-2] = w[n-1]
        w1 = wn; % w[n-1] = w[n]
    end

    % filt.w(:, ch) = [w1; w2];
    w = [w1; w2];

end


% function [y, w] = processBiquad(x, filt, ch)
% 
%    [y,w] = filter([filt.a0, filt.a1, filt.a2], [filt.b0, filt.b1, filt.b2],x,filt.w(:,ch));
% 
% end