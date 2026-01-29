#pragma once
#ifndef RUUTU_H
#define RUUTU_H

class Ruutu
{
public:
    Ruutu(int rivi, int pRivi);
    Ruutu() : pRivi(-1), rivi(-1) {}
    int getRivi();
    int getpRivi();

private:
    int pRivi;
    int rivi;
};

#endif