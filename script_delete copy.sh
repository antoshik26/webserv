curl -X GET http://localhost:7000/ -H "Transfer-Encoding: chunked" --data "9\r\n chunk 1,\r\n7\r\nchunk 2\r\n0\r\n\r\n"
