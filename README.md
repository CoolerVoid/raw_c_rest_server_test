# raw_c_rest_server_test
Very simple rest server to test payloads, TLS libraries and soon.

To run:
```
$ git clone https://github.com/CoolerVoid/raw_c_rest_server_test
$ cd raw_c_rest_server_test
$ make clean
$ make
$ bin/rest_server
```
So to test follow this  example:
```
In client side to send a POST:
$ curl -k -X POST -d "apple=2&banana=10" https://127.0.0.1:20100/test/234234234
{"result": "/test/234234234"}

--- result on server side
t$ bin/rest_server 

Vulnerable simple REST server
 Listening : https://127.0.0.1:20100
---
SERVER recv:
 POST /test/234234234 HTTP/1.1
Host: 127.0.0.1:20100
User-Agent: curl/7.68.0
Accept: */*
Content-Length: 17
Content-Type: application/x-www-form-urlencoded

apple=2&banana=10
------


```

Note you can change TLS certs in directory /cert.
