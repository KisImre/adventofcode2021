/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include <fstream>
#include <iostream>
#include <list>

class BinaryStream {
    public:
        BinaryStream() = default;

        BinaryStream(uint8_t *data, size_t length) : data(data), length(length * 8), index(0) {
        }

        bool get(uint32_t length, uint64_t *res) {
            uint32_t result = 0;

            for (uint32_t bits = 0; bits < length; bits++) {
                if (index >= this->length) {
                    return false;
                }

                result <<= 1;
                result |= (data[index / 8] >> (7 - (index % 8))) & 0x01;
                index++;
            }

            *res =  result;
            return true;
        }

        BinaryStream get_subpacket(uint32_t length) {
            BinaryStream bs;

            if (this->index + length > this->length) {
                return bs;
            }

            bs.data = this->data;
            bs.length = this->index + length;
            bs.index = this->index;

            this->index += length;

            return bs;
        }

    private:
        uint8_t *data;
        size_t length;
        uint32_t index;
};

bool parse_packet(uint32_t level, BinaryStream &bs, uint32_t *version, uint64_t *result) {
    uint64_t temp = 0;

    if (!bs.get(3, &temp)) {
        return false;
    }

    *version += temp;

    uint64_t type = 0;
    if (!bs.get(3, &type)) {
        return false;
    }

    if (type == 4) {
        uint64_t value = 0;
        *result = 0;
        do {
            if (!bs.get(5, &value)) {
                return false;
            }
            *result <<= 4;
            *result |= value & 0x0f;
        } while(value & 0x10);
    } else {
        uint64_t len_type = 0;
        std::list<uint64_t> subpacket_results;
        uint64_t subpacket_result = 0;

        if (bs.get(1, &len_type)) {
            if (!len_type) {
                uint64_t subpacket_length = 0;
                if (!bs.get(15, &subpacket_length)) {
                    return false;
                }

                BinaryStream subpacket_bs = bs.get_subpacket(subpacket_length);
                while (parse_packet(level + 1, subpacket_bs, version, &subpacket_result)) {
                    subpacket_results.push_back(subpacket_result);
                }
            } else {
                uint64_t subpacket_count = 0;
                if (!bs.get(11, &subpacket_count)) {
                    return false;
                }

                for (uint32_t i = 0; i < subpacket_count; i++) {
                    if (!parse_packet(level + 1, bs, version, &subpacket_result)) {
                        return false;
                    };
                    subpacket_results.push_back(subpacket_result);
                }
            }
        } else {
            return false;
        }

        switch (type) {
            case 0:
                // sum
                *result = 0;
                for (auto a : subpacket_results)
                    *result += a;
                break;

            case 1:
                // product
                *result = 1;
                for (auto a : subpacket_results)
                    *result *= a;
                break;

            case 2:
                // minimum
                *result = 0xffffffffffffffff;
                for (auto a : subpacket_results)
                    *result = std::min(*result, a);
                break;

            case 3:
                // maximum
                *result = 0;
                for (auto a : subpacket_results)
                    *result = std::max(*result, a);
                break;

            case 5:
                // greater than
                *result = (subpacket_results.front() > subpacket_results.back()) ? 1 : 0;
                break;

            case 6:
                // less than
                *result = (subpacket_results.front() < subpacket_results.back()) ? 1 : 0;
                break;

            case 7:
                // equal
                *result = (subpacket_results.front() == subpacket_results.back()) ? 1 : 0;
                break;

            default:
                std::cout << "unknown packet " << type << std::endl;
                break;
        }
    }

    return true;
}

uint8_t from_hex(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    return c - 'A' + 10;
}

int main() {
    std::fstream input("input");
    uint8_t buffer[1024] = {0};

    uint32_t buffer_index = 0;
    for (char h = 0, l = 0; input >> h >> l; ) {
        buffer[buffer_index++] = (from_hex(h) << 4) | from_hex(l);
    }

    BinaryStream bs(buffer, buffer_index);
    uint32_t version = 0;
    uint64_t res = 0;

    parse_packet(0, bs, &version, &res);

    std::cout << version << std::endl;
    std::cout << res << std::endl;
}
