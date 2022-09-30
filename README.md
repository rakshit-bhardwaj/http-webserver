# http-webserver
A http webserver made using socket programming in C language.

The server creates a TCP socket and listens for requests on it until a browser client sends a request.
after connection is formed the server will process the client request and send the correct webpage accordingly.
Webpages can be added or removed using the multiple if loops.

The conf.txt file contains port number and directory of webpages. This config file will pe parsed before server creates socket.


char webpage[15000] = 
        "HTTP/1.1 200 OK\r\n"
        "Content-length: 800\r\n"
        "Content-Type: text/html\r\n"
        "Connection: close\r\n\r\n";
        
This response gets concatenated with the html code client has requested for.


![scrnshot](https://user-images.githubusercontent.com/100684015/193165092-7cf89cc8-7ac4-408d-afdc-c4348698a9a1.jpeg)
