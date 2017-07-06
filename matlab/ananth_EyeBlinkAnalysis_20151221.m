% AUTHOR - Kambadur Ananthamurthy
% PURPOSE - Read raw .csv files for eye blink behaviour data
% SPECIAL NOTE - This version of the code will work for data obtained till 20151221
% This code additionall requires getInfo.m and blinkFilter.m to work.

addpath('/Users/ananth/Documents/MATLAB/eyeBlinkBehaviourAnalysis_MATLAB')
addpath('/Users/ananth/Documents/MATLAB/CustomFunctions_MATLAB')

%Please work with the data from all sessions of an animal, before proceeding to the next animal

clear all
close all

saveDirec = ('/Users/ananth/Desktop/Work/Analysis/eyeBlinkBehaviourAnalysis/');

listPath=('/Users/ananth/Desktop/Work/Behaviour/folder_list.txt'); %Check path ID
fid=fopen(listPath);

%Protocol Information
preTime = 5000; %in ms
csTime = 350; %in ms
traceTime = 250; %in ms
puffTime = 100; %in ms
postTime = 5000; %in ms
nstages = 4; % The number of stages of the session

%Parameters for filter
samplingRate = 100;
lowFreq = 10; % in Hz
highFreq = 1; % in Hz
nbins = 50;
filterOrder = 4;
offset = 0.6; % in the range of 0.0 - 1.0
gain = 4;
phaseOffsetFactor = 2; %in samples

csPlus_scores = [];
csMinus_scores = [];

