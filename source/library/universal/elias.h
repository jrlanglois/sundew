#ifndef SUNDEW_ELIAS_H
#define SUNDEW_ELIAS_H

template<typename Type>
bool isBitSet (Type value, size_t index)
{
    return (value & (1u << index)) != 0;
}

int calculateIndexOfMSB (bool value)
{
    return value ? 1 : 0;
}

int calculateIndexOfMSB (unsigned char value)
{


    return (value & 0xc0) >> 6;
}

int calculateIndexOfMSB (float value)
{
    return std::log2 (value);
}

int calculateIndexOfMSB (double value)
{
    return std::log2 (value);
}

int calculateIndexOfMSB (long double value)
{
    return std::log2 (value);
}

template<typename IntegralType>
int calculateIndexOfMSB (IntegralType value)
{
    return 0;
}

namespace Elias
{
    namespace Delta
    {
        //Might have to move the template into a class-construct
        template<typename Type, const char numBitsForValue = sizeof (Type) * 8>
        void encode (std::vector<char>& resultingBits, Type* sourceBuffer, size_t length)
        {
            if (buffer == nullptr || destination == nullptr)
                return;

            for (size_t i = 0; i < length; ++i)
            {
                const Type sourceValue = sourceBuffer[i];

                Type len = 0;
                Type lengthOfLen = 0;

                for (Type temp = num; temp > 0; temp >>= 1)  // calculate 1+floor(log2(num))
                    len++;

                for (int temp = len; temp > 1; temp >>= 1)  // calculate floor(log2(len))
                    lengthOfLen++;

                for (int i = lengthOfLen; --i > 0;)
                    resultingBits.push_back (0);

                for (int i = lengthOfLen; --i >= 0;)
                    resultingBits.push_back ((len >> i) & 1);

                for (int i = len - 2; --i >= 0;)
                    resultingBits.push_back ((num >> i) & 1);
            }
        }
    }
}

#endif //SUNDEW_ELIAS_H
