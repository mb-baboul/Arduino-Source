/*  Abstract Logger
 *
 *  From: https://github.com/PokemonAutomation/Arduino-Source
 *
 */

#ifndef PokemonAutomation_AbstractLogger_H
#define PokemonAutomation_AbstractLogger_H

#include <string>
#include <vector>
#include "Color.h"
#include "Time.h"

namespace PokemonAutomation{


class Logger{
public:
    virtual void log(const std::string& msg, Color color = Color()) = 0;
    virtual void log(std::string&& msg, Color color = Color()){
        log((const std::string&)msg, color);
    }
    virtual void log(const char* msg, Color color = Color()){
        log(std::string(msg), color);
    }

    virtual std::vector<std::string> get_last() const{
        return {};
    }
};


}
#endif
