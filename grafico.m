close all, clear all, clc
Out = readtable("dados.txt");

figure();
plot(Out{:,2},Out{:,3});
title("XRef x Yref");

figure();
plot(Out{:,4},Out{:,5});
title("Xm x Ym");

figure();
plot(Out{:,6},Out{:,7});
title("Xmdot x Ymdot");

figure();
plot(Out{:,8},Out{:,9});
title("V");

figure();
plot(Out{:,10},Out{:,11});
title("U");

figure();
plot(Out{:,12},Out{:,13});
title("Xc vs Yc");

figure();
plot(Out{:,1},Out{:,12});
title("Xc vs t");

figure();
plot(Out{:,1},Out{:,13});
title("Yc vs t");

figure();
plot(Out{:,1},Out{:,14});
title("Theta vs t");

figure();
plot(Out{:,15},Out{:,16});
title("Xdotc vs Ydotc");

figure();
plot(Out{:,18},Out{:,19});
title("Y final");