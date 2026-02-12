/*
    Initial author: Convery (tcn@hedgehogscience.com)
    Started: 08-01-2018
    License: MIT
*/

#pragma once
#include "../Stdinclude.hpp"

class Bytebuffer
{
    enum Bytebuffertype : uint8_t
    {
        BB_NONE = 0, BB_BOOL = 1, BB_SINT8 = 2, BB_UINT8 = 3,
        BB_SINT16 = 4, BB_UINT16 = 5, BB_SINT32 = 6, BB_UINT32 = 7,
        BB_SINT64 = 8, BB_UINT64 = 9, BB_FLOAT32 = 10, BB_FLOAT64 = 11,
        BB_STRING_WIDE = 12, BB_STRING_ASCII = 13, BB_BLOB = 14, BB_ARRAY = 15, BB_MAX
    };

    using Type_t = std::pair<Bytebuffertype, void *>;

    std::unique_ptr<uint8_t[]> Internalbuffer;
    std::vector<Type_t> Internalvariables;
    size_t Internaliterator;
    size_t Internalsize;

    bool Readdatatype(Bytebuffertype Type);
    bool Writedatatype(Bytebuffertype Type);
    bool Rawread(size_t Readcount, void *Buffer = nullptr);
    bool Rawwrite(size_t Writecount, const void *Buffer = nullptr);

public:
    Bytebuffer(size_t Datasize, const void *Databuffer);
    void Setbuffer(std::vector<uint8_t> &Data);
    Bytebuffer(std::vector<uint8_t> &Data);
    Bytebuffer(const Bytebuffer &Right);
    void Setbuffer(std::string &Data);
    Bytebuffer(Bytebuffer &&Right);
    Bytebuffer(std::string &Data);
    Bytebuffer();

    bool Setposition(size_t Newposition);
    const size_t Getposition();
    std::string to_string();
    const uint8_t *Data();
    const uint8_t Peek();
    const size_t Size();
    void Deserialize();
    void Rewind();
    void Clear();

    template <typename Type> Type Read(bool Typechecked = true);
    template <typename Type> bool Read(Type &Buffer, bool Typechecked = true);
    template <typename Type> bool Write(const Type Value, bool Typechecked = true);

    template <typename Type> bool Readarray(std::vector<Type> &Data);
    template <typename Type> bool Writearray(std::vector<Type> Data);

    template <typename Type> Bytebuffer &operator += (const Type &Right) noexcept;
    template <typename Type> Bytebuffer &operator += (const Type *Right) noexcept;
    template <typename Type> Bytebuffer &operator << (const Type &Right) noexcept;
    template <typename Type> Bytebuffer &operator << (const Type *Right) noexcept;

    Bytebuffer &operator += (const Bytebuffer &Right) noexcept;
    Bytebuffer &operator + (const Bytebuffer &Right) noexcept;
    Bytebuffer &operator = (const Bytebuffer &Right) noexcept;
    Bytebuffer &operator = (Bytebuffer &&Right) noexcept;
    bool operator == (const Bytebuffer &Right) noexcept;
    Type_t &operator [](size_t Index) noexcept;
};
