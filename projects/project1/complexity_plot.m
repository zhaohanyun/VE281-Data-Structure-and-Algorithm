x=[50 500 2000 5000 7500 10000 20000];
bubble=[49 4928 76801 484939 1075136 1946907 7654933]./3;
selection=[33 2743 42773 283599 594468 1050237 4710305]./3;
insertion=[7 726 11546 72485 160461 280369 1157445];
merge=[14 195 895 2270 3422 4673  9885]./3;
qs_inplace=[70 1338 7964 28779 57581 95704 196804]./3;
qs_extra=[101 1212 4934 13911 19511 26656 54740]./3;
stdsort=[6 92 449 1213 1944 2775 5718];


Bubble = spcrv([[x(1) x x(end)];[bubble(1) bubble bubble(end)]],3,15000);

%Selection = spcrv([[x(1) x x(end)];[selection(1) selection selection(end)]]);
%plot(Bubble(2,:));hold on;
%plot(Selection(2,:));hold on;
%axis([0 20000 0 100000]);
plot(x,bubble);hold on;
plot(x,selection);hold on;
plot(x,insertion);hold on;
plot(x,merge); hold on;
plot (x,qs_inplace); hold on;
plot(x, qs_extra);hold on;
plot(x,stdsort);hold on;legend('bubble','selection','insertion','merge','qs inplace','qs extra','stdsort');
axis([0 20000 0 100000]);