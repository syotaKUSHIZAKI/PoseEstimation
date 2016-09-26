load joints.mat
imgdir = './images/';

whos -file joints.mat

i = randi(length(joints));
s=sprintf('%04d',i)
filepath=['im',s,'.jpg']
img = imread([imgdir,'/',filepath]);
cla, imagesc(img), axis image, hold on
disp(joints(:,:,i))
plotjoints(joints(:,:,i),'g')

fileID = fopen('joints.csv','w')
fprintf(fileID,'%s,%s\n','filepath','data');
for i=1:length(joints)
 s=sprintf('%04d',i)
 filepath=['im',s,'.jpg']
 fprintf(fileID,'%s',filepath)
 for j=1:14
  fprintf(fileID,',%d,%d',joints(1,j,i),joints(2,j,i))
 end
 fprintf(fileID,'\n')
end
fclose(fileID)