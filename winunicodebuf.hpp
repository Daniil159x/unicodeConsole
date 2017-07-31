// UTF-8 with BOM

/*
    https://alfps.wordpress.com/2011/12/08/unicode-part-2-utf-8-stream-mode/
*/

#ifndef WINUNICODEBUF_HPP
#define WINUNICODEBUF_HPP
#ifdef WIN32

#include <Windows.h>
#include <io.h>
#include <fcntl.h>

#include <streambuf>

namespace details {
    class winUnicodeBuf : public std::wstreambuf
    {
        using Base = std::wstreambuf;
        using Traits = Base::traits_type;

    public:
        winUnicodeBuf(const Base& buf) : Base(std::move(buf)), m_buffer() {}

    protected:
        virtual std::streamsize xsgetn(wchar_t* pBuffer, std::streamsize n) override
        {
            const wchar_t ctrlZ = wchar_t(1 + ('Z' - 'A'));

            DWORD nCharactersRead = 0;

            const bool readSucceeded = !!ReadConsoleW(
                GetStdHandle(STD_INPUT_HANDLE), pBuffer,
                static_cast<DWORD>(n), &nCharactersRead, nullptr
            );

            if (readSucceeded)
            {
                wchar_t const* const pCleanEnd =
                    myRemove(pBuffer, pBuffer + nCharactersRead);

                nCharactersRead = pCleanEnd - pBuffer;

                bool const isInteractiveEOF =
                    (nCharactersRead == 2 && pBuffer[0] == ctrlZ && pBuffer[1] == '\n');

                return (isInteractiveEOF ? 0 : static_cast<std::streamsize>(nCharactersRead));
            }
            return 0;
        }

        virtual int_type underflow() override
        {
            if (pCurrent() == 0 || pCurrent() >= pEnd())
            {
                const std::streamsize nCharactersRead =
                    xsgetn(m_buffer, m_bufferSize);

                if (nCharactersRead > 0)
                {
                    setg(m_buffer, m_buffer,
                            m_buffer + m_bufferSize);
                }
            }

            if (pCurrent() == 0 || pCurrent() >= pEnd())
            {
                return Traits::eof();
            }
            return Traits::to_int_type(*pCurrent());
        }

    private:
        static const std::streamsize m_bufferSize = 128;
        wchar_t m_buffer[m_bufferSize];

        // std::remove
        template <typename It>
        static inline It myRemove(It first, It last) noexcept
        {
            const auto value = L'\r';

            for (; first != last; ++first) {
                if (*first == value) {
                    break;
                }
            }

            if (first != last) {
                for (auto i = first; ++i != last; ) {
                    if (!(*i == value)) {
                        *first++ = std::move(*i);
                    }
                }
            }
            return first;
        }

        inline wchar_t* pStart()   const noexcept { return eback(); }
        inline wchar_t* pCurrent() const noexcept { return gptr();  }
        inline wchar_t* pEnd()     const noexcept { return egptr(); }
    };
} // namespace details


#endif
#endif // WINUNICODEBUF_HPP
