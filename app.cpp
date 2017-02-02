//
// Created by vagrant on 18.11.16.
//

#include "app.h"
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <system_error>
#include <unistd.h>
#include <vector>
#include <string>
#include <sstream>
#include <string.h>
#include <stdlib.h>
using namespace std;
app::app()
{
    std::cout<<"============================="<<std::endl;
    std::cout<<"welcome to our final project"<<std::endl;
    std::cout<<"============================="<<std::endl;
}

app::~app()
{
    std::cout<<"============================="<<std::endl;
    std::cout<<"closing the project"<<std::endl;
    std::cout<<"============================="<<std::endl;
}

std::string app::start()
{
    string command_str;
    cout << "\nvbash>>";
    getline (cin, command_str);
    cout << "Command Entered: " << command_str << endl;
    std::vector < std::string > command_options;
    //Read the command string till the end of the line.

    // With the "exit" command it exits the program
    while (command_str != "exit")
    {
        return command_str;
    }
    return "exit";
}

int app::execute(std::string str)
{
    pid_t w;
    int status;
    istringstream iss (str);
    std::vector < string > command;
    //Command string can contain the main command and a number of command line arguments.
    do
    {
        string sub;
        iss >> sub;
        command.push_back (sub);
    }
    while (iss);
    char **args = (char **) malloc (command.size () * sizeof (char *));
    for (int i = 0; i < command.size (); i++)
    {
        args[i] = strdup (command[i].c_str ());

    }
    args[command.size ()-1] = 0;
    w=fork();
    //fork here to start a child process
    if(w==0){
        //in the child process, let's do the execvp
        std::cout<<"Command Output:"<<std::endl;
        if(execvp(args[0],args)<=0){
            //do execvp here and judge whether the function ran correctly.
            //What's more, I know that execvp could be done without a if function, but I prefer
            //to use if here to make it more reasonable
            std::cout<<"\nExec Failed "<<errno<<"\n";
            //if there's anything wrong with execvp, print exec failed
            exit(1);
            //the child process will exit 1 if there's something wrong with Exec
        }
    }
    else if(w<0){
        std::cout<<"\nFork Failed "<<errno<<"\n";
        //print error information if fork failed
    }
    else{
        int retvalue = 0;
        while (retvalue != w)
        {
            status = 0;
            retvalue = waitpid (w, &status, 0);
            //waitpid here and give the pid value of child process to retvalue
            if (retvalue < 0)
                //if there's something wrong with waitpid, we will do the following things
            {
                char buffer[256];
                strerror_r (errno, buffer, 256);
                printf ("error occured %s\n", buffer);
                //return the error information if waitpid failed.
                break;
            }
            else
            {
                if (WIFEXITED (status))
                    //check if the child process terminated by itself
                {
                    if(WEXITSTATUS(status)==0){
                        //check if the child process exited in a correct way
                        //if the exit code of the child process is 0, the child exited successfully
                        std::cout<<"\nChild Exited Successfully\n";
                        //print if child process exit correctly
                    }
                    else{
                        //if the exit code is not 0, this function would be executed
                        int exitcode=WEXITSTATUS(status);
                        //get the exit code
                        std::cout<<"\nChild Self Terminated With Exit Code "<<exitcode<<"\n";
                        //return the exitcode if child process exited in a wrong way
                    }
                }
                else if (WIFSIGNALED (status))
                    //check if the child process is terminated by a signal
                {
                    int signalsent=WTERMSIG(status);
                    //if so, get the signal code
                    std::cout<<"\nChild Terminated Due to Signal "<<signalsent<<"\n";
                    //print the signal code
                }
            }
        }
    }
}
