//
// Created by shelhelix on 30.12.17.
//

#include "ColorBank.h"
#include "../utils/Color.h"

Color ColorBank::getObjectColor(const string &name) {
    if (name == "hero") return {0,255,0};
    if (name == "object") return {255,255,0};
    if (name == "object2") return {255,255,255};
    if (name == "hero2") return {255,0,255};
    return {0,0,0};
}
