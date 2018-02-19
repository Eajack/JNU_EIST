%加载测试的成套“伪FRF”谱Hp（k）数据
load('Hca1ca1.mat')
f=a0;
w=2*pi*f;
hca1ca1=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hca1ca2.mat')
hca1ca2=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hca2ca1.mat')
hca2ca1=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hca2ca2.mat')
hca2ca2=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hcb1cb1.mat')
hcb1cb1=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hcb1cb2.mat')
hcb1cb2=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hcb1ib1.mat')
hcb1ib1=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hcb1ib2.mat')
hcb1ib2=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hcb2cb1.mat')
hcb2cb1=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hcb2cb2.mat')
hcb2cb2=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hcb2ib1.mat')
hcb2ib1=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hcb2ib2.mat')
hcb2ib2=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hoa1ca1.mat')
hoa1ca1=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hoa1ca2.mat')
hoa1ca2=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hoa2ca1.mat')
hoa2ca1=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hoa2ca2.mat')
hoa2ca2=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hsca1ca1.mat')
hsca1ca1=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hsca1ca2.mat')
hsca1ca2=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hsca1cb1.mat')
hsca1cb1=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hsca1cb2.mat')
hsca1cb2=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hsca2ca1.mat')
hsca2ca1=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hsca2ca2.mat')
hsca2ca2=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hsca2cb1.mat')
hsca2cb1=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hsca2cb2.mat')
hsca2cb2=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hscb1cb1.mat')
hscb1cb1=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hscb1cb2.mat')
hscb1cb2=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hscb2cb1.mat')
hscb2cb1=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hscb2cb2.mat')
hscb2cb2=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hsoa1ib1.mat')
hsoa1ib1=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hsoa1ib2.mat')
hsoa1ib2=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hsoa2ib1.mat')
hsoa2ib1=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
load('Hsoa2ib2.mat')
hsoa2ib2=[a4+i*a5];
clear a0 a1 a2 a3 a4 a5 a6 a7 a8
for k=2:401;
    %构成FRF矩阵
    Hcaca=[hca1ca1(k),hca1ca2(k);hca2ca1(k),hca2ca2(k)]/(-w(k)^2);
    Hcbcb=[hcb1cb1(k),hcb1cb2(k);hcb2cb1(k),hcb2cb2(k)]/(-w(k)^2);
    Hcbib=[hcb1ib1(k),hcb1ib2(k);hcb2ib1(k),hcb2ib2(k)]/(-w(k)^2);
    Hoaca=[hoa1ca1(k),hoa1ca2(k);hoa2ca1(k),hoa2ca2(k)]/(-w(k)^2);
    Hsoaib=[hsoa1ib1(k),hsoa1ib2(k);hsoa2ib1(k),hsoa2ib2(k)]/(-w(k)^2);
    Hscaca=[hsca1ca1(k),hsca1ca2(k);hsca2ca1(k),hsca2ca2(k)]/(-w(k)^2);
    Hscacb=[hsca1cb1(k),hsca1cb2(k);hsca2cb1(k),hsca2cb2(k)]/(-w(k)^2);
    Hscbcb=[hscb1cb1(k),hscb1cb2(k);hscb2cb1(k),hscb2cb2(k)]/(-w(k)^2);
    %计算Ks11(k)和Ks22(k)
    Ksd=inv(Hscaca*transpose(inv(Hscacb))*Hscbcb-Hscacb);
    Ks11d(k)=Ksd(1,1);Ks22d(k)=Ksd(2,2);
    Ksind=inv(Hcbib*transpose(inv(Hsoaib))*Hoaca-Hcaca-Hcbcb);
    Ks11ind(k)=Ksind(1,1);Ks22ind(k)=Ksind(2,2);
    %计算各分析频率线fk的装配耦合动刚度谱矩阵
    Ksm11(k)=197800+i*w(k)*1344.2;
    Ksm22(k)=189300+i*w(k)*1625.4;
end
%绘制半对数频谱图
subplot(2,1,1);
semilogy(f,abs(Ks11d),'k--',f,abs(Ks11ind),'r-o',f,abs(Ksm11),'b-');
subplot(2,1,2);
semilogy(f,abs(Ks22d),'k--',f,abs(Ks22ind),'r-o',f,abs(Ksm22),'b-');