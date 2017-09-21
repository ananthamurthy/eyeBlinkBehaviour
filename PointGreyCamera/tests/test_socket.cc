/*
 * =====================================================================================
 *
 *       Filename:  test_socket.cc
 *
 *    Description:  Test a socket. 
 *
 *    Here I create a socket and write images to it. When no one is reading,
 *
 *        Version:  1.0
 *        Created:  12/03/2016 04:17:27 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dilawar Singh (), dilawars@ncbs.res.in
 *   Organization:  NCBS Bangalore
 *
 * =====================================================================================
 */

#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/un.h>
#include <cstdlib>
#include <csignal>

using namespace std;

#define SOCK_PATH "/tmp/echo_socket"

void sig_handler( int s )
{
    cout << "Got keyboard interrupt. Removing socket" << endl;
    remove( SOCK_PATH );
    exit( 1 );
}

void write_data( int socket )
{
    char buf[50] = "Heellow duniya waalo";
    cout << "Writing some data" << endl;
    if( -1 == write( socket, (void *) buf,  10 ) )
    {
        cout <<"[ERROR] Failed to write to socket" << endl;
        cout << "\t Error was " << strerror( errno ) << endl;
    }
}

int main(void)
{
    signal( SIGINT, sig_handler );
    int s, s2, len;
    struct sockaddr_un local, remote;

    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, SOCK_PATH);
    
    remove(local.sun_path);
    len = strlen(local.sun_path) + sizeof(local.sun_family);
    if (bind(s, (struct sockaddr *)&local, len) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(s, 5) == -1) {
        perror("listen");
        exit(1);
    }

    for(;;) {
        int done;
        cout << "Waiting for a connection..." << endl;
        socklen_t t = sizeof(remote);
        if ((s2 = accept(s, (struct sockaddr *)&remote, &t)) == -1) {
            perror("accept");
            exit(1);
        }

        cout << "Connected." << endl;

        done = 0;
        do {
            write_data( s2 );

        #if 0
            n = recv(s2, str, 100, 0);
            if (n <= 0) {
                if (n < 0) perror("recv");
                done = 1;
            }

            if (!done) 
                if (send(s2, str, n, 0) < 0) {
                    perror("send");
                    done = 1;
                }
            cout << "Recieved : " << str << endl;
#endif 
        } while (!done);

        shutdown(s2, 0);
    }

    return 0;
}
