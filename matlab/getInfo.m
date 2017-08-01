% The following gets General Information from the filename of any dataset
% Author: Kambadur Ananthamurthy
% Created: 20151128

% The function depends on the input "x1" which should have the dataset
% information in the form of "MouseNN_SessionTypeX_SessionY"

function [mouse, sessionType, session] = getInfo(direc)

slashi=strfind(direc, '/');
dataset=direc(1,(slashi(1,length(slashi)-1))+1:(length(direc))); % Dataset name, in the format of MouseNN_BlockX_sessionY
uscorei=strfind(dataset, '_');

mouse = dataset(1:uscorei(1,1)-1);
sessionType = dataset((uscorei(1,1)+12):uscorei(1,2)-1); %How does this work?:P
session = dataset((uscorei(1,2)+8):end);

end
