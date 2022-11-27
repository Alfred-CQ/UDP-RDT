#ifndef __UTILS_H__
    #define __UTILS_H__

    #include "main_header.h"

    namespace utils
    {
       /** Checksum **/
        static inline uint make_Checksum(const char data[MAX_SEGMENT_SIZE + 1])
        {
            uint checksum{0};

            for (size_t idx = 0; idx < MAX_SEGMENT_SIZE; ++idx)
                checksum += int(data[idx]);

            return (checksum % 7);
        }

        static inline bool test_Checksum(const char data[MAX_SEGMENT_SIZE + 1], uint recv_checksum)
        {
            return (make_Checksum(data) == recv_checksum);
        }

        static inline string complete_Bytes(uint number, uint size)
        {
            string numb = std::to_string(number);
            uint complete = size - numb.size();

            while(complete--)
                numb.insert(numb.begin(), '0');

            return numb;
        }
        
    }

#endif // !__UTILS_H__