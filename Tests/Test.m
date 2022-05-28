fs = 44100;
duration = 5;
t = 0:1/fs:duration-1/fs;
A = 1;
f = 5000;
s1 = A * sin(2*pi*f*t);

y1 = QuantiseAudio(s1,16,1,-1,0,1);

plotSpectrum(y1,fs,1,1);
print "plots/s1_spectrum.png"

xlim([20 22050]);
ylim([-140 0]);

audiowrite('audio/sine.wav',y1,fs);
