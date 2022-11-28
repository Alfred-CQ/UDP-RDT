#ifndef __UTILS_H__
    #define __UTILS_H__

    #include "main_header.h"

    namespace utils
    {
       /** Checksum **/
        static inline uint make_Checksum(string data)
        {
            uint checksum{0};

            for (char character : data)
                checksum += int(character);

            return (checksum % 7);
        }

        static inline bool test_Checksum(string data, uint recv_checksum)
        {
            return (make_Checksum(data) == recv_checksum);
        }

        static inline string complete_Bytes(uint number, uint n)
        {
            string numb = std::to_string(number);
            uint complete = n - numb.size();

            while(complete--)
                numb.insert(numb.begin(), '0');

            return numb;
        }
        
        static inline void fill_Zeros(char* data, uint padding)
        {
            for ( size_t j = MAX_SEGMENT_SIZE - padding; j < MAX_SEGMENT_SIZE; ++j)
            {
                data[j] = '0';
            }
        }
    }

#endif // !__UTILS_H__