function varargout = task_for_shortterm(varargin)
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @task_for_shortterm_OpeningFcn, ...
                   'gui_OutputFcn',  @task_for_shortterm_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
function task_for_shortterm_OpeningFcn(hObject, eventdata, handles, varargin)
handles.output = hObject;
guidata(hObject, handles);
function varargout = task_for_shortterm_OutputFcn(hObject, eventdata, handles) 
varargout{1} = handles.output;




% --------------------------------------------------------------------
function m_file_Callback(hObject, eventdata, handles)
% hObject    handle to m_file (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
function m_file_open_Callback(hObject, eventdata, handles)
[filename,pathname]=uigetfile( ...
{'*.bmp;*.jpg;*.png;*.jpeg','Image Files(*.bmp,*.jpg,*.png,*.jpeg)';
    '*,*','All Files(*,*)'},...
'Pick an image');
 if isequal(filename,0)||isequal(pathname,0)
     return;
 end
fpath=[pathname filename];
global img_orig;
img_orig=imread(fpath);
unvisable_all(handles);
axes(handles.axes1);
imshow(img_orig);
% --------------------------------------------------------------------
function m_file_save_Callback(hObject, eventdata, handles)
[filename, pathname]=uiputfile({'*.bmp','BMP files';'*.jpg','JPG files'},'Save an Image');
 if isequal(filename,0)||isequal(pathname,0)
     return;
 else
     fpath=fullfile(pathname,filename);
 end
 global img_orig;
 imwrite(img_orig,fpath);
% --------------------------------------------------------------------
function m_file_exit_Callback(hObject, eventdata, handles)
close(handles.figure1);

function m_file_jihe_pingyi_Callback(hObject, eventdata, handles)
global img_orig;
A=img_orig;
a=50;
b=50;
se=translate(strel(1),[a b]);
B=imdilate(A,se);

unvisable_all(handles);

axes(handles.axes1);
imshow(A);
title('原图');
axes(handles.axes2);

str=['平移',num2str(a),',',num2str(b)];
imshow(B);title(str);
function m_file_jihe_suofang_Callback(hObject, eventdata, handles)
global img_orig;
A=img_orig;
D=imresize(A,0.5);

figure;
imshow(A);title('原图');

figure;
imshow(D);title('缩放');
function m_file_jihe_xuanzhuan_Callback(hObject, eventdata, handles)
global img_orig;
A=img_orig;
C=imrotate(A,45);



unvisable_all(handles);

axes(handles.axes1);
imshow(A);
title('原图');
axes(handles.axes2);
imshow(C);
title('旋转');
function m_file_jihe_jingxiang_Callback(hObject, eventdata, handles)

global img_orig;
A=img_orig;
E=size(A);
F=size(A);

for i=1:3
    a0=[];
    L=A(:,:,i);
    for j=1:E(1)
        H=[L(j,:);a0];%即在H下方补上a0
        a0=H;       %循环抽取每一行，并在下方加上a0，即前面几行的倒序排列
    end
    M(:,:,i)=H;
end

for i=1:3
    a0=[];
    L=A(:,:,i);
    for j=1:F(2)
        H=[L(:,j),a0];%即在H右方补上a0
        a0=H;         %循环抽取每一行，并在下方加上a0，即前面几行的倒序排列
    end
    N(:,:,i)=H;
end

unvisable_all(handles);

axes(handles.axes1);
imshow(A);title('原图');
axes(handles.axes2);
imshow(M);title('上下翻转');
axes(handles.axes5);
imshow(N);title('左右翻转');
function m_file_jihe_zhuanzhi_Callback(hObject, eventdata, handles)
global img_orig;
I=img_orig;
T=affine2d([0 1 0;1 0 0;0 0 1]);
dst=imwarp(I,T); 
unvisable_all(handles);
axes(handles.axes1);
imshow(I);title('原图');
axes(handles.axes2);
imshow(dst);title('转置');
function m_file_jihe_baiyechuang_Callback(hObject, eventdata, handles)

global img_orig;
I=img_orig;
unvisable_all(handles);
size_info=size(I);    
height=size_info(1);	
width=size_info(2);  
mask=zeros(height,width);  
num=10;
for j=1:floor(height/num)
    for i=1:num
        white_begin=floor(1+(i-1)*(height/num));
        white_end=ceil(j+(i-1)*(height/num));
        mask(white_begin:white_end,:)=1;  
    end
    J=cat(3,mask,mask,mask);
    J8=uint8(J);
    I8=uint8(I);
    L=immultiply(I8,J8);
    drawnow
    axes(handles.axes1);
    imshow(I8);title('原图')
    axes(handles.axes2);
    imshow(J);title('遮罩')
    axes(handles.axes3);
    imshow(L);title('百叶窗=原图.*遮罩');
end
function m_file_jihe_fenkuai_Callback(hObject, eventdata, handles)
global img_orig;
I=img_orig;
I = imresize(I,[64*4 64*5]);
rs = size(I, 1); cs = size(I, 2); 
sz = 64;                         
numr = rs/sz;                   
numc = cs/sz;                    
ch = sz; cw = sz;                  
t1 = (0:numr-1)*ch + 1; t2 = (1:numr)*ch;     
t3 = (0:numc-1)*cw + 1; t4 = (1:numc)*cw;     
figure;   
k = 0;                                   
for i = 1 : numr            
    for j = 1 : numc          
        temp = I(t1(i):t2(i), t3(j):t4(j), :);      
        k = k + 1;  
        subplot(numr, numc, k);                     
        imshow(temp);  
        pause(0.1);  
    end  
end  
% --------------------------------------------------------------------

function m_file_duibidu_Callback(hObject, eventdata, handles)
global img_orig;
I=img_orig;
I=im2double(I);
a=2;b=0;
O=a.*I+b/255;
unvisable_all(handles);
axes(handles.axes2);
imshow(O);title('增加对比度');
a=0.5;b=0;
O=a.*I+b/255;
axes(handles.axes3);
imshow(O);title('减小对比度'); 
axes(handles.axes1);
imshow(I);title('原图')
function m_file_liangdu_Callback(hObject, eventdata, handles)
global img_orig;
I=img_orig;
I=im2double(I);
a=1;b=50;
O=a.*I+b/255;
unvisable_all(handles);
axes(handles.axes2);
imshow(O);title('增加亮度');
a=1;b=-50;
O=a.*I+b/255;
axes(handles.axes3);
imshow(O);title('减小亮度');
axes(handles.axes1);
imshow(I);title('原图')
function m_file_fangse_Callback(hObject, eventdata, handles)
global img_orig;
I=img_orig;
I=im2double(I);
a=-1;b=255;
O=a.*I+b/255;
unvisable_all(handles);
axes(handles.axes2);
imshow(O);title('图像反色');
axes(handles.axes1);
imshow(I);title('原图')
% --------------------------------------------------------------------
function m_file_huidu_Callback(hObject, eventdata, handles)
global img_orig;
Image=img_orig;
unvisable_all(handles);
[M,N,nDims]=size(Image);
Image=im2double(Image);
ImageStretch=Image;
for i=1:nDims  % 对每个波段依次进行灰度拉伸
    Sp=Image(:,:,i);
    MaxDN=max(max(Sp));
    MinDN=min(min(Sp));
    Sp=(Sp-MinDN)/(MaxDN-MinDN);  % 灰度拉伸公式
    ImageStretch(:,:,i)=Sp;
end
if nDims==3||nDims==1  % 若为灰度图和RGB真彩色图则以常规方式保存并输出
    axes(handles.axes1);imshow(Image);title('原图');
    axes(handles.axes2);imshow(ImageStretch);title('灰度拉伸');
else  % 若为多波段遥感影像则按照TM 3,2,1组合形式保存并输出
    axes(handles.axes1);imshow(Image(:,:,[3,2,1]));title('原图');
    axes(handles.axes2);imshow(ImageStretch(:,:,[3,2,1]));title('灰度拉伸');   
end

function m_file_junhenhua_Callback(hObject, eventdata, handles)
global img_orig;
I=img_orig;

unvisable_all(handles);

[row,col] = size(I);
%display the original image
axes(handles.axes1);imshow(I);title('原始图像');
axes(handles.axes2);imhist(I);title('原始图像直方图');
%Compute the PMF of all pixels of the image
PMF = zeros(1,256);
for i = 1:row
    for j = 1:col
        PMF(I(i,j) + 1) = PMF(I(i,j) + 1) + 1;
    end
end
%Compute the CDF of all pixels of the image
CDF = zeros(1,256);
CDF(1) = PMF(1);
for i = 2:256
    CDF(i) = CDF(i - 1) + PMF(i);
end
%Mapping
for i = 1:256
    Map(i) = round((CDF(i)-1)*255/(row*col));
end
for i = 1:row
    for j = 1:col
        I(i,j) = Map(I(i,j) + 1);
    end
end
axes(handles.axes4);imshow(I);title('处理后图像');
axes(handles.axes5);imhist(I);title('处理后图像直方图');

function m_file_junzhi_Callback(hObject, eventdata, handles)
global img_orig;
A=img_orig;
B=imfilter(A,fspecial('average',5));


unvisable_all(handles);
axes(handles.axes2);
imshow(B);title('均值滤波');
axes(handles.axes1);
imshow(A);title('原图')


function m_file_zhongzhi_Callback(hObject, eventdata, handles)
global img_orig;
A=img_orig;
C=medfilt2(A,[3 3]);

unvisable_all(handles);
axes(handles.axes2);
imshow(C);title('中值滤波');
axes(handles.axes1);
imshow(A);title('原图')



% --------------------------------------------------------------------
function m_file_ditong_Callback(hObject, eventdata, handles)
unvisable_all(handles);
global img_orig;
A=img_orig;
A=im2double(A);
F=fftshift(fft2(A));
[M,N]=size(F);
n=3;D0=40;
u0=floor(M/2);
v0=floor(N/2);
 
for u=1:M
    for v=1:N
        D=sqrt((u-u0)^2+(v-v0)^2);
        H=1/(1+(D/D0)^(2*n));
        G(u,v)=H*F(u,v);
    end
end
g=ifft2(ifftshift(G));
g=im2uint8(real(g));
axes(handles.axes2);
imshow(g);title('低通滤波')
 
axes(handles.axes1);
imshow(A);title('原图')

function m_file_gaotong_Callback(hObject, eventdata, handles)

unvisable_all(handles);
global img_orig;
A=img_orig;
A=im2double(A);
F=fftshift(fft2(A));
[M,N]=size(F);
n=3;D0=40;
u0=floor(M/2);
v0=floor(N/2);
for u=1:M
    for v=1:N
        D=sqrt((u-u0)^2+(v-v0)^2);
        H=1/(1+(D0/D)^(2*n));
        G(u,v)=H*F(u,v);
    end
end
g=ifft2(ifftshift(G));
g=im2uint8(real(g));
axes(handles.axes2);
imshow(g);title('高通滤波')
 
axes(handles.axes1);
imshow(A);title('原图')
% --------------------------------------------------------------------

function m_file_wei_Callback(hObject, eventdata, handles)
unvisable_all(handles);
global img_orig;
I=img_orig;
axes(handles.axes1);
imshow(I);title('原图')
X=grayslice(I,16);
figure();
imshow(X,hot(16));title('伪彩色增强')

function m_file_jia_Callback(hObject, eventdata, handles)
unvisable_all(handles);
global img_orig;
RGB=img_orig;
axes(handles.axes4);
imshow(RGB(:,:,1));title('原图红色分量灰度图->假彩色增强绿色分量','fontsize',9);
axes(handles.axes5);
imshow(RGB(:,:,2));title('原图绿色分量灰度图->假彩色增强蓝色分量','fontsize',9);
axes(handles.axes6);
imshow(RGB(:,:,3));title('原图蓝色分量灰度图->假彩色增强红色分量','fontsize',9);
RGBnew(:,:,1)=RGB(:,:,3);
RGBnew(:,:,2)=RGB(:,:,1);
RGBnew(:,:,3)=RGB(:,:,2);
axes(handles.axes3);
imshow(RGBnew);title('下面三张灰度图进行假彩色增强');
axes(handles.axes1);
imshow(RGB);title('原图');

function m_file_zhen_Callback(hObject, eventdata, handles)
unvisable_all(handles);
global img_orig;
RGB=img_orig;
axes(handles.axes4);
imshow(RGB(:,:,1));title('原图红色分量灰度图');
axes(handles.axes5);
imshow(RGB(:,:,2));title('原图绿色分量灰度图');
axes(handles.axes6);
imshow(RGB(:,:,3));title('原图蓝色分量灰度图');
RGBnew(:,:,1)=RGB(:,:,1)/2;
RGBnew(:,:,2)=RGB(:,:,2);
RGBnew(:,:,3)=RGB(:,:,3);
axes(handles.axes3);
imshow(RGBnew);title('真彩色增强->红色分量减少');
axes(handles.axes1);
imshow(RGB);title('原图');
axes(handles.axes2);
RGBnew(:,:,1)=RGB(:,:,1);
RGBnew(:,:,2)=RGB(:,:,2)/2;
imshow(RGBnew);title('真彩色增强->绿色分量减少');
% --------------------------------------------------------------------
function m_file_Roberts_Callback(hObject, eventdata, handles)
unvisable_all(handles);
global img_orig;
P=img_orig;
P=rgb2gray(P);
A=edge(P,'roberts');
axes(handles.axes1);
imshow(img_orig);title('原图');
axes(handles.axes2);
imshow(A);title('roberts算子');






function m_file_Sobel_Callback(hObject, eventdata, handles)
unvisable_all(handles);
global img_orig;
P=img_orig;
P=rgb2gray(P);
B=edge(P,'sobel');
axes(handles.axes2);
imshow(B);title('sobel算子');
axes(handles.axes1);
imshow(img_orig);title('原图');


function m_file_Laplacian_Callback(hObject, eventdata, handles)
unvisable_all(handles);
global img_orig;
P=img_orig;
P=rgb2gray(P);
grayPic=P;
[m,n]=size(grayPic);

newGrayPic=grayPic;%为保留图像的边缘一个像素
LaplacianNum=0;%经Laplacian算子计算得到的每个像素的值
LaplacianThreshold=0.2;%设定阈值
for j=2:m-1 %进行边界提取
for k=2:n-1
LaplacianNum=abs(4*grayPic(j,k)-grayPic(j-1,k)-grayPic(j+1,k)-grayPic(j,k+1)-grayPic(j,k-1));
if(LaplacianNum > LaplacianThreshold)
newGrayPic(j,k)=255;
else
newGrayPic(j,k)=0;
end
end
end
axes(handles.axes2);
imshow(newGrayPic);title('Laplacian算子');
axes(handles.axes1);
imshow(img_orig);title('原图');


% --------------------------------------------------------------------
function m_file_jiaohu_Callback(hObject, eventdata, handles)
unvisable_all(handles);

set(handles.slider1,'visible','on');
set(handles.text1,'visible','on');

global img_orig;
P=img_orig;
P=rgb2gray(P);
%h=im2bw_args;
[width,height]=size(P);
axes(handles.axes2);
imhist(P);
title('原图直方图');
T1=128;
P1=zeros(width,height);
for i=1:width
    for j=1:height
        if(P(i,j)<T1)
            P1(i,j)=0;
        else
            P1(i,j)=1;
        end
    end
end

axes(handles.axes4);
imshow(P1);title('阈值分割');




axes(handles.axes1);
imshow(img_orig);title('原图');




function m_file_didai_Callback(hObject, eventdata, handles)
unvisable_all(handles);
global img_orig;
P=img_orig;
P=rgb2gray(P);
P2=double(P);
T=(min(P2(:))+max(P2(:)))/2;
done=false;
i=0;
while ~done
   r1=find(P2<=T);
   r2=find(P2>T);
   Tnew=(mean(P2(r1))+mean(P2(r2)))/2;
   done=abs(Tnew-T)<1;
   T=Tnew;
   i=i+1;
end
P2(r1)=0;
P2(r2)=1;
axes(handles.axes2);
imshow(P2);title('迭代分割');
axes(handles.axes1);
imshow(img_orig);title('原图');
% --------------------------------------------------------------------
function peng_Callback(hObject, eventdata, handles)

unvisable_all(handles);
global img_orig;
P=img_orig;
P=im2bw(P);
sel=strel('square',3);
P1=imdilate(P,sel);
axes(handles.axes1);
imshow(P);title('原图');
axes(handles.axes2);
imshow(P1);title('膨胀');
function fu_Callback(hObject, eventdata, handles)
unvisable_all(handles);
global img_orig;
P=img_orig;
P=im2bw(P);
sel=strel('square',3);
P2=imerode(P,sel);
axes(handles.axes1);
imshow(P);title('原图');
axes(handles.axes2);
imshow(P2);title('腐蚀');
function kai_Callback(hObject, eventdata, handles)
unvisable_all(handles);
global img_orig;
P=img_orig;
P=im2bw(P);
sel=strel('square',3);
P3=imopen(P,sel);
axes(handles.axes1);
imshow(P);title('原图');
axes(handles.axes2);
imshow(P3);title('开运算');
function bi_Callback(hObject, eventdata, handles)
unvisable_all(handles);
global img_orig;
P=img_orig;
P=im2bw(P);
sel=strel('square',3);
P4=imclose(P,sel);
axes(handles.axes1);
imshow(P);title('原图');
axes(handles.axes2);
imshow(P4);title('闭运算');
% --------------------------------------------------------------------









function m_file_jihe_Callback(hObject, eventdata, handles)
function m_file_zengqiang_Callback(hObject, eventdata, handles)
function Untitled_22_Callback(hObject, eventdata, handles)
function Untitled_41_Callback(hObject, eventdata, handles)

function Untitled_32_Callback(hObject, eventdata, handles)
function Untitled_33_Callback(hObject, eventdata, handles)
function m_file_kingyu_Callback(hObject, eventdata, handles)
function m_file_pingyu_Callback(hObject, eventdata, handles)
function m_file_color_Callback(hObject, eventdata, handles)








function Untitled_16_Callback(hObject, eventdata, handles)


function Untitled_19_Callback(hObject, eventdata, handles)


% --- Executes on slider movement.
function slider1_Callback(hObject, eventdata, handles)
% hObject    handle to slider1 (see GCBO)
val=get(hObject,'Value');
set(handles.text1,'String',num2str(val));


global img_orig;
P=img_orig;
P=rgb2gray(P);
%h=im2bw_args;
[width,height]=size(P);
T1=val;
P1=zeros(width,height);
for i=1:width
    for j=1:height
        if(P(i,j)<T1)
            P1(i,j)=0;
        else
            P1(i,j)=1;
        end
    end
end

axes(handles.axes4);
imshow(P1);title('阈值分割');



% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider1_CreateFcn(hObject, eventdata, handles)

if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end






% --- Executes on slider movement.
function slider2_Callback(hObject, eventdata, handles)
val=get(hObject,'Value');
str=['平移',num2str(int8(val))];
set(handles.text2,'String',str);
global img_orig;
A=rgb2gray(img_orig);
A=im2double(A);
val=fix(val);
[M,N]=size(A);
 G=zeros(M,N);
 G(1+val:M,1+val:N)=A(1:M-val,1:N-val);
 axes(handles.axes4);
imshow(G);title('图2');
 B2=fft2(G);
 C2=abs(B2);
 D2=fftshift(C2);
 D2=uint8(D2);
 axes(handles.axes6);
 imshow(D2);title('图2的傅立叶变化')

% --- Executes during object creation, after setting all properties.
function slider2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider3_Callback(hObject, eventdata, handles)
val=get(hObject,'Value');
str=['旋转',num2str(val)];
set(handles.text3,'String',str);

global img_orig;
A=rgb2gray(img_orig);
A=im2double(A);
val=fix(val);

 G=imrotate(A,val);

 axes(handles.axes5);
imshow(G);title('图2');
 B2=fft2(G);
 C2=abs(B2);
 D2=fftshift(C2);
 D2=uint8(D2);
 axes(handles.axes6);
 imshow(D2);title('图2的傅立叶变化')




% --- Executes during object creation, after setting all properties.
function slider3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --------------------------------------------------------------------
function m_file_fuliye_Callback(hObject, eventdata, handles)
% hObject    handle to m_file_fuliye (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_42_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_42 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function liti_Callback(hObject, eventdata, handles)
unvisable_all(handles);
global img_orig;
P=img_orig;
P=rgb2gray(P);
axes(handles.axes2);
view(2);
mesh(P);title('三维表示');
axes(handles.axes1);
imshow(P);title('原图');




% --------------------------------------------------------------------
function sichashu_Callback(hObject, eventdata, handles)
unvisable_all(handles);
global img_orig;
P=img_orig;
P=rgb2gray(P);
I=P;
axes(handles.axes1);
imshow(P);title('原图');


I(1024,1024)=0;
S = qtdecomp(I,.27);
for dim = [1024 512 256 128 64 32 16 8 4 2 1];   
  numblocks = length(find(S==dim));   
  if (numblocks > 0)   
    [values, ~, ~] = qtgetblk(I, S, dim);
 
    values(1:end,1,:)=0;
    values(1,1:end,:)=0;
    I= qtsetblk(I,S,dim,values);
  end
end
I(end,1:end) = 0;
I(1:end,end) = 0;
figure, imshow(I,[])





% --------------------------------------------------------------------
function m_file_fuliye_pingyi_Callback(hObject, eventdata, handles)
unvisable_all(handles);
global img_orig;
A=im2double(img_orig);
B=fft2(A);
C=abs(B);
D=fftshift(C);
D=uint8(D);

set(handles.slider2,'visible','on');
set(handles.text2,'visible','on');

axes(handles.axes1);
imshow(A);title('原图');


axes(handles.axes2);
imshow(D);title('原图的傅里叶变换');
 
axes(handles.axes4);
imshow(A);title('图2');

axes(handles.axes6);
imshow(D);title('图2的傅里叶变换');



% --------------------------------------------------------------------
function m_file_fuliye_xuanzhuan_Callback(hObject, eventdata, handles)
unvisable_all(handles);
global img_orig;
A=im2double(img_orig);
B=fft2(A);
C=abs(B);
D=fftshift(C);
D=uint8(D);

set(handles.slider3,'visible','on');
set(handles.text3,'visible','on');


axes(handles.axes1);
imshow(A);title('原图');


axes(handles.axes2);
imshow(D);title('原图的傅里叶变换');
 
axes(handles.axes5);
imshow(A);title('图2');

axes(handles.axes6);
imshow(D);title('图2的傅里叶变换');
 
