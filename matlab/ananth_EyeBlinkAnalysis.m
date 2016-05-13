% AUTHOR - Kambadur Ananthamurthy
% PURPOSE - Read raw .csv files for eye blink behaviour data
% SPECIAL NOTE - This version of the code will work for data obtained from 20151225
% This code additionall requires getInfo.m and blinkFilter.m to work.

%addpath('/home/shriya/Documents/MATLAB/CustomFunctions_MATLAB')

%Please work with the data from all sessions of an animal, before proceeding to the next animal

clear all
%close all

%Operations (0 = Don't Perform, 1 = Perform)
getGeneralInformation = 1;
doBaselineCorrection = 1;
plotFigures = 0;
filterData = 0;
splitCS = 1; % split CS+ and CS- trials
calculatePerformance = 0;
saveData = 1;

saveDirec = ('/home/shriya/Work/Analysis/eyeBlinkBehaviourAnalysis/');

listPath=('/home/shriya/Work/BehaviourData/folder_list.txt'); %Check path ID
%Exception cases
%listPath=('/Users/ananth/Desktop/Work/Behaviour/folder_list2.txt'); %Check path ID

fid=fopen(listPath);

%Protocol Information
preTime = 5000; %in ms
csTime = 100; %in ms
traceTime = 250; %in ms
puffTime = 100; %in ms
postTime = 5000; %in ms
nstages = 4; % The number of stages of the session

if filterData == 1
    %Parameters for filter
    samplingRate = 100;
    lowPassCutoffFreq = 40; % in Hz
    highPassCutoffFreq = 0.1; % in Hz
    nbins = 50;
    filterOrder = 4;
    offset = 0.6; % in the range of 0.0 - 1.0
    gain = 4;
    phaseOffsetFactor = 2; %in samples; also used for scoring performance
end

count = 0;
nHeaderLines = 5;
while 1
    tline = fgetl(fid);
    if ~ ischar(tline), break, end
    
    direc = [tline '/'];
    
    if getGeneralInformation == 1
        %General Information:
        [mouse, sessionType, session] = getInfo(direc);
        sessionType_description = {'Control'; 'Trace'; 'Delay'};
        dataset = [mouse, '_SessionType', sessionType, '_Session' session];
        dataset(dataset == '/') = [];
        disp(dataset);
    end
    
    if str2num(sessionType) == 12
        traceTime = 350; %in ms
        totalTrials = 40;
    elseif str2num(sessionType) == 13
        traceTime = 350; %in ms
        totalTrials = 100;
        %     elseif str2num(sessionType) == 2
        %         traceTime = 0; %in ms
        %         totalTrials = 100;
    else
        warning('Unable to determine SessionType');
    end
    
    %PROBLEM: Different trials have unequal number of data points (not MATLAB friendly)
    %SOLUTION: First pass to preallocate
    for trialNum = 1:totalTrials
        filename = [direc, 'Trial', num2str(trialNum), '.csv'];
        rawData_size(trialNum) = size(csvread(filename, nHeaderLines, 0), 1);
    end
    
    blinkData = zeros(totalTrials, min(rawData_size)); %to store baseline corrected data (Percent df/F)
    blinkData_stdDev = zeros(totalTrials, min(rawData_size)); %to store std dev
    blinkData_baselines = zeros(totalTrials,1); %to store baselines for every trial
    blinkData_smooth = zeros(totalTrials, min(rawData_size)); %to store sliding window average smoothened data
    blinkRastors = zeros(totalTrials, min(rawData_size)); %to store blink rastors
    
    %We are next going to seperate out the CS+ and CS- trials
    blinkData_csPlus = [];
    blinkData_csMinus = [];
    %     blinkData_csPlus_butterFiltered = [];
    %     blinkData_csMinus_butterFiltered = [];
    blinkData_csPlus_fullFiltered = [];
    blinkData_csPlus_butterFiltered = [];
    blinkData_csMinus_fullFiltered = [];
    blinkData_csMinus_butterFiltered = [];
    probeTrials = [];
    probeTrials_actualIndices = [];
    
    %Preallocation for speed
    csType = nan(totalTrials, 1);
    
    for trialNum = 1:totalTrials
        
        filename = [direc, 'Trial', num2str(trialNum), '.csv'];
        csType(trialNum)= csvread(filename, nHeaderLines, 2, [ nHeaderLines 2 nHeaderLines 2] ); %reads only row nHeaderLines, column 3
        rawData = csvread(filename, nHeaderLines, 0); %starts reading only from row 6; skips till row 4
        blinkData(trialNum,1:min(rawData_size))= rawData(1:min(rawData_size),1); %has only blinkValues
        
        if doBaselineCorrection == 1
            blinkData_baselines(trialNum) = prctile(blinkData(trialNum,:), 50, 2); %50th percentile - median
            for sample = 1: size(blinkData,2)
                blinkData(trialNum, sample) = ((blinkData(trialNum,sample)/blinkData_baselines(trialNum,1))-1)*100; %baseline corrected
            end
            clear sample
        end
        
        % Filtering
        if filterData == 1
            myData = blinkData(trialNum,:);
            [onlyButterworth, fullFiltered] = blinkFilter(myData, samplingRate, lowPassCutoffFreq, highPassCutoffFreq, filterOrder, offset, gain, phaseOffsetFactor, nbins);
            blinkData_butterFiltered(trialNum,1:size(onlyButterworth,2))= onlyButterworth;
            blinkData_fullFiltered(trialNum,(1:size(fullFiltered,2))) = fullFiltered;
            
        end
        
        %close all
        if plotFigures == 1
            figure(1); %CS Trial Type
            plot(csType, 'ro',...
                'MarkerSize', 10,...
                'MarkerFaceColor', 'r');
            
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
        
        %Slicing
        if splitCS == 1
            if csType(trialNum) == 1
                blinkData_csPlus = [blinkData_csPlus; blinkData(trialNum,:)];
                if filterData ==1
                    blinkData_csPlus_fullFiltered = [blinkData_csPlus_fullFiltered; blinkData_fullFiltered(trialNum,:)];
                    blinkData_csPlus_butterFiltered = [blinkData_csPlus_butterFiltered; blinkData_butterFiltered(trialNum,:)];
                end
                try
                    if csvread(filename, nHeaderLines+1, 3, [ nHeaderLines+1 3 nHeaderLines+1 3] ) == 0   %reads only the row after nHeaderLines, column 4
                        probeTrials = [probeTrials size(blinkData_csPlus,1)];
                        %disp('Found a probe Trial!')
                        %disp(probeTrials)
                        probeTrials_actualIndices(trialNum) = 1;
                    else
                        probeTrials_actualIndices(trialNum) = 0;
                    end
                catch
                    warning('Unable to determine ProbeTrials');
                end
            elseif csType(trialNum) == 0
                blinkData_csMinus = [blinkData_csMinus; blinkData(trialNum,:)];
                if filterData == 1
                    blinkData_csMinus_fullFiltered = [blinkData_csMinus_fullFiltered; blinkData_fullFiltered(trialNum,:)];
                    blinkData_csMinus_butterFiltered = [blinkData_csMinus_butterFiltered; blinkData_butterFiltered(trialNum,:)];
                end
            end
        end
    end
    
    clear trialNum
    
    %Trial Averages for every session
    blinkData_csPlus_fullFiltered_trialAvg = mean(blinkData_csPlus_fullFiltered, 1);
    blinkData_csPlus_butterFiltered_trialAvg = mean(blinkData_csPlus_butterFiltered, 1);
    blinkData_csMinus_fullFiltered_trialAvg = mean(blinkData_csMinus_fullFiltered, 1);
    blinkData_csMinus_butterFiltered_trialAvg = mean(blinkData_csMinus_butterFiltered, 1);
    
    %Calculate the performance per trial separately for CS+ and CS-
    if calculatePerformance == 1
        %Scoring
        %Get Session Performance for CS+
        myData = blinkData_csPlus_fullFiltered;
        % --based on RMS --
        [cs_csPlus_rms, preTone_csPlus_rms] = calculateRMS(myData, samplingRate, phaseOffsetFactor, traceTime, preTime, csTime);
        % --based on Thresholded Blinks --
        csPlus_fullScore = scorePerformance_thresholdedBlinks(myData, samplingRate, phaseOffsetFactor, traceTime, preTime, csTime);
        
        %Get Session Performance - for CS-
        myData = blinkData_csMinus_fullFiltered;
        % --based on RMS --
        [cs_csMinus_rms, preTone_csMinus_rms] = calculateRMS(myData, samplingRate, phaseOffsetFactor, traceTime, preTime, csTime);
        % --based on Thresholded Blinks --
        csMinus_fullScore = scorePerformance_thresholdedBlinks(myData, samplingRate, phaseOffsetFactor, traceTime, preTime, csTime);
    end
    % --------
    if saveData == 1
        %mkdir
        saveFolder = [saveDirec, '/', mouse '/' dataset '/'];
        if ~isdir(saveFolder)
            mkdir(saveFolder);
        end
        %As .csv files
        if filterData == 1
            %filtered data
            csvwrite([saveFolder, dataset, '_butterFiltered.csv'], blinkData_butterFiltered);
            csvwrite([saveFolder, dataset, '_fullFiltered.csv'], blinkData_fullFiltered);
            csvwrite([saveFolder, dataset, '_csPlus_fullFiltered.csv'], blinkData_csPlus_fullFiltered);
            csvwrite([saveFolder, dataset, '_csMinus_fullFiltered.csv'], blinkData_csMinus_fullFiltered);
            csvwrite([saveFolder, dataset, '_csPlus_fullFiltered_trialAvg.csv'], blinkData_csPlus_fullFiltered_trialAvg);
            csvwrite([saveFolder, dataset, '_csMinus_fullFiltered_trialAvg.csv'], blinkData_csMinus_fullFiltered_trialAvg);
            csvwrite([saveFolder, dataset, '_csPlus_butterFiltered.csv'], blinkData_csPlus_butterFiltered);
            csvwrite([saveFolder, dataset, '_csMinus_butterFiltered.csv'], blinkData_csMinus_butterFiltered);
            csvwrite([saveFolder, dataset, '_csPlus_butterFiltered_trialAvg.csv'], blinkData_csPlus_butterFiltered_trialAvg);
            csvwrite([saveFolder, dataset, '_csMinus_butterFiltered_trialAvg.csv'], blinkData_csMinus_butterFiltered_trialAvg);
        end
        %raw data
        csvwrite([saveFolder, dataset, '_csPlus.csv'], blinkData_csPlus);
        csvwrite([saveFolder, dataset, '_csMinus.csv'], blinkData_csMinus);
        % CS Type for the session
        csvwrite(([saveFolder, dataset, '_csType.csv']), csType); %".csv"
        % Probe (no puff) trials for the session
        csvwrite(([saveFolder, dataset, '_probeTrials.csv']), probeTrials); %".csv"
        csvwrite(([saveFolder, dataset, '_probeTrials_actual.csv']), probeTrials_actualIndices); %".csv"
        
        if calculatePerformance == 1
            %scores
            %CS+
            csvwrite([saveFolder, dataset, '_csPlus_fullScore.csv'], csPlus_fullScore);
            %CS-
            csvwrite([saveFolder, dataset, '_csMinus_fullScore.csv'], csMinus_fullScore);
            
            %RMS values
            csvwrite([saveFolder, dataset, '_cs_csPlus_rms.csv'], cs_csPlus_rms);
            csvwrite([saveFolder, dataset, '_preTone_csPlus_rms.csv'], preTone_csPlus_rms);
            csvwrite([saveFolder, dataset, '_cs_csMinus_rms.csv'], cs_csMinus_rms);
            csvwrite([saveFolder, dataset, '_preTone_csMinus_rms.csv'], preTone_csMinus_rms);
        end
        %As matlab files
        if filterData == 1
            %filtered data
            save([saveFolder dataset '_butterFiltered'], 'blinkData_butterFiltered');
            save([saveFolder dataset '_fullFiltered'], 'blinkData_fullFiltered');
            save([saveFolder dataset '_csPlus_fullFiltered'], 'blinkData_csPlus_fullFiltered');
            save([saveFolder dataset '_csMinus_fullFiltered'], 'blinkData_csMinus_fullFiltered');
            save([saveFolder, dataset, '_csPlus_fullFiltered_trialAvg'], 'blinkData_csPlus_fullFiltered_trialAvg');
            save([saveFolder, dataset, '_csMinus_fullFiltered_trialAvg'], 'blinkData_csMinus_fullFiltered_trialAvg');
            save([saveFolder dataset '_csPlus_butterFiltered'], 'blinkData_csPlus_butterFiltered');
            save([saveFolder dataset '_csMinus_butterFiltered'], 'blinkData_csMinus_butterFiltered');
            save([saveFolder, dataset, '_csPlus_butterFiltered_trialAvg'], 'blinkData_csPlus_butterFiltered_trialAvg');
            save([saveFolder, dataset, '_csMinus_butterFiltered_trialAvg'], 'blinkData_csMinus_butterFiltered_trialAvg');
        end
        %raw data
        save([saveFolder dataset '_csPlus'], 'blinkData_csPlus');
        save([saveFolder dataset '_csMinus'], 'blinkData_csMinus');
        % CS Type for the session
        save(([saveFolder dataset '_csType']), 'csType'); %".mat"
        % Probe (no puff) trials for the session
        save(([saveFolder, dataset, '_probeTrials']), 'probeTrials'); %".mat"
        save(([saveFolder, dataset, '_probeTrials_actual']), 'probeTrials_actualIndices'); %".mat"
        
        if calculatePerformance == 1
            %scores
            %CS+
            save([saveFolder, dataset, '_csPlus_fullScore'], 'csPlus_fullScore');
            %CS-
            save([saveFolder, dataset, '_csMinus_fullScore'], 'csMinus_fullScore');
            
            %RMS values
            save([saveFolder, dataset, '_cs_csPlus_rms'], 'cs_csPlus_rms');
            save([saveFolder, dataset, '_preTone_csPlus_rms'], 'preTone_csPlus_rms');
            save([saveFolder, dataset, '_cs_csMinus_rms'], 'cs_csMinus_rms');
            save([saveFolder, dataset, '_preTone_csMinus_rms'], 'preTone_csMinus_rms');
        end
    end
    
    %deinde;
end
%pause(5);
beep;
disp('Done!');