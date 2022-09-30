# http-webserver
A http webserver made using socket programming in C language.

The server creates a TCP socket and listens for requests on it until a browser client sends a request.
after connection is formed the server will process the client request and send the correct webpage accordingly.
Webpages can be added or removed using the multiple if loops.

The conf.txt file contains port number and directory of webpages. This config file will pe parsed before server creates socket.


char webpage[15000] = <br>
     <t>"HTTP/1.1 200 OK\r\n" <br>
     <t>"Content-length: 800\r\n" <br>
     <t>"Content-Type: text/html\r\n" <br>
     <t>"Connection: close\r\n\r\n"; <br>
        
This response gets concatenated with the html code client has requested for.


![scrnshot](https://user-images.githubusercontent.com/100684015/193165718-99f69a0c-503f-4e30-9454-16c4312199f6.jpeg)

