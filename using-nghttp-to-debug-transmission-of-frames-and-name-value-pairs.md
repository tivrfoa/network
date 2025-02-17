`nghttp -nv https://idealcircular.com`


```
[  0.168] Connected
The negotiated protocol: h2
[  0.340] send SETTINGS frame <length=12, flags=0x00, stream_id=0>
          (niv=2)
          [SETTINGS_MAX_CONCURRENT_STREAMS(0x03):100]
          [SETTINGS_INITIAL_WINDOW_SIZE(0x04):65535]
[  0.340] send PRIORITY frame <length=5, flags=0x00, stream_id=3>
          (dep_stream_id=0, weight=201, exclusive=0)
[  0.340] send PRIORITY frame <length=5, flags=0x00, stream_id=5>
          (dep_stream_id=0, weight=101, exclusive=0)
[  0.340] send PRIORITY frame <length=5, flags=0x00, stream_id=7>
          (dep_stream_id=0, weight=1, exclusive=0)
[  0.340] send PRIORITY frame <length=5, flags=0x00, stream_id=9>
          (dep_stream_id=7, weight=1, exclusive=0)
[  0.340] send PRIORITY frame <length=5, flags=0x00, stream_id=11>
          (dep_stream_id=3, weight=1, exclusive=0)
[  0.340] send HEADERS frame <length=40, flags=0x25, stream_id=13>
          ; END_STREAM | END_HEADERS | PRIORITY
          (padlen=0, dep_stream_id=11, weight=16, exclusive=0)
          ; Open new stream
          :method: GET
          :path: /
          :scheme: https
          :authority: idealcircular.com
          accept: */*
          accept-encoding: gzip, deflate
          user-agent: nghttp2/1.64.0
[  0.498] recv SETTINGS frame <length=6, flags=0x00, stream_id=0>
          (niv=1)
          [SETTINGS_MAX_CONCURRENT_STREAMS(0x03):100]
[  0.499] recv WINDOW_UPDATE frame <length=4, flags=0x00, stream_id=0>
          (window_size_increment=2147418112)
[  0.499] recv SETTINGS frame <length=0, flags=0x01, stream_id=0>
          ; ACK
          (niv=0)
[  0.499] send SETTINGS frame <length=0, flags=0x01, stream_id=0>
          ; ACK
          (niv=0)
[  0.508] recv (stream_id=13) :status: 200
[  0.508] recv (stream_id=13) last-modified: Sat, 15 Jul 2023 21:37:10 GMT
[  0.508] recv (stream_id=13) accept-ranges: bytes
[  0.508] recv (stream_id=13) vary: Accept-Encoding
[  0.508] recv (stream_id=13) content-encoding: gzip
[  0.508] recv (stream_id=13) content-length: 1117
[  0.508] recv (stream_id=13) content-type: text/html
[  0.508] recv (stream_id=13) date: Mon, 17 Feb 2025 00:39:55 GMT
[  0.508] recv (stream_id=13) server: Apache
[  0.508] recv HEADERS frame <length=95, flags=0x04, stream_id=13>
          ; END_HEADERS
          (padlen=0)
          ; First response header
[  0.508] recv DATA frame <length=1117, flags=0x01, stream_id=13>
          ; END_STREAM
[  0.508] send GOAWAY frame <length=8, flags=0x00, stream_id=0>
          (last_stream_id=0, error_code=NO_ERROR(0x00), opaque_data(0)=[])
```
