#ifndef _OFSOL_H_
#define _OFSOL_H_

#pragma once
#define SOL_ALL_SAFETIES_ON 1

class ofApp;

#include "sol.hpp"
#include "ofMain.h"

class ofSol {

public:

    void create_interop(sol::state& lua, ofApp& app);
    void blendMode(std::string mode);

};

#endif