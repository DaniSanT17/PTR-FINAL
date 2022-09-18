close all, clear all, clc
Out = readtable("dados.txt");
figure();
plot(Out{:,2},Out{:,3});
title("X por Y");

figure();
plot(Out{:,1},Out{:,2});
title("X por t");

figure();
plot(Out{:,1},Out{:,3});
title("Y por t");

figure();
plot(Out{:,1},Out{:,4});
title("Theta por t");