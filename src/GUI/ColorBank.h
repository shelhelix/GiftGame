//
// Created by shelhelix on 30.12.17.
//

#ifndef GIFTGAME_COLORBANK_H
#define GIFTGAME_COLORBANK_H

#include <string>
#include "../utils/Color.h"

using namespace std;


class ColorBank {
public:
    Color getObjectColor(const string &name);
};


#endif //GIFTGAME_COLORBANK_H
