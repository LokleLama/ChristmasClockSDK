#include "ChristmasClock.hpp"
#include "ColorGRBa.hpp"
#include "IRErrorCorrection.hpp"
#include <iostream>

namespace ChristmasClock{

ChristmasClock::ChristmasClock() :
    _led(pio0),
    _seg(_led),
    _tx(pio0),
    _time(180)
{
    _seg.SetGain(0x0F);
}

void ChristmasClock::Update() {
    if(_time > 60){
        _seg.SetForeground(ColorGRBa::GREEN);
    }else if(_time > 30){
        _seg.SetForeground(ColorGRBa::YELLOW);
    }else{
        _seg.SetForeground(ColorGRBa::RED);
    }
    _seg.SetTime(_time);
    _tx.Transmit(_time);
    _seg.Update();

    _time--;
    if(_time < -360){
        _time = 180;
    }
}
}
