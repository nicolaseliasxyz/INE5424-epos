// EPOS Configuration Engine

#ifndef __config_h
#define __config_h

//============================================================================
// ARCHITECTURE, MACHINE, AND APPLICATION SELECTION
// This section is generated automatically from makedefs by $EPOS/etc/makefile
//============================================================================
#define SMOD xxx
#define ARCH xxx
#define MACH xxx
#define MMOD xxx
#define NETW xxx
#define APPL xxx
#define __mode_xxx__
#define __arch_xxx__
#define __mach_xxx__
#define __mmod_xxx__
#define __netw_xxx__

//============================================================================
// NAMESPACES AND DEFINITIONS
//============================================================================
namespace EPOS {
    namespace S {
        namespace U {}
        using namespace U;
    }
}

#define __BEGIN_API             namespace EPOS {
#define __END_API               }
#define _API                    ::EPOS

#define __BEGIN_UTIL            namespace EPOS { namespace S { namespace U {
#define __END_UTIL              }}}
#define __USING_UTIL            using namespace S::U;
#define _UTIL                   ::EPOS::S::U

#define __BEGIN_SYS             namespace EPOS { namespace S {
#define __END_SYS               }}
#define __IN_SYS(X)             namespace EPOS { namespace S { X }}
#define __USING_SYS             using namespace EPOS::S;
#define _SYS                    ::EPOS::S

#ifndef __kernel__
namespace EPOS {
    using namespace S;
    using namespace S::U;
}
#endif

#define __CONCATENATE(X,Y)      X##Y
#define __HEADER_NAME(X,Y)      __CONCATENATE(X,_##Y).h
#define __HEADER_ARCH(X)        <architecture/ARCH/__HEADER_NAME(ARCH,X)>
#define __HEADER_MACH(X)        <machine/MACH/__HEADER_NAME(MACH,X)>
#define __HEADER_MMOD(X)        <machine/MACH/MMOD/__HEADER_NAME(MMOD,X)>
#define __HEADER_TRAN(X)        <transducer/X.h>
#define __APPL_TRAITS_T(X)      <../app/X/X##_traits.h>
#define __APPL_TRAITS(X)        __APPL_TRAITS_T(X)

#define __ARCHITECTURE_TRAITS_H __HEADER_ARCH(traits)
#define __MACHINE_TRAITS_H      __HEADER_MMOD(traits)
#define __APPLICATION_TRAITS_H  __APPL_TRAITS(APPL)

#define ASM                     __asm__ __volatile__

//============================================================================
// ASSERT (for pre and post conditions)
//============================================================================
#define assert(expr)    ((expr) ? static_cast<void>(0) : Assert::fail (#expr, __FILE__, __LINE__, __PRETTY_FUNCTION__))
//#define assert(expr)    (static_cast<void>(0))

//============================================================================
// CONFIGURATION
//============================================================================
#define __CPU_H                 __HEADER_ARCH(cpu)
#define __MMU_H                 __HEADER_ARCH(mmu)

#define __MACH_H                __HEADER_MACH(machine)
#define __IC_H                  __HEADER_MACH(ic)
#define __TIMER_H               __HEADER_MACH(timer)

#ifdef __legacy_pc__
#define __pc__
#define __TSC_H                 __HEADER_ARCH(tsc)
#define __PMU_H                 __HEADER_ARCH(pmu)

#define __PCI_H                 __HEADER_MACH(pci)
#define __RTC_H                 __HEADER_MACH(rtc)
#define __EEPROM_H              __HEADER_MACH(eeprom)
#define __UART_H                __HEADER_MACH(uart)
#define __DISPLAY_H             __HEADER_MACH(display)
#define __KEYBOARD_H            __HEADER_MACH(keyboard)
#define __SCRATCHPAD_H          __HEADER_MACH(scratchpad)
#define __FPGA_H                __HEADER_MACH(fpga)

#ifndef __standalone__
#define __NIC_H                 __HEADER_MACH(nic)
#define __ethernet__
#define __elp__
#define __ipv4__
#define __tstp__
#endif

#define __KEYPAD_H              __HEADER_TRAN(keypad)

#endif

