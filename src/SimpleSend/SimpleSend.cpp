/* 
    Simple example of sending an OSC message using oscpack.
*/

#include <windows.h>
#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

// for oscpack library
#ifdef _DEBUG
#pragma comment(lib, "liboscpackD.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winmm.lib")
#else
#pragma comment(lib, "liboscpack.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winmm.lib")
#endif

#define ADDRESS "127.0.0.1"
#define PORT 7000

#define OUTPUT_BUFFER_SIZE 1024

int main(int argc, char* argv[])
{
    UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, PORT ) );
    
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
    
    p << osc::BeginBundleImmediate
        << osc::BeginMessage( "/test1" ) 
            << true << 23 << (float)3.1415 << "hello" << osc::EndMessage
        << osc::BeginMessage( "/test2" ) 
            << true << 24 << (float)10.8 << "world" << osc::EndMessage
        << osc::EndBundle;
    
    transmitSocket.Send( p.Data(), p.Size() );
}

