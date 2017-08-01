% AUTHOR - Kambadur Ananthamurthy
% PURPOSE - Use this to plot the week's behaviour data

%addpath('/home/shriya/Documents/MATLAB/CustomFunctions_MATLAB')

clear all
close all

week = 3;
nAnimals = 3;
nSessions = 2;
sessionType = 12;
multipleSets = 0;

if multipleSets == 1
    nSets = 2;
else
    nSets = 1;
end

if sessionType == 12
    probe = 0;
else
    probe = 1;
    %probe = 0;
end

saveDirec = ('/home/shriya/Work/Analysis/eyeBlinkBehaviourAnalysis/');

fontSize = 12;

for session = 1:nSessions
    close all
    for set = 1:nSets
        if set == 1
            count = 1;
            count2 = 1;
        else
            count = 3;
            count2 = 2;
        end
        for i = 1:nAnimals
            if set == 1
                %mouse = ['MouseK' num2str(i+16)]; %edit
                mouse = ['S' num2str(i+1)]; %edit
            else
                %mouse = ['MouseK' num2str(i+22)]; %edit
                mouse = ['S' num2str(i+22)]; %edit
            end
            
            a_plus = [];
            b_minus = [];
            c_probe = [];
            
            %session = 1;
            dataset = [mouse '_SessionType' num2str(sessionType) '_Session' num2str(session)];
            saveFolder = [saveDirec, 'Mouse' mouse '/' 'Mouse' dataset '/'];
            
            blinkData_csPlus = csvread([saveFolder 'Mouse' dataset '_csPlus.csv']);
            blinkData_csMinus = csvread([saveFolder 'Mouse' dataset '_csMinus.csv']);
            probeTrials = csvread([saveFolder 'Mouse' dataset '_probeTrials.csv']);
            
            a_plus = [a_plus; blinkData_csPlus(1:12,1:1000)];
            b_minus = [b_minus; blinkData_csMinus(1:12,1:1000)];
            if probe == 1
                c_probe = [c_probe; blinkData_csPlus(probeTrials,:)];
            end
            
            figure(1);
            subplot(nAnimals,nSets*2,count);
            imagesc(blinkData_csPlus);
            title([mouse ' ST' num2str(sessionType) ' S' num2str(session) ' CS+'],...
                'FontSize',fontSize,...
                'FontWeight','bold');
            xlabel('Time/10 ms',...
                'FontSize',fontSize,...
                'FontWeight','bold');
            xt = get(gca, 'XTick');
            %set(gca, 'FontSize', fontSize);
            ylabel('Trials',...
                'FontSize',fontSize,...
                'FontWeight','bold');
            yt = get(gca, 'YTick');
            %set(gca, 'FontSize', fontSize);
            caxis([-30, 30])
            colorbar;
            colormap(jet);
            
            subplot(nAnimals,nSets*2,count+1);
            imagesc(blinkData_csMinus);
            title([mouse ' ST' num2str(sessionType) ' S' num2str(session) ' CS-'],...
                'FontSize',fontSize,...
                'FontWeight','bold');
            xlabel('Time/10 ms',...
                'FontSize',fontSize,...
                'FontWeight','bold');
            xt = get(gca, 'XTick');
            %set(gca, 'FontSize', fontSize);
            ylabel('Trials',...
                'FontSize',fontSize,...
                'FontWeight','bold');
            yt = get(gca, 'YTick');
            %set(gca, 'FontSize', fontSize);
            caxis([-30, 30])
            colorbar;
            colormap(jet);
            %         print(['/Users/ananth/Desktop/' 'rawBlinks_set'...
            %             num2str(set) '_SessionType_' num2str(sessionType)...
            %             '_Session' num2str(session)],...
            %             '-djpeg');
            count = count+nSets*2;
            
            figure(2);
            subplot(nAnimals,nSets,count2)
            if probe == 1
                plot(median(c_probe,1), 'g')
                hold on
            end
            plot(median(a_plus,1),'b');
            hold on;
            plot(median(b_minus,1),'r');
            
            title([mouse ' ST' num2str(sessionType) ' S' num2str(session)],...
                'FontSize',fontSize,...
                'FontWeight','bold');
            axis([0 1000 -30 30]);
            xlabel('Time/10 ms',...
                'FontSize',fontSize,...
                'FontWeight','bold');
            xt = get(gca, 'XTick');
            %set(gca, 'FontSize', fontSize);
            ylabel('Blink (fold change)',...
                'FontSize',fontSize,...
                'FontWeight','bold');
            yt = get(gca, 'YTick');
            %set(gca, 'FontSize', fontSize);
            if probe == 1
                legend('Median Probe Trials', 'Median CS+ Trials','Median CS- Trials');
            else
                legend('Median CS+ Trials','Median CS- Trials');
            end
            %         figure(2);
            %         print(['/Users/ananth/Desktop/' 'median_set'...
            %             num2str(set) '_SessionType_' num2str(sessionType)...
            %             '_Session' num2str(session)],...
            %             '-djpeg');
            count2 = count2+nSets;
        end
    end
    
    figure(1);
    print(['/Users/ananth/Desktop/rawBlinks_SessionType' num2str(sessionType)...
        '_Session' num2str(session) ...
        '_week' num2str(week)],...
        '-djpeg');
    figure(2);
    print(['/home/shriya/Desktop/median_SessionType_' num2str(sessionType)...
        '_Session' num2str(session) ...
        '_week' num2str(week)],...
        '-djpeg');
end
