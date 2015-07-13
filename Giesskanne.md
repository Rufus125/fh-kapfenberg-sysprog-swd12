Gießkanne (File-Distributor)

Team: Christoph Mitteregger, Philipp Temmel, Elena Wendl
Link: https://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/trunk/project/Project_Giesskanne

# Background information #

Gießkanne is a client-server-architecture project written in C++ which allows clients to register as listeners to a server which serves as the file dispatcher in an internal network. The clients and the server communicate via TCP/IP (socket-syscall) and the clients can register/deregister themselves at the server which is always up and running. The server keeps track of all registered clients via an internal list of the clients' IP addresses.

The server has a pool of files in a predefined folder and performs checks on a regular basis if any of these files changed. This is accomplished by performing md5-checksums on each file of the current filepool and comparing the calculated m5d-checksum with the md5 checksums which have been calculated at the last check. These are stored in a separate file on the server and provide the association between the filenames and md5 checksums. The server creates a new TCP/IP connection to each client and transfers all modified files to the clients in a loop. If a client can't be reached (network problem or client program terminated), this client is omitted for the current file update. After all clients have been updated with the modified files, the server updates the file which holds the association between the filenames and the md5-checksums which forms the basis for any future checks.