%Operations (0 = Don't Perform, 1 = Perform)
getGeneralInformation = 1;
doBaselineCorrection = 1;
findSignificantBlinks = 1;
plotFigures = 0;
saveData = 1;

while 1
    tline = fgetl(fid);
    if ~ ischar(tline), break, end
    
    direc = [tline '/'];
    
    if getGeneralInformation == 1
        %General Information:
        [mouse, sessionType, session] = getInfo(direc);
        sessionType_description = {'Control'; 'Trace'; 'Delay'};
        dataset = [mouse, '_SessionType', sessionType, '_Session' session];
        disp(dataset);
    end
    
    if str2num(sessionType) == 0
        traceTime = 250; %in ms
        totalTrials = 50;
    elseif str2num(sessionType) == 1
        traceTime = 250; %in ms
        totalTrials = 100;
    elseif str2num(sessionType) == 2
        traceTime = 0; %in ms
        totalTrials = 100;
    else
        disp('Cannot understand what SessionType');
    end
    
    %PROBLEM: Different trials have unequal number of data points (not MATLAB friendly)
    %SOLUTION: First pass to preallocate
    for trialNum = 1:totalTrials
        filename = [direc, 'Trial', num2str(trialNum), '.csv'];
        rawData_size(trialNum) = size(csvread(filename, 3, 0), 1);
    end
    
    blinkData = zeros(totalTrials, min(rawData_size)); %to store baseline corrected data (Percent df/F)
    blinkData_stdDev = zeros(totalTrials, min(rawData_size)); %to store std dev
    blinkData_baselines = zeros(totalTrials,1); %to store baselines for every trial
    blinkData_smooth = zeros(totalTrials, min(rawData_size)); %to store sliding window average smoothened data
    blinkRastors = zeros(totalTrials, min(rawData_size)); %to store blink rastors
    
    %We are next going to seperate out the CS+ and CS- trials
    blinkData_csPlus = [];
    blinkData_csMinus = [];
    blinkData_csPlus_fullFiltered = [];
    blinkData_csMinus_fullFiltered = [];
    
    %Preallocation for speed
    csType = nan(totalTrials, 1);
    
    for trialNum = 1:totalTrials
        filename = [direc, 'Trial', num2str(trialNum), '.csv'];
        runningTrial = csvread(filename, 2, 0, [ 2 0 2 0] ); %reads only row 3, column 1
        %Check to see if "i" and the currently read runningTrial match
        if runningTrial ~= trialNum
            disp('Please check the trial number in the file Trial', trialNum)
            %continue
        else
            csType(trialNum)= csvread(filename, 2, 1, [ 2 1 2 1] ); %reads only row 3, column 2
            rawData = csvread(filename, 3, 0);  %skips till row 3; has timestamps as well
            blinkData(trialNum,1:min(rawData_size))= rawData(1:min(rawData_size), 1); %has only blinkValues
        end
        
        if doBaselineCorrection == 1
            blinkData_baselines(trialNum) = prctile(blinkData(trialNum,:), 50, 2); %50th percentile - median
            for sample = 1: size(blinkData,2)
                blinkData(trialNum, sample) = ((blinkData(trialNum,sample)/blinkData_baselines(trialNum,1))-1)*100; %baseline corrected
            end
            clear sample
        end
        
        
        % Filtering
        myData = blinkData(trialNum,:);
        [onlyButterworth, fullFiltered] = blinkFilter(myData, samplingRate, lowFreq, highFreq, filterOrder, offset, gain, phaseOffsetFactor, nbins);
        
        close all
        if plotFigures == 1
            figure(1); %CS Trial Type
            plot(csType, 'ro', 'MarkerSize', 10, 'MarkerFaceColor', 'r');
            
            if doBaselineCorrection == 1
                figure(3);
                imagesc(blinkData);
                colormap(jet);
            end
            
            figure(2)
            plot(onlyButterworth,'magenta')
            %     hold on
            %     plot(argvalue*100,'cyan')
            hold on
            plot(fullFiltered,'green')
            
        end
        blinkData_butterFiltered(trialNum,1:size(onlyButterworth,2))= onlyButterworth;
        blinkData_fullFiltered(trialNum,(1:size(fullFiltered,2))) = fullFiltered;
        
        %Slicing
        if csType(trialNum) == 1
            blinkData_csPlus = [blinkData_csPlus; blinkData(trialNum,:)];
            blinkData_csPlus_fullFiltered = [blinkData_csPlus_fullFiltered; blinkData_fullFiltered(trialNum,:)];
        elseif csType(trialNum) == 0
            blinkData_csMinus = [blinkData_csMinus; blinkData(trialNum,:)];
            blinkData_csMinus_fullFiltered = [blinkData_csMinus_fullFiltered; blinkData_fullFiltered(trialNum,:)];
        end
    end
    clear i
    
    %Trial Average for every session
    blinkData_csPlus_fullFiltered_trialAvg = mean(blinkData_csPlus_fullFiltered, 1);
    blinkData_csMinus_fullFiltered_trialAvg = mean(blinkData_csMinus_fullFiltered, 1);
    
    %Calculate the performance per trial separately for CS+ and CS-
    samplingInterval = 1000/samplingRate; %in ms
    nSamples = floor(((csTime+traceTime)/samplingInterval)-2*phaseOffsetFactor); %in number of samples
    nSamples_pretone = floor((preTime/samplingInterval)-2*phaseOffsetFactor); %in number of sammples
    
    nBins_pretone = floor(nSamples_pretone/nSamples) ; %number of bins
    continuous_blinkBinThreshold = nBins_pretone/2;
    
    %Find Blinks
    if findSignificantBlinks == 1
        %CS+
        for trial = 1:size(blinkData_csPlus_fullFiltered,1)
            blinkData_csPlus_fullFiltered_std(trial)= std(blinkData_csPlus_fullFiltered(trial,:));
            for sample = 1:size(blinkData_csPlus_fullFiltered,2)
                if blinkData_csPlus_fullFiltered(trial, sample)>= 2*blinkData_csPlus_fullFiltered_std(trial)
                    blinks_csPlus_fullTrial(trial,sample) = 1;
                else
                    blinks_csPlus_fullTrial(trial,sample) = 0;
                end
            end
        end
        clear trial
        clear sample
        
        %CS-
        for trial = 1:size(blinkData_csMinus_fullFiltered,1)
            blinkData_csMinus_fullFiltered_std(trial) = std(blinkData_csMinus_fullFiltered(trial,:));
            for sample = 1:size(blinkData_csMinus_fullFiltered,2)
                if blinkData_csMinus_fullFiltered(trial,sample)>=2*blinkData_csMinus_fullFiltered_std(trial)
                    blinks_csMinus_fullTrial(trial,sample)= 1;
                else
                    blinks_csMinus_fullTrial(trial,sample)= 0;
                end
            end
        end
        clear trial
        clear sample
        
        %Scoring
        %Get Session Performance for CS+
        %Score PRE Phase
        blinks_csPlus_pretone = blinks_csPlus_fullTrial(:,((phaseOffsetFactor):(nSamples_pretone-(phaseOffsetFactor))));
        Y=blinks_csPlus_pretone(:, end-(nBins_pretone*nSamples)+1:end);
        X=reshape(Y, size(blinks_csPlus_fullTrial,1), nSamples, nBins_pretone); %1st dimension = trials; 2nd dimension = samples in bin; 3rd dimension = bin index
        nBlinks_csPlus_pretone = squeeze(sum(sum(X,2)>0,3));
        %clipping
        blinks_csPlus_pretone(blinks_csPlus_pretone > continuous_blinkBinThreshold) = continuous_blinkBinThreshold;
        %Score CS phase
        blinks_csPlus_cs = blinks_csPlus_fullTrial(:,((nSamples_pretone+phaseOffsetFactor+1):(nSamples_pretone+phaseOffsetFactor+nSamples)));
        nBlinks_csPlus = (sum(blinks_csPlus_cs,2)>0);
        %Get Trial Score
        csPlus_hitScore = (1 - (nBlinks_csPlus_pretone/4)).*nBlinks_csPlus; %per CS+ trial
        csPlus_missScore = (nBlinks_csPlus_pretone/4).*(1-nBlinks_csPlus); %per CS+ trial
        csPlus_fullScore = mean(csPlus_hitScore - csPlus_missScore); % per CS+ session
        
        %Get Session Performance - for CS-
        %Score PRE Phase
        blinks_csMinus_pretone = blinks_csMinus_fullTrial(:,((phaseOffsetFactor):(nSamples_pretone-(phaseOffsetFactor))));
        Y=blinks_csMinus_pretone(:, end-(nBins_pretone*nSamples)+1:end);
        X=reshape(Y,size(blinks_csMinus_fullTrial,1), nSamples, nBins_pretone);%1st dimension = trials; 2nd dimension = samples in bin; 3rd dimension = bin index
        nBlinks_csMinus_pretone = squeeze(sum(sum(X,2)>0,3)); %overrides previous definition
        %clipping
        blinks_csMinus_pretone(blinks_csMinus_pretone > continuous_blinkBinThreshold)= continuous_blinkBinThreshold;
        %Score CS phase
        blinks_csMinus_cs = blinks_csMinus_fullTrial(:,((nSamples_pretone+phaseOffsetFactor+1):(nSamples_pretone+phaseOffsetFactor+nSamples)));
        nBlinks_csMinus = (sum(blinks_csMinus_cs,2)>0);
        %Give Trial Score
        csMinus_hitScore = (1 - (nBlinks_csMinus_pretone/4)).*nBlinks_csMinus; %per CS- Trial
        csMinus_missScore = (nBlinks_csMinus_pretone/4).*(1-nBlinks_csMinus); %per CS- trial
        csMinus_fullScore = mean(csMinus_hitScore - csMinus_missScore); % per CS- session
    end
    % --------
    if saveData == 1
        %mkdir
        saveFolder = [saveDirec, '/', mouse '/' dataset '/'];
        if ~isdir(saveFolder)
            mkdir(saveFolder);
        end
        %As .csv files
        %filtered data
        csvwrite([saveFolder, dataset, '_butterFiltered.csv'], blinkData_butterFiltered);
        csvwrite([saveFolder, dataset, '_fullFiltered.csv'], blinkData_fullFiltered);
        csvwrite([saveFolder, dataset, '_csPlus_fullFiltered.csv'], blinkData_csPlus_fullFiltered);
        csvwrite([saveFolder, dataset, '_csMinus_fullFiltered.csv'], blinkData_csMinus_fullFiltered);
        csvwrite([saveFolder, dataset, '_csPlus_fullFiltered_trialAvg.csv'], blinkData_csPlus_fullFiltered_trialAvg);
        csvwrite([saveFolder, dataset, '_csMinus_fullFiltered_trialAvg.csv'], blinkData_csMinus_fullFiltered_trialAvg);
        %raw data
        csvwrite([saveFolder, dataset, '_csPlus.csv'], blinkData_csPlus);
        csvwrite([saveFolder, dataset, '_csMinus.csv'], blinkData_csMinus);
        % CS Type for the session
        csvwrite(([saveFolder, dataset, '_csType.csv']), csType); %".csv"
        
        if findSignificantBlinks == 1
            %scores
            %CS+
            csvwrite([saveFolder, dataset, '_csPlus_hitScore.csv'], csPlus_hitScore);
            csvwrite([saveFolder, dataset, '_csPlus_missScore.csv'], csPlus_missScore);
            csvwrite([saveFolder, dataset, '_csPlus_fullScore.csv'], csPlus_fullScore);
            %CS-
            csvwrite([saveFolder, dataset, '_csMinus_hitScore.csv'], csMinus_hitScore);
            csvwrite([saveFolder, dataset, '_csMinus_missScore.csv'], csMinus_missScore);
            csvwrite([saveFolder, dataset, '_csMinus_fullScore.csv'], csMinus_fullScore);
            
            %blink rastors
            %CS+
            csvwrite([saveFolder, dataset, '_blinks_csPlus_fullTrial.csv'], blinks_csPlus_fullTrial);
            csvwrite([saveFolder, dataset, '_blinks_csPlus_pretone.csv'], blinks_csPlus_pretone);
            csvwrite([saveFolder, dataset, '_blinks_csPlus_cs.csv'], blinks_csPlus_cs);
            %CS-
            csvwrite([saveFolder, dataset, '_blinks_csMinus_fullTrial.csv'], blinks_csPlus_fullTrial);
            csvwrite([saveFolder, dataset, '_blinks_csMinus_pretone.csv'], blinks_csMinus_pretone);
            csvwrite([saveFolder, dataset, '_blinks_csMinus_cs.csv'], blinks_csMinus_cs);
        end
        
        %As matlab files
        %filtered data
        save([saveFolder dataset '_butterFiltered'], 'blinkData_butterFiltered');
        save([saveFolder dataset '_fullFiltered'], 'blinkData_fullFiltered');
        save([saveFolder dataset '_csPlus_fullFiltered'], 'blinkData_csPlus_fullFiltered');
        save([saveFolder dataset '_csMinus_fullFiltered'], 'blinkData_csMinus_fullFiltered');
        save([saveFolder, dataset, '_csPlus_fullFiltered_trialAvg'], 'blinkData_csPlus_fullFiltered_trialAvg');
        save([saveFolder, dataset, '_csMinus_fullFiltered_trialAvg'], 'blinkData_csMinus_fullFiltered_trialAvg');
        %raw data
        save([saveFolder dataset '_csPlus'], 'blinkData_csPlus');
        save([saveFolder dataset '_csMinus'], 'blinkData_csMinus');
        % CS Type for the session
        save(([saveFolder dataset '_csType']), 'csType'); %".mat"
        
        if findSignificantBlinks == 1
            %scores
            %CS+
            save([saveFolder, dataset, '_csPlus_hitScore'], 'csPlus_hitScore');
            save([saveFolder, dataset, '_csPlus_missScore'], 'csPlus_missScore');
            save([saveFolder, dataset, '_csPlus_fullScore'], 'csPlus_fullScore');
            %CS-
            save([saveFolder, dataset, '_csMinus_hitScore'], 'csMinus_hitScore');
            save([saveFolder, dataset, '_csMinus_missScore'], 'csMinus_missScore');
            save([saveFolder, dataset, '_csMinus_fullScore'], 'csMinus_fullScore');
            
            %blink rastors
            %CS+
            save([saveFolder, dataset, '_blinks_csPlus_fullTrial'], 'blinks_csPlus_fullTrial');
            save([saveFolder, dataset, '_blinks_csPlus_pretone'], 'blinks_csPlus_pretone');
            save([saveFolder, dataset, '_blinks_csPlus_cs'], 'blinks_csPlus_cs');
            %CS-
            save([saveFolder, dataset, '_blinks_csMinus_fullTrial'], 'blinks_csPlus_fullTrial');
            save([saveFolder, dataset, '_blinks_csMinus_pretone'], 'blinks_csMinus_pretone');
            save([saveFolder, dataset, '_blinks_csMinus_cs'], 'blinks_csMinus_cs');
        end
    end
end
pause(5);
beep;
disp('Done!');
%
% %--
% %Plot all scores
% close all
% nSessions = 4;
% nMice = 4;
% csPlus = zeros(nMice, nSessions);
% csMinus = zeros(nMice, nSessions);
%
% for i = 1:nMice
%     mouse = ['MouseK' num2str(i)];
%     csPlus(i,:) = (csvread([saveDirec mouse '_csPlus.csv']))*100;
%     csMinus(i,:) = (csvread([saveDirec mouse '_csMinus.csv']))*100;
% end
% figure(3);
% plot((14:17), csPlus,'blue*-', 'LineWidth', 1, 'MarkerSize', 6);
% hold on;
% plot((14:17), csMinus, 'red*-', 'LineWidth', 1, 'MarkerSize', 2);
% hold on;
% errorbar((14:17), mean(csPlus,1), std(csPlus,1), 'blue', 'LineWidth', 3, 'Marker', 'o', 'MarkerSize', 8);
% hold on;
% errorbar((14:17), mean(csMinus,1), std(csMinus,1), 'red', 'LineWidth', 3, 'Marker', 'o', 'MarkerSize', 8);
