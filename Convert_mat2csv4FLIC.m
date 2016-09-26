load examples.mat
imgdir = './images/';
%% display a random image
length(examples)
i = randi(length(examples));

for j=1:length(examples)
 if strcmp(examples(j).filepath,'2-fast-2-furious-00033091.jpg');
 %if examples(j).filepath == '2-fast-2-furious-00033091.jpg';
  i = j
  break;
 end
end

%desire number of image
%i=1;

%=========== file ===========

fileID = fopen('torsobox.csv','w')
fprintf(fileID,'%s,%s\n','filepath','data');
for i=1:length(examples)
 fprintf(fileID,'%s',examples(i).filepath)
 fprintf(fileID,',%d',round(examples(i).torsobox))
 fprintf(fileID,'\n')
end
fclose(fileID)

fileID = fopen('joints.csv','w')
fprintf(fileID,'%s,%s\n','filepath','data');
for i=1:length(examples)
 fprintf(fileID,'%s',examples(i).filepath)
 fprintf(fileID,',%d',round(examples(i).coords))
 fprintf(fileID,'\n')
end
fclose(fileID)

%============================

% display torso detected by berkeley poselets
plotbox(examples(i).torsobox,'w--')
x=examples(i).coords(1,2)
y=examples(i).coords(2,2)
hold on
d = plot(x,y,'g')
plotjoints(examples(i).coords,'g')

% display all the labeled joints; median of 5 annotations by mechanical turk
%myplot(examples(i).coords(:,lookupPart('lsho','lelb','lwri')),'go-','linewidth',3)
%myplot(examples(i).coords(:,lookupPart('rsho','relb','rwri')),'mo-','linewidth',3)
%myplot(examples(i).coords(:,lookupPart('rhip','lhip')),'bo-','linewidth',3)
%myplot(examples(i).coords(:,lookupPart('leye','reye','nose','leye')),'c.-','linewidth',3)