#ifdef __lm3s811__
#define __armv7m__
#define __cortex_m__
#define __cortex_m3__
#define __TSC_H                 __HEADER_ARCH(tsc)

#define __UART_H                __HEADER_MACH(uart)
#define __GPIO_H                __HEADER_MACH(gpio)
#endif

#ifdef __emote3__
#define __armv7m__
#define __cortex_m__
#define __cortex_m3__
#define __TSC_H                 __HEADER_ARCH(tsc)

#define __EEPROM_H              __HEADER_MACH(eeprom)
#define __UART_H                __HEADER_MACH(uart)
#define __SPI_H                 __HEADER_MACH(spi)
#define __RS485_H               __HEADER_MACH(rs485)
#define __USB_H                 __HEADER_MACH(usb)
#define __I2C_H                 __HEADER_MACH(i2c)
#define __GPIO_H                __HEADER_MACH(gpio)
#define __ADC_H                 __HEADER_MACH(adc)
#define __PWM_H                 __HEADER_MACH(pwm)
#define __WATCHDOG_H            __HEADER_MACH(watchdog)

#ifndef __standalone__
#define __NIC_H                 __HEADER_MACH(nic)
#define __modem__
#define __ieee802_15_4__
#define __elp__
#define __tstp__
#endif

#define __ACCELEROMETER_H       __HEADER_TRAN(accelerometer)
#define __GYROSCOPE_H           __HEADER_TRAN(gyroscope)
#define __CO2_SENSOR_H          __HEADER_TRAN(co2_sensor)
#define __PLUVIOMETER_H         __HEADER_TRAN(pluviometer)
#define __PRESSURE_SENSOR_H     __HEADER_TRAN(pressure_sensor)
#define __THERMOMETER_H         __HEADER_TRAN(thermometer)
#define __HYGROMETER_H          __HEADER_TRAN(hygrometer)
#endif

#ifdef __fz3__
#define __cortex_a__
#define __cortex_a53__
#define __TSC_H                 __HEADER_ARCH(tsc)
#define __PMU_H                 __HEADER_ARCH(pmu)

#define __UART_H                __HEADER_MACH(uart)
#endif

#ifdef __zynq__
#define __armv7a__
#define __cortex_a__
#define __cortex_a9__
#define __TSC_H                 __HEADER_ARCH(tsc)
#define __PMU_H                 __HEADER_ARCH(pmu)

#define __UART_H                __HEADER_MACH(uart)
#define __AES_H                 __HEADER_MACH(aes)
#endif

#ifdef __realview_pbx__
#define __armv7a__
#define __cortex_a__
#define __cortex_a9__
#define __realview_pbx__
#define __TSC_H                 __HEADER_ARCH(tsc)
#define __PMU_H                 __HEADER_ARCH(pmu)

#define __UART_H                __HEADER_MACH(uart)
#endif

#ifdef __raspberry_pi3__
#define __cortex_a__
#define __cortex_a53__
#define __TSC_H                 __HEADER_ARCH(tsc)
#define __PMU_H                 __HEADER_ARCH(pmu)

#define __UART_H                __HEADER_MACH(uart)
#endif

#ifdef __sifive_e__
#define __riscv__
#define __TSC_H                 __HEADER_ARCH(tsc)
#define __PMU_H                 __HEADER_ARCH(pmu)

#define __UART_H                __HEADER_MACH(uart)
#endif

#ifdef __sifive_u__
#define __riscv__
#define __TSC_H                 __HEADER_ARCH(tsc)
#define __PMU_H                 __HEADER_ARCH(pmu)
#define __UART_H                __HEADER_MACH(uart)
#define __SPI_H                 __HEADER_MACH(spi)

#ifndef __standalone__
#define __NIC_H                 __HEADER_MACH(nic)
#define __ethernet__
#define __elp__
#define __ipv4__
#define __tstp__
#endif

#endif

#include <system/meta.h>
#include <system/traits.h>
#include __APPLICATION_TRAITS_H
#include <system/types.h>

//============================================================================
// THINGS EVERBODY NEEDS
//============================================================================
#include <utility/ostream.h>
#include <utility/debug.h>

#endif
