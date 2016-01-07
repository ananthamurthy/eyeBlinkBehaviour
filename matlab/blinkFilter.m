% The following code filters blink data based on a bandpass Butterworth
% Author: Kambadur Ananthamurthy
% Created: 20151128

function [onlyButterworth, fullFiltered] = blinkFilter(myData, samplingRate, lowPassCutoffFreq, highPassCutoffFreq, filterOrder, offset, gain, phaseOffsetFactor, nbins)

nyquistsamplingRate = samplingRate/2;

%Butterworth
%low pass
lowWn =lowPassCutoffFreq/nyquistsamplingRate;
[b,a]=butter(filterOrder, lowWn, 'low'); %weirdly sets up a bandstop.. NOTE: we have adjusted this in Wn
y=filtfilt(b,a,myData);
%high pass
highWn =highPassCutoffFreq/nyquistsamplingRate;
[b,a]=butter(filterOrder, highWn, 'high'); %weirdly sets up a bandstop.. NOTE: we have adjusted this in Wn
onlyButterworth=filtfilt(b,a,y);

dtMAX = nbins-1;
dtMIN = nbins/5;
vecLength = length(myData);

B = zeros((dtMAX-dtMIN+1),(vecLength-2*(dtMAX+1))); %pre-allocating for speed; corr coeffs

A = zeros((dtMAX+1),vecLength-dtMAX); %pre-allocating for speed
A2 = zeros((dtMAX+1),vecLength-dtMAX); %pre-allocating for speed
A3 = zeros(size(A2));

%1. Get all windows of nbins, and subtract mean and weight
for sample = 1:(vecLength-dtMAX)
    A(:,sample)= myData(1,(sample:sample+dtMAX));
    
    % Subtract mean and weight
    %A2(:,i) = (A(:,i)-mean(A(:,i))).*hann(dtMAX+1);
    A2(:,sample) = A(:,sample).*hann(dtMAX+1);
end
clear sample

%FORWARD DIRECTION
%2a. Corr coeff between signal and window shifted by dt
for sample = 1:(vecLength-(2*dtMAX)-1)
    for dt = (dtMIN:dtMAX)
        B((dt-dtMIN+1), sample) = (A2(:,sample))'*(A2(:,sample+dt))/(norm(A2(:,sample),2)*norm(A2(:,sample+dt),2));
        %A3(:,i) = A2(:,i)*(norm(A2(:,i),2))/norm(A2(:,i+ii),2);
    end
end
clear sample
clear dt

%3a. Maximize corr coeff(s)
[argvalue, argmax] = max(B,[],1);
myRange_fwd = (((dtMAX+1)/2)):(size(B,2)+((dtMAX+1)/2)-1);

%E = zeros(size(myRange_fwd)+dtMAX);
E = zeros(size(myData));

for sample = 1:length(myRange_fwd)
    E(((dtMAX+1)/2)+sample) = A2((dtMAX+1)/2,sample);
end
clear sample

%4a. Modify the argvalue
new_argvalue1 = zeros(size(myData));
new_argvalue1(1,((dtMAX+1)/2):((dtMAX+1)/2)+size(argvalue,2)-1)= (gain/2)*(argvalue-offset);
% new_argvalue1(new_argvalue1 < 0) = 0;
% new_argvalue1(new_argvalue1 > 1) = 1;

%BACKWARD DIRECTION
%2b. Corr coeff between signal and window shifted by dt
for sample = (vecLength-dtMAX-1):-1:(dtMAX+1)
    for dt = (dtMIN:dtMAX)
        B((dt-dtMIN+1),sample-dtMAX) = (A2(:,sample-dt))'*(A2(:,sample))/(norm(A2(:,sample-dt),2)*norm(A2(:,sample),2));
        %A3(:,i) = A2(:,i-ii)*(norm(A2(:,i-ii),2))/norm(A2(:,i),2);
    end
end
clear sample
clear dt

%3b. Maximize corr coeff
[argvalue, argmax] = max(B,[],1);
%myRange_bwd = (size(A2,2)-size(B,2)-((dtMAX+1)/2)+1:size(A2,2)-((dtMAX+1)/2));

for sample = dtMAX:size(B,2)+dtMAX
    E(((dtMAX+1)/2)+sample) = A2((dtMAX+1)/2, sample);
end
clear sample

%E = A2(:,myRange);

%4b. modify the argvalue
new_argvalue2 = zeros(size(myData));
new_argvalue2(end-((dtMAX+1)/2)-size(argvalue,2):(end-(dtMAX+1)/2)-1) = (gain/2)*(argvalue - offset);
% new_argvalue2(new_argvalue2 < 0) = 0;
% new_argvalue2(new_argvalue2 > 1) = 1;
new_argvalue=new_argvalue2+new_argvalue1;
new_argvalue(new_argvalue < 0) = 0;
new_argvalue(new_argvalue >= 1) = 1;

fullFiltered = onlyButterworth - onlyButterworth.*(new_argvalue); %we use "2" to get smoother curves rather than sharp edges

end