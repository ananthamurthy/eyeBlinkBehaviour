%Please work with the data from all sessions of an animal, before proceeding to the next animal

clear all
close all

saveDirec = getenv("HOME") + 'Desktop/Work/Behaviour';

listPath=('C:\Users\vinay\Desktop\upiLabrotation\TrialDataSave\folder_list.txt'); %Check path ID
fid=fopen(listPath);

%Protocol Information
totalTrials = 100;
preTime = 5000; %in ms
csTime = 350; %in ms
traceTime = 250; %in ms
puffTime = 100; %in ms
postTime = 5000; %in ms

%Additional Parameters
samplingRate = 100;
nyquistsamplingRate = samplingRate/2;
filterOrder = 4;
offset = 0.6; % in the range of 0.0 - 1.0
gain = 4;

phaseOffsetFactor = 2; %in samples
csPlus = [];
csMinus = [];

%Operations (0 = Don't Perform, 1 = Perform)
getGeneralInformation = 1;
doBaselineCorrection = 1;
findSignificantBlinks = 1;
plotFigures = 0;
saveData = 1;

%Preallocation for speed
csType = nan(totalTrials, 1);

while 1
    tline = fgetl(fid);
    if ~ ischar(tline), break, end
    
    direc = [tline '\'];
    
    if getGeneralInformation == 1
        %General Information:
        slashi=strfind(direc, '\');
        dataset=direc(1, (slashi(1, (length(slashi)-1))+1:((length(direc)-1)))); % Dataset name, in the format of MouseNN_BlockXX_sessionY
        uscorei=strfind(dataset, '_');
        mouse=dataset(1:uscorei(1,1)-1);
        sessionType = dataset((uscorei(1,2)-1):uscorei(1,2)-1); %How does this work?:P
        sessionType_description = {'Control'; 'Trace'; 'Delay'};
        session = dataset((uscorei(1,2)+8):end);
        %disp(['Animal: ', mouse, ' SessionType: ', sessionType_description(sessionType), ' Session: ', num2str(session)])
    end
    
    %PROBLEM: Different trials have unequal number of data points (not MATLAB friendly)
    %SOLUTION: First pass to preallocate
    for trialNum = 1:totalTrials
        filename = [direc, 'Trial', num2str(trialNum), '.csv'];
        rawData_size(trialNum) = size(csvread(filename, 3),1);
    end
    rawBlinkData = zeros(totalTrials, min(rawData_size)); %to store non-baseline corrected data
    blinkData = zeros(totalTrials, min(rawData_size)); %to store baseline corrected data (Percent df/F)
    std_blinkData = zeros(totalTrials, min(rawData_size)); %to store std dev
    blinkBaseline = zeros(totalTrials,1); %to store baselines for every trial
    smooth_blinkData = zeros(totalTrials, min(rawData_size)); %to store sliding window average smoothened data
    blinks = zeros(totalTrials, min(rawData_size)); %to store blink rastors
    %Seperate out the CS+ and CS- trials
    %Preallocation
    %raw data
    %     blinkData_csPlus = zeros(length(find(csType == 1)), size(blinkData,2));
    %     blinkData_csMinus = zeros(length(find(csType == 0)), size(blinkData,2));
    %     %filtered data
    %     blinkData_csPlus_filtered = zeros(length(find(csType == 1)), size(blinkData,2));
    %     blinkData_csMinus_filtered = zeros(length(find(csType == 0)), size(blinkData,2));
    clear i
    blinkData_csPlus = [];
    blinkData_csMinus = [];
    blinkData_csPlus_filtered = [];
    blinkData_csMinus_filtered = [];
    
    for trialNum = 1:totalTrials
        filename = [direc, 'Trial', num2str(trialNum), '.csv'];
        runningTrial = csvread(filename, 2, 0, [ 2 0 2 0] ); %reads only row 3, column 1
        %Check to see if "i" and the currently read runningTrial match
        if runningTrial ~= trialNum
            disp('Please check the trial number in the file Trial', trialNum)
            %continue
        else
            csType(trialNum)= csvread(filename, 2, 1, [ 2 1 2 1] ); %reads only row 3, column 2
            rawData = csvread(filename, 3);  %skips till row 3; has timestamps as well
            rawBlinkData(trialNum,1:min(rawData_size))= rawData(1:min(rawData_size), 1); %has only blinkValues
        end
        
        if doBaselineCorrection == 1
            blinkBaseline(trialNum) = prctile(rawBlinkData(trialNum,:), 10, 2); %10th percentile
            for sample = 1: size(rawBlinkData,2)
                blinkData(trialNum, sample) = ((rawBlinkData(trialNum,sample)/blinkBaseline(trialNum,1))-1)*100; %baseline corrected
            end
        end
        clear sample
        
        %add stuff to be done in the trials loop
        % ----- The following section of code filers the data
        close all
        myData = blinkData(trialNum,:);
        %Butterworth
        %low pass
        lowWn =10/nyquistsamplingRate;
        [b,a]=butter(filterOrder, lowWn, 'low'); %weirdly sets up a bandstop.. NOTE: we have adjusted this in Wn
        y=filtfilt(b,a,myData);
        %high pass
        highWn =1/nyquistsamplingRate;
        [b,a]=butter(filterOrder, highWn, 'high'); %weirdly sets up a bandstop.. NOTE: we have adjusted this in Wn
        C=filtfilt(b,a,y);
        
        % figure(1);
        % plot(y(1:(end-30)),'b')
        % hold on
        % plot(myData(1:end-30),'r');
        
        dtMAX = 49; %for 50 bins
        dtMIN = 10;
        vecLength = length(myData);
        
        B = zeros((dtMAX-dtMIN+1),(vecLength-2*(dtMAX+1))); %pre-allocating for speed; corr coeffs
        
        A = zeros((dtMAX+1),vecLength-dtMAX); %pre-allocating for speed
        A2 = zeros((dtMAX+1),vecLength-dtMAX); %pre-allocating for speed
        A3 = zeros(size(A2));
        
        %1. Get all windows of 50 bins
        for sample = 1:(vecLength-dtMAX)
            A(:,sample)= myData(1,(sample:sample+dtMAX));
            %2. subtract mean and weight
            %A2(:,i) = (A(:,i)-mean(A(:,i))).*hann(dtMAX+1);
            A2(:,sample) = A(:,sample).*hann(dtMAX+1);
        end
        clear sample
        
        %FORWARD DIRECTION
        %3. Corr coeff between signal and window shifted by dt
        for sample = 1:(vecLength-(2*dtMAX)-1)
            for dt = (dtMIN:dtMAX)
                B((dt-dtMIN+1),sample) = (A2(:,sample))'*(A2(:,sample+dt))/(norm(A2(:,sample),2)*norm(A2(:,sample+dt),2));
                %A3(:,i) = A2(:,i)*(norm(A2(:,i),2))/norm(A2(:,i+ii),2);
            end
        end
        clear sample
        clear dt
        
        %4. Find the max corr coeff(s)
        [argvalue, argmax] = max(B,[],1);
        myRange_fwd = (((dtMAX+1)/2)):(size(B,2)+((dtMAX+1)/2)-1);
        
        %E = zeros(size(myRange_fwd)+dtMAX);
        E = zeros(size(myData));
        
        for sample = 1:length(myRange_fwd)
            E(((dtMAX+1)/2)+sample) = A2((dtMAX+1)/2,sample);
        end
        clear sample
        %E = A2(:,myRange);
        
        %modify the argvalue
        new_argvalue1 = zeros(size(myData));
        new_argvalue1(1,((dtMAX+1)/2):((dtMAX+1)/2)+size(argvalue,2)-1)= (gain/2)*(argvalue-offset);
        % new_argvalue1(new_argvalue1 < 0) = 0;
        % new_argvalue1(new_argvalue1 > 1) = 1;
        
        %BACKWARD DIRECTION
        %3. Corr coeff between signal and window shifted by dt
        for ii = (vecLength-dtMAX-1):-1:(dtMAX+1)
            for iii = (dtMIN:dtMAX)
                B((iii-dtMIN+1),ii-dtMAX) = (A2(:,ii-iii))'*(A2(:,ii))/(norm(A2(:,ii-iii),2)*norm(A2(:,ii),2));
                %A3(:,i) = A2(:,i-ii)*(norm(A2(:,i-ii),2))/norm(A2(:,i),2);
            end
        end
        clear ii
        clear iii
        
        %4. Maximize corr coeff
        [argvalue, argmax] = max(B,[],1);
        %myRange_bwd = (size(A2,2)-size(B,2)-((dtMAX+1)/2)+1:size(A2,2)-((dtMAX+1)/2));
        
        for sample = dtMAX:size(B,2)+dtMAX
            E(((dtMAX+1)/2)+sample) = A2((dtMAX+1)/2, sample);
        end
        clear sample
        %E = A2(:,myRange);
        
        %modify the argvalue
        new_argvalue2 = zeros(size(myData));
        new_argvalue2(end-((dtMAX+1)/2)-size(argvalue,2):(end-(dtMAX+1)/2)-1) = (gain/2)*(argvalue - offset);
        
        % new_argvalue2(new_argvalue2 < 0) = 0;
        % new_argvalue2(new_argvalue2 > 1) = 1;
        
        new_argvalue=new_argvalue2+new_argvalue1;
        new_argvalue(new_argvalue < 0) = 0;
        new_argvalue(new_argvalue >= 1) = 1;
        
        D = C - C.*(new_argvalue); %we use "2" to get smoother curves rather than sharp edges
        
        if plotFigures == 1
            %             figure(1); %CS Trial Type
            %             plot(csType, 'ro', 'MarkerSize', 10, 'MarkerFaceColor', 'r');
            %
            %             %         figure(2);
            %             %         imagesc(rawBlinkData);
            %             %         colormap(jet);
            %
            %             if doBaselineCorrection == 1
            %                 figure(3);
            %                 imagesc(blinkData);
            %                 colormap(jet);
            %             end
            figure(1)
            %     plot(E,'blue')
            %     hold on
            plot(C,'magenta')
            %     hold on
            %     plot(argvalue*100,'cyan')
            hold on
            plot(D,'green')
            
            %figure(2)
            %plot(argmax)
            %imagesc(A2)
            
            %figure(3)
            %imagesc(B)
        end
        blinkData_butterFiltered(trialNum,1:size(C,2))= C;
        blinkData_filtered(trialNum,(1:size(D,2))) = D;
        
        %Slicing
        if csType(trialNum) == 1
            blinkData_csPlus = [blinkData_csPlus; blinkData(trialNum,:)];
            blinkData_csPlus_filtered = [blinkData_csPlus_filtered; blinkData_filtered(trialNum,:)];
        elseif csType(trialNum) == 0
            blinkData_csMinus = [blinkData_csMinus; blinkData(trialNum,:)];
            blinkData_csMinus_filtered = [blinkData_csMinus_filtered; blinkData_filtered(trialNum,:)];
        end
    end
    clear i
    
    %Calculate the performance per trial separately for CS+ and CS-
    samplingInterval = 1000/samplingRate; %in ms
    csNtraceSamples = floor(((csTime+traceTime)/samplingInterval)-2*phaseOffsetFactor); %in number of samples 
    preSamples = floor((preTime/samplingInterval)-2*phaseOffsetFactor); %in number of sammples
    
    num_preBins = floor(preSamples/csNtraceSamples) ; %number of bins
    continuous_blinkBinThreshold = num_preBins/2;
    %Find Blinks
    %CS+
    for trial = 1:size(blinkData_csPlus_filtered,1)
        blinkData_csPlus_filtered_std(trial)= std(blinkData_csPlus_filtered(trial,:));
        for sample = 1:size(blinkData_csPlus_filtered,2)
            if blinkData_csPlus_filtered(trial, sample)>= 2*blinkData_csPlus_filtered_std(trial)
                blink_csPlus(trial,sample) = 1;
            else
                blink_csPlus(trial,sample) = 0;
            end 
        end
    end
    clear trial
    clear sample
    
    %CS-
    for trial = 1:size(blinkData_csMinus_filtered,1)
        blinkData_csMinus_filtered_std(trial) = std(blinkData_csMinus_filtered(trial,:));
        for sample = 1:size(blinkData_csMinus_filtered,2)
            if blinkData_csMinus_filtered(trial,sample)>=2*blinkData_csMinus_filtered_std(trial)
                blink_csMinus(trial,sample)= 1;
            else
                blink_csMinus(trial,sample)= 0;
            end
        end
    end
    clear trial
    clear sample
    
    %Scoring
    %Get Session Performance for CS+
    %Score PRE Phase
        blink_csPlus_PRE = blink_csPlus(:,((phaseOffsetFactor):(preSamples-(phaseOffsetFactor))));
        Y=blink_csPlus_PRE(:,end-(num_preBins*csNtraceSamples)+1:end);
        X=reshape(Y,size(blink_csPlus,1),csNtraceSamples,num_preBins);%1st dimension = trials; 2nd dimension = samples in bin; 3rd dimension = bin index
        blink_PRE = squeeze(sum(sum(X,2)>0,3));
        %clipping
        blink_PRE(blink_PRE > continuous_blinkBinThreshold)= continuous_blinkBinThreshold;
    %Score CS phase
        blink_csPlus_CS = blink_csPlus(:,((preSamples+phaseOffsetFactor+1):(preSamples+phaseOffsetFactor+csNtraceSamples)));
        blink_CS = (sum(blink_csPlus_CS,2)>0);
    %Give Trial Score
        all_csPlusTrials_hitCS_score = (1 - (blink_PRE/4)).*blink_CS;%per CS+ trial
        all_csPlusTrials_misCS_score = (blink_PRE/4).*(1-blink_CS); %per CS+ trial
        all_csPlusTrials_score = mean(all_csPlusTrials_hitCS_score - all_csPlusTrials_misCS_score); % per CS+ session
    %Get Session Performance - for CS+
    %Score PRE Phase
        blink_csMinus_PRE = blink_csMinus(:,((phaseOffsetFactor):(preSamples-(phaseOffsetFactor))));
        Y=blink_csMinus_PRE(:,end-(num_preBins*csNtraceSamples)+1:end);
        X=reshape(Y,size(blink_csMinus,1),csNtraceSamples,num_preBins);%1st dimension = trials; 2nd dimension = samples in bin; 3rd dimension = bin index
        blink_PRE = squeeze(sum(sum(X,2)>0,3));
        %clipping
        blink_PRE(blink_PRE > continuous_blinkBinThreshold)= continuous_blinkBinThreshold;
    %Score CS phase
        blink_csMinus_CS = blink_csMinus(:,((preSamples+phaseOffsetFactor+1):(preSamples+phaseOffsetFactor+csNtraceSamples)));
        blink_CS = (sum(blink_csMinus_CS,2)>0);
    %Give Trial Score
        all_csMinusTrials_hitCS_score = (1 - (blink_PRE/4)).*blink_CS;%per CS- Trial
        all_csMinusTrials_misCS_score = (blink_PRE/4).*(1-blink_CS); %per CS- trial
        all_csMinusTrials_score = mean(all_csMinusTrials_hitCS_score - all_csMinusTrials_misCS_score); % per CS- session
    
    % --------
    if saveData == 1
        %filtered data
        csvwrite([saveDirec dataset '_butterFiltered.csv'], blinkData_butterFiltered);
        csvwrite([saveDirec dataset '_filtered.csv'], blinkData_filtered);
        csvwrite([saveDirec dataset '_csPlus_filtered.csv'], blinkData_csPlus_filtered);
        csvwrite([saveDirec dataset '_csMinus_filtered.csv'], blinkData_csMinus_filtered);
        %raw data
        csvwrite([saveDirec dataset '_csPlus.csv'], blinkData_csPlus);
        csvwrite([saveDirec dataset '_csMinus.csv'], blinkData_csMinus);
        
        csPlus = [csPlus all_csPlusTrials_score];
        csvwrite([saveDirec mouse '_csPlus.csv'], csPlus);
        csMinus = [csMinus all_csPlusTrials_score];
        csvwrite([saveDirec mouse '_csPlus.csv'], csMinus);
					   
        %as matlab files
        %filtered data
%         save([saveDirec dataset '_butterFiltered'], blinkData_butterFiltered);
%         save([saveDirec dataset '_filtered'], blinkData_filtered);
%         save([saveDirec dataset '_csPlus_filtered'], blinkData_csPlus_filtered);
%         save([saveDirec dataset '_csMinus_filtered'], blinkData_csMinus_filtered);
%         %raw data
%         save([saveDirec dataset '_csPlus'], blinkData_csPlus);
%         save([saveDirec dataset '_csMinus'], blinkData_csMinus);
    end
end
