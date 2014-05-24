/*
 * STS - Simple Time System, common protocol
 * Ascher, Lamb, Viehberger
 */

#ifndef sts_h
#define sts_h

void sts_start_server();

const char* sts_request_time_from_server(const char* host_name);

#endif
