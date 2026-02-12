/*
    Initial author: Convery (tcn@hedgehogscience.com)
    Started: 08-01-2018
    License: MIT
*/

#pragma once
#include "../Stdinclude.hpp"

namespace Hooking
{
    #define EXTENDEDHOOKDECL(Basehook)                                  \
    template <typename Signature>                                       \
    struct Basehook ##Ex : public Basehook                              \
    {                                                                   \
        std::pair<std::mutex, std::function<Signature>> Function;       \
        virtual bool Installhook(void *Location, void *Target) override \
        {                                                               \
            Function.second = *(Signature *)Location;                   \
            return Basehook::Installhook(Location, Target);             \
        }                                                               \
    }                                                                   \

    struct IHook
    {
        uint8_t Savedcode[20]{};
        void *Savedlocation;
        void *Savedtarget;

        virtual bool Removehook() = 0;
        virtual bool Installhook(void *Location, void *Target) = 0;
        virtual bool Reinstall() { return Installhook(Savedlocation, Savedtarget); };
    };

    struct Stomphook : public IHook
    {
        virtual bool Removehook() override;
        virtual bool Installhook(void *Location, void *Target) override;
    };
    EXTENDEDHOOKDECL(Stomphook);

    struct Callhook : public IHook
    {
        virtual bool Removehook() override;
        virtual bool Installhook(void *Location, void *Target) override;
    };
    EXTENDEDHOOKDECL(Callhook);
}
