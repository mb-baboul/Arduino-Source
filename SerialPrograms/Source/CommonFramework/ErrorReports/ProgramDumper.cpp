/*  Program Dumper
 *
 *  From: https://github.com/PokemonAutomation/Arduino-Source
 *
 */

#include "ProgramDumper.h"


#if _WIN32 && _MSC_VER
#include "ProgramDumper_Windows.tpp"

#else
void setup_crash_handler(){
    //  Not supported
}
bool program_dump(Logger* logger, const std::string& filename){

}
#endif
