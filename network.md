# Network

Goal: learn how computer networks work: protocols, hardware, software, OS, ...

https://github.com/curl/curl/blob/master/lib/http2.c

HTTP/2 development: A hands-on approach (part 1)
https://www.youtube.com/watch?v=-KLGzMQj7EE

https://github.com/deweerdt/h2o-exercise

https://x.com/fdeweerdt

## Prompt: how does a server application can handle http 2 request?

Gemini 1.5 Flash:

**Handling HTTP/2 Requests on a Server**

When a server application needs to handle HTTP/2 requests, it needs to implement the following key features:

**1. Multiplexing:**
   - **Multiple streams:** HTTP/2 allows multiple requests and responses to be interleaved over a single TCP connection. This is achieved through the use of streams, which are independent, bidirectional flows of data within the connection.
   - **Reduced latency:** Multiplexing eliminates the head-of-line blocking problem, where a slow request can delay subsequent requests in HTTP/1.1. With HTTP/2, even if one request is slow, others can continue to be processed and sent.

**2. Header Compression:**
   - **HPACK:** HTTP/2 uses HPACK, a specialized compression algorithm for HTTP headers. This significantly reduces the overhead of sending headers, especially for repetitive headers like cookies and user-agent strings.

**3. Server Push:**
   - **Proactive resource delivery:** The server can proactively push resources to the client that it anticipates the client will need, such as images, stylesheets, and scripts referenced in an HTML document. This can reduce the number of round trips required between the client and server.

**4. Binary Framing:**
   - **Efficient data transfer:** HTTP/2 messages are framed into smaller, binary units called frames. This allows for more efficient data transfer and parsing compared to the text-based format of HTTP/1.1.

**Implementation Steps:**

1. **Support TLS 1.2 or higher:** HTTP/2 requires a secure connection using TLS.
2. **Negotiate ALPN:** During the TLS handshake, the server and client negotiate the use of HTTP/2 using Application-Layer Protocol Negotiation (ALPN).
3. **Handle streams:** The server must be able to create, manage, and close multiple streams concurrently.
4. **Implement HPACK:** The server needs to encode and decode headers using the HPACK algorithm.
5. **Support server push:** If desired, the server can implement server push to proactively send resources to the client.

**Popular Server Implementations:**

Many popular web servers, such as Nginx, Apache, and IIS, have built-in support for HTTP/2. Additionally, there are several libraries and frameworks available for various programming languages that can help you implement HTTP/2 in your own server applications.

**Example (Conceptual):**

```python
# Pseudocode for handling an HTTP/2 request

def handle_http2_request(stream):
    # Receive the request headers
    request_headers = receive_framed_data(stream)

    # Decode headers using HPACK
    decoded_headers = hpack_decode(request_headers)

    # Process the request
    response_body = process_request(decoded_headers)

    # Encode headers and body using HPACK and binary framing
    response_data = hpack_encode_and_frame(response_headers, response_body)

    # Send the response
    send_framed_data(stream, response_data)
```

By implementing these features, a server application can efficiently handle HTTP/2 requests, leading to improved performance and a better user experience.


## Curl

lib/http2.c has 3006 lines (2025-01-12)



## HTTP 2

https://github.com/h2o/h2o

https://datatracker.ietf.org/doc/html/rfc7540

    Because HTTP header fields used in a connection can contain large
   amounts of redundant data, frames that contain them are compressed
   (Section 4.3).  This has especially advantageous impact upon request
   sizes in the common case, allowing many requests to be compressed
   into one packet.

frame:  The smallest unit of communication within an HTTP/2
      connection, consisting of a header and a variable-length sequence
      of octets structured according to the frame type.

stream:  A bidirectional flow of frames within the HTTP/2 connection

Application-Layer Protocol Negotiation (ALPN)

### When server does not support it

   A server that does not support HTTP/2 can respond to the request as
   though the Upgrade header field were absent:

     HTTP/1.1 200 OK
     Content-Length: 243
     Content-Type: text/html

     ...

### Benefits

  - it allows interleaving of request and response messages on the same
   connection;
  - it uses an efficient coding for HTTP header fields;
  - it also allows prioritization of requests, letting more important
   requests complete more quickly;
  - enables more efficient processing of messages
   through use of binary message framing.

### HTTP 1.1 problems

    - It suffers from head-of-line blocking.
    -  HTTP header fields are often repetitive and verbose,
   causing unnecessary network traffic as well as causing the initial
   TCP [TCP] congestion window to quickly fill.

### Frames

The basic protocol unit in HTTP/2 is a frame.

  - HEADERS
  - DATA
  - SETTINGS
  - WINDOW_UPDATE
  - PUSH_PROMISE

### Multiplexing

Multiplexing of requests is achieved by having each HTTP request/
response exchange associated with its own stream (Section 5).
Streams are largely independent of each other, so a blocked or
stalled request or response does not prevent progress on other
streams.


### Connection Preface


```
   The client connection preface starts with a sequence of 24 octets,
   which in hex notation is:

     0x505249202a20485454502f322e300d0a0d0a534d0d0a0d0a

   That is, the connection preface starts with the string "PRI *
   HTTP/2.0\r\n\r\nSM\r\n\r\n").
```


### Steps Preface

Summary of Flow:
Client → Server: Sends connection preface (PRI * HTTP/2.0\r\n\r\nSM\r\n\r\n).
Client → Server: Sends an initial SETTINGS frame.
Server → Client: Responds with its own SETTINGS frame.
Server → Client: Sends an ACK frame for the client's SETTINGS.
Client → Server: Sends an ACK frame for the server's SETTINGS.

### Steps

  - Detect http or https
  - Check h2 or h2c
  - 
