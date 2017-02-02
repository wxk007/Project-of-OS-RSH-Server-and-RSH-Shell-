#include <iostream>
#include <cstring>
#include "app.h"
#include "PracticalSocket.h" // For Socket and SocketException

int main() {
    //the following variables is for TCP socket client
    std::string servAddress = "localhost";
    char* echoString=NULL;
    unsigned short echoServPort=1234;
    //the following variables is for getting command
    std::string command;
    //TCPSocket sock (servAddress, echoServPort);
    app a;
    command=a.start();
    while(command!="exit")
    {
        //In the later version, I should replce the a.execte with socket send
        // and the execute function should be done in the socketserver
        echoString=(char*)&command;
        int echoStringLen = strlen (echoString);
        try
        {
            //create socket and send the command here.


        }
        catch (SocketException &e)
        {
            cerr << e.what () << endl;
            exit (1);
        }
        a.execute(command);
        command=a.start();
    }
    return 0;

}