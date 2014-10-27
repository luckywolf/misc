class GenericReader {
  Reader4k _reader4k;
  int _buf_ptr;
  char* _internal_buf;
  
public:
  int Read(int n, char* buf) {
      int count = 0;
      int remain = n;
      int buf_ptr = 0;
      while (remain > 0) {
          if (buf_ptr_ == -1) {
              int bytes_read = _reader4k.Read(_internal_buf);
              if (bytes_read == 0) { // we have exhausted the buffer
                  break;
              }
              _buf_ptr = 0;
              if (bytes_read > remain) {       
                  memcpy(buf + buf_ptr, _internal_buf, remain);
                  count += remain;
                  _buf_ptr += remain;
                  return count;
              } else {
                  remain -= bytes_read;
                  count += bytes_read;
                  _buf_ptr = -1;
                  memcpy(buf + buf_ptr, _internal_buf, bytes_read);
                  buf_ptr += bytes_read;
              }
         } else { // we still have stuff in _internal_buf, read those first
            if (4096 - _buf_ptr > remain) {
                memcpy(buf + buf_ptr, _internal_buf + _buf_ptr, remain);
                _buf_ptr += remain;
                count += remain;
                return count;
            } else {
                remain -= (4096 - _buf_ptr);
                count += (4096 - _buf_ptr);
                memcpy(but + buf_ptr, _internal_buf + _buf_ptr, 4096 - _buf_ptr);
                buf_ptr += (4096 - _buf_ptr);
                _buf_ptr = -1;
            }       
         }         
      }
    return count;
  }  
};
