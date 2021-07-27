%% algoritmo de convolucion circular
clc; clear all; close all;

N=9;

%asigno x[n] e y[n]
x=[4 2-3j 3+2j -4+6j 8-7j 8+7j -4-6j 3-2j 2+3j];
y=[4 2-3j 3+2j -4+6j 8-7j 8+7j -4-6j 3-2j 2+3j];

z=circonv(N,x,y)