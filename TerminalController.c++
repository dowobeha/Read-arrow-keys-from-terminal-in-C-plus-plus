/* Copyright 2024 Lane Schwartz <dowobeha@gmail.com>
 * 
 * Permission is hereby granted, free of charge, 
 *   to any person obtaining a copy of this software 
 *   and associated documentation files (the “Software”), 
 *   to deal in the Software without restriction, 
 *   including without limitation the rights to use, 
 *   copy, modify, merge, publish, distribute, sublicense, 
 *   and/or sell copies of the Software, and to permit 
 *   persons to whom the Software is furnished to do so, 
 *   subject to the following conditions:
 *
 * The above copyright notice and this permission notice 
 *   shall be included in all copies or substantial portions 
 *   of the Software.
 * 
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY 
 *   KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
 *   THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
 *   PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 *
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE 
 *   LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
 *   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
 *   SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "TerminalController.h"

namespace TTY {

    namespace TerminalInterfaceLibrary {

        // Include this C header, but wrap its functions in this namespace
        #include <termios.h>  // Provides tcgetattr, tcsetattr, and struct termios

        // Define Configuration as a nicer name for the C-style struct termios
#if __cplusplus >= 201103L
        // Use the C++-11 alias syntax if that's available
        using Configuration = struct termios; 
#else
        // Otherwise grudgingly use the older C++-98 typedef syntax
        typedef struct termios Configuration; 
#endif

    } // End namespace TerminalInterfaceLibrary

    class Controller {

    public:
        Controller();
        ~Controller();
        void setCanonicalInput(bool b);
        void setEchoInput(bool b);
        void setInterruptSignals(bool b);
        void setAttributes();
        void reset();

    private:
        TerminalInterfaceLibrary::Configuration actualTTY;
        TerminalInterfaceLibrary::Configuration originalTTY;
    };

}



TTY::Controller::Controller() {
    TTY::TerminalInterfaceLibrary::tcgetattr(0, &actualTTY);
    originalTTY = actualTTY;
}

namespace TTY {
    namespace TerminalInterfaceLibrary {
        // Include this C header, but wrap its functions in this namespace
        #include "stdio.h" // Provides setvbuf, which we need below

    }
}

void TTY::Controller::setAttributes() {
    TerminalInterfaceLibrary::tcsetattr(0, TCSANOW, &actualTTY);
    TerminalInterfaceLibrary::setvbuf(TerminalInterfaceLibrary::stdin, NULL, _IONBF, 0);
}

TTY::Controller::~Controller() {
    TTY::TerminalInterfaceLibrary::tcsetattr(0, TCSANOW, &originalTTY);
}

void TTY::Controller::reset() {
    actualTTY = originalTTY;
    TTY::TerminalInterfaceLibrary::tcsetattr(0, TCSANOW, &actualTTY);
}

void TTY::Controller::setCanonicalInput(bool b) {
    if (b)
    {
        actualTTY.c_lflag &= ICANON;
    }
    else
    {
        actualTTY.c_lflag &= ~ICANON;
    }
}

void TTY::Controller::setEchoInput(bool b) {
    if (b)
    {
        actualTTY.c_lflag &= ECHO;
    }
    else
    {
        actualTTY.c_lflag &= ~ECHO;
    }
}

void TTY::Controller::setInterruptSignals(bool b) {
    if (b)
    {
        actualTTY.c_lflag &= ISIG;
    }
    else
    {
        actualTTY.c_lflag &= ~ISIG;
    }
}

namespace TTY {

    // This is the function you are looking for
    void recognizeIndividualKeyPresses(bool enable) {

        static TTY::Controller controller;

        if (enable) {
            controller.setCanonicalInput(false);
            controller.setEchoInput(false);
            controller.setInterruptSignals(false);
            controller.setAttributes();
        } else {
            controller.reset();
        }
    }
